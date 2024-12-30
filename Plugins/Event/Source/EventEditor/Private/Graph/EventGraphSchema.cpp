#include "Graph/EventGraphSchema.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Blueprint/Blueprint_EventNode_Input.h"
#include "Blueprint/Blueprint_EventNode_Output.h"
#include "Blueprint/Blueprint_EventNode_Precondition.h"
#include "Blueprint/Blueprint_EventNode_Trigger.h"
#include "Graph/EventGraphSchemaActions.h"
#include "Graph/Node/EdGraphNode_Input.h"
#include "Graph/Node/EdGraphNode_Output.h"
#include "Graph/Node/EdGraphNode_Precondition.h"
#include "Graph/Node/EdGraphNode_Trigger.h"
#include "Node/EventNode_Input.h"
#include "Node/EventNode_Output.h"
#include "Node/EventNode_Precondition.h"
#include "Node/EventNode_Trigger.h"

#define LOCTEXT_NAMESPACE "UEventGraphSchema"

TArray<UClass*> UEventGraphSchema::NativeEventNodes;
TMap<UClass*, UClass*> UEventGraphSchema::AssignedEdGraphNodeClasses; // <EventNode,EdGraphNode>
TMap<FName, FAssetData> UEventGraphSchema::BlueprintEventNodes; // <资产名，蓝图资产>

void UEventGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	BindEventNodeActions(ContextMenuBuilder);

	UE_LOG(LogTemp, Log, TEXT("右键显示节点列表"));
}

void UEventGraphSchema::BindAssetChangeActions()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(AssetRegistryConstants::ModuleName);
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	AssetRegistry.OnFilesLoaded().AddStatic(&UEventGraphSchema::GatherEventNodes);
	AssetRegistry.OnAssetAdded().AddStatic(&UEventGraphSchema::OnAssetAdded);
	AssetRegistry.OnAssetRemoved().AddStatic(&UEventGraphSchema::OnAssetRemoved);
}

UClass* UEventGraphSchema::GetAssignedEdGraphNodeClass(const UClass* EventNodeClass)
{
	if (AssignedEdGraphNodeClasses.Num() == 0)
	{
		GatherEventNodes();
	}

	for (auto KV : AssignedEdGraphNodeClasses)
	{
		if (EventNodeClass->IsChildOf(KV.Key))
		{
			return KV.Value;
		}
	}

	return UEdGraphNode_Event::StaticClass();
}

void UEventGraphSchema::BindEventNodeActions(FGraphActionMenuBuilder& ActionMenuBuilder)
{
	if (NativeEventNodes.Num() == 0)
	{
		GatherEventNodes();
	}

	TArray<UEventNode_Base*> FilteredNodes;
	{
		FilteredNodes.Reserve(NativeEventNodes.Num() + BlueprintEventNodes.Num()); // 预留足够的内存控件，不用在添加元素的时候频繁申请内存，提高性能

		for (const UClass* EventNodeClass : NativeEventNodes)
		{
			UEventNode_Base* NodeDefault = EventNodeClass->GetDefaultObject<UEventNode_Base>();
			FilteredNodes.Emplace(NodeDefault);
		}

		for (const auto AssetData : BlueprintEventNodes)
		{
			if (const UBlueprint* Blueprint = Cast<UBlueprint>(AssetData.Value.GetAsset()))
			{
				UClass* EventNodeClass = Blueprint->GeneratedClass;
				UEventNode_Base* NodeDefault = EventNodeClass->GetDefaultObject<UEventNode_Base>();
				FilteredNodes.Emplace(NodeDefault);
			}
		}

		FilteredNodes.Shrink();
	}

	for (const UEventNode_Base* EventNode : FilteredNodes)
	{
		TSharedPtr<FEventGraphSchemaActions_NewNode> NewNodeAction(new FEventGraphSchemaActions_NewNode(EventNode));
		ActionMenuBuilder.AddAction(NewNodeAction);
	}
}

void UEventGraphSchema::GatherEventNodes()
{
	// 在游戏中返回
	if (GEditor && GEditor->PlayWorld)
	{
		return;
	}

	if (NativeEventNodes.Num() == 0)
	{
		TArray<UClass*> EventNodes;
		GetDerivedClasses(UEventNode_Base::StaticClass(), EventNodes); // 获取已有的 EventNode_Base 列表 (蓝图)
		for (UClass* Class : EventNodes)
		{
			NativeEventNodes.Emplace(Class);
		}

		UE_LOG(LogTemp, Log, TEXT("加载已创建的蓝图节点进列表"));

		// Trigger
		AssignedEdGraphNodeClasses.Emplace(UEventNode_Trigger::StaticClass(), UEdGraphNode_Trigger::StaticClass());

		// Precondition
		AssignedEdGraphNodeClasses.Emplace(UEventNode_Precondition::StaticClass(), UEdGraphNode_Precondition::StaticClass());

		// Input
		AssignedEdGraphNodeClasses.Emplace(UEventNode_Input::StaticClass(), UEdGraphNode_Input::StaticClass());

		// Output
		AssignedEdGraphNodeClasses.Emplace(UEventNode_Output::StaticClass(), UEdGraphNode_Output::StaticClass());

		UE_LOG(LogTemp, Log, TEXT("绑定节点类和编辑节点类"));
	}

	// 加载已有的节点资产进列表
	{
		const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(AssetRegistryConstants::ModuleName);

		FARFilter Filter;
		Filter.ClassNames.Add(UBlueprint::StaticClass()->GetFName());
		Filter.ClassNames.Add(UBlueprintGeneratedClass::StaticClass()->GetFName());
		Filter.bRecursiveClasses = true;

		TArray<FAssetData> FoundAssets;
		AssetRegistryModule.Get().GetAssets(Filter, FoundAssets);
		for (const FAssetData& AssetData : FoundAssets)
		{
			OnAssetAdded(AssetData);
		}

		UE_LOG(LogTemp, Log, TEXT("加载加载创建的节点资产进列表"));
	}
}

void UEventGraphSchema::OnAssetAdded(const FAssetData& AssetData)
{
	if (!BlueprintEventNodes.Contains(AssetData.PackageName))
	{
		IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(AssetRegistryConstants::ModuleName).Get();
		if (AssetRegistry.IsLoadingAssets())
		{
			return;
		}

		auto ChildClass = AssetData.GetClass();
		if (ChildClass->IsChildOf(UBlueprint_EventNode_Trigger::StaticClass())
			|| ChildClass->IsChildOf(UBlueprint_EventNode_Precondition::StaticClass())
			|| ChildClass->IsChildOf(UBlueprint_EventNode_Input::StaticClass())
			|| ChildClass->IsChildOf(UBlueprint_EventNode_Output::StaticClass()))
		{
			BlueprintEventNodes.Emplace(AssetData.PackageName, AssetData);

			UE_LOG(LogTemp, Log, TEXT("编辑器开着的时候，节点资产创建，添加进节点列表"));
		}
	}
}

void UEventGraphSchema::OnAssetRemoved(const FAssetData& AssetData)
{
	if (BlueprintEventNodes.Contains(AssetData.PackageName))
	{
		BlueprintEventNodes.Remove(AssetData.PackageName);
		BlueprintEventNodes.Shrink(); // 移除容器末端未使用的内存
	}
}

#undef LOCTEXT_NAMESPACE
