#include "Graph/EventGraphSchema.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Blueprint/Blueprint_EventNode_Action.h"
#include "Blueprint/Blueprint_EventNode_Input.h"
#include "Blueprint/Blueprint_EventNode_Output.h"
#include "Blueprint/Blueprint_EventNode_Precondition.h"
#include "Blueprint/Blueprint_EventNode_Trigger.h"
#include "Graph/EventGraphSchemaActions.h"
#include "Graph/Node/EdGraphNode_Action.h"
#include "Graph/Node/EdGraphNode_Dialog.h"
#include "Graph/Node/EdGraphNode_DialogEvent.h"
#include "Graph/Node/EdGraphNode_Input.h"
#include "Graph/Node/EdGraphNode_Output.h"
#include "Graph/Node/EdGraphNode_Precondition.h"
#include "Graph/Node/EdGraphNode_Script.h"
#include "Graph/Node/EdGraphNode_Trigger.h"
#include "Misc/HotReloadInterface.h"
#include "Node/EventNode_Action.h"
#include "Node/EventNode_Dialog.h"
#include "Node/EventNode_DialogEvent.h"
#include "Node/EventNode_Input.h"
#include "Node/EventNode_Output.h"
#include "Node/EventNode_Precondition.h"
#include "Node/EventNode_Script.h"
#include "Node/EventNode_Trigger.h"

#define LOCTEXT_NAMESPACE "UEventGraphSchema"

TArray<UClass*> UEventGraphSchema::NativeEventNodes;
TMap<UClass*, UClass*> UEventGraphSchema::AssignedEdGraphNodeClasses; // <EventNode,EdGraphNode>
TMap<FName, FAssetData> UEventGraphSchema::BlueprintEventNodes; // <资产名，蓝图资产>

FOnPinConnection UEventGraphSchema::OnPinConnection;
FEventGraphSchemaRefresh UEventGraphSchema::OnNodeListChanged;

void UEventGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	BindEventNodeActions(ContextMenuBuilder);

	UE_LOG(LogTemp, Log, TEXT("右键显示节点列表"));
}

const FPinConnectionResponse UEventGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	// 无法自己连接自己
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,LOCTEXT("PinErrorSameNode", "Both are on the same node"));
	}

	// 输入无法连接输入
	if (A->Direction == EGPD_Input && B->Direction == EGPD_Input)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,LOCTEXT("PinErrorInputToInput", "Can't connnect input to input"));
	}

	// 输出无法连接输出
	if (A->Direction == EGPD_Output && B->Direction == EGPD_Output)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,LOCTEXT("PinErrorOutputToOutput", "Can't connnect output to output"));
	}

	// 引脚类型不一致
	if (!A->PinType.PinCategory.IsEqual(B->PinType.PinCategory))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,LOCTEXT("PinErrorPinTypeNotSame", "PinType not same"));
	}

	// CONNECT_RESPONSE_BREAK_OTHERS_AB先中断AB再连接
	return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_AB,LOCTEXT("PinConnect", "Connect nodes"));
}

bool UEventGraphSchema::TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const
{
	const bool bModified = UEdGraphSchema::TryCreateConnection(A, B);
	if (bModified)
	{
		A->GetOwningNode()->GetGraph()->NotifyGraphChanged();
		OnPinConnection.ExecuteIfBound(A, B);
	}

	return bModified;
}

void UEventGraphSchema::BindAssetChangeActions()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(AssetRegistryConstants::ModuleName);
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	AssetRegistry.OnFilesLoaded().AddStatic(&UEventGraphSchema::GatherEventNodes);
	AssetRegistry.OnAssetAdded().AddStatic(&UEventGraphSchema::OnAssetAdded);
	AssetRegistry.OnAssetRemoved().AddStatic(&UEventGraphSchema::OnAssetRemoved);

	// 允许在不重开编辑器的情况下，编译重载（比如节点蓝图更改）
	IHotReloadInterface& HotReloadInterface = FModuleManager::LoadModuleChecked<IHotReloadInterface>("HotReload");
	HotReloadInterface.OnHotReload().AddStatic([](bool bWasTriggeredAutomatically) { GatherEventNodes(); });

	// 蓝图编译触发
	if (GEditor)
	{
		GEditor->OnBlueprintCompiled().AddStatic([]() { GatherEventNodes(); });
	}
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

	return UEdGraphNode_Base::StaticClass();
}

TArray<TSharedPtr<FString>> UEventGraphSchema::GetEventNodeCategories()
{
	if (NativeEventNodes.Num() == 0)
	{
		GatherEventNodes();
	}

	TSet<FString> UnsortedCategories;
	for (const UClass* EventNodeClass : NativeEventNodes)
	{
		if (const UEventNode_Base* DefaultObject = EventNodeClass->GetDefaultObject<UEventNode_Base>())
		{
			UnsortedCategories.Emplace(DefaultObject->GetNodeCategory());
		}
	}

	for (const TPair<FName, FAssetData>& AssetData : BlueprintEventNodes)
	{
		if (const UBlueprint* Blueprint = Cast<UBlueprint>(AssetData.Value.GetAsset()))
		{
			if (Blueprint->BlueprintCategory.IsEmpty())
			{
				auto DefaultObject = Blueprint->GeneratedClass->GetDefaultObject<UEventNode_Base>();
				if (DefaultObject == nullptr)
				{
					continue;
				}

				UnsortedCategories.Emplace(DefaultObject->GetNodeCategory());
			}
			else
			{
				UnsortedCategories.Emplace(Blueprint->BlueprintCategory);
			}
		}
	}

	TArray<FString> SortedCategories = UnsortedCategories.Array();
	SortedCategories.Sort();

	// create list of categories
	TArray<TSharedPtr<FString>> Result;
	for (const FString& Category : SortedCategories)
	{
		if (!Category.IsEmpty())
		{
			Result.Emplace(MakeShareable(new FString(Category)));
		}
	}

	return Result;
}

void UEventGraphSchema::GetPaletteActions(FGraphActionMenuBuilder& ActionMenuBuilder)
{
	BindEventNodeActions(ActionMenuBuilder);
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
			if (EventNodeClass == nullptr)
			{
				continue;
			}

			UEventNode_Base* NodeDefault = EventNodeClass->GetDefaultObject<UEventNode_Base>();
			FilteredNodes.Emplace(NodeDefault);
		}

		for (const auto AssetData : BlueprintEventNodes)
		{
			if (const UBlueprint* Blueprint = Cast<UBlueprint>(AssetData.Value.GetAsset()))
			{
				UClass* EventNodeClass = Blueprint->GeneratedClass;
				if (EventNodeClass->HasAnyClassFlags(CLASS_Abstract | CLASS_NotPlaceable | CLASS_Deprecated))
				{
					continue;
				}

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
			if (Class->ClassGeneratedBy == nullptr && Class->HasAnyClassFlags(CLASS_Abstract | CLASS_NotPlaceable | CLASS_Deprecated))
			{
				continue;
			}

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

		// Event
		AssignedEdGraphNodeClasses.Emplace(UEventNode_DialogEvent::StaticClass(), UEdGraphNode_DialogEvent::StaticClass());

		// Script
		AssignedEdGraphNodeClasses.Emplace(UEventNode_Script::StaticClass(), UEdGraphNode_Script::StaticClass());

		// Action
		AssignedEdGraphNodeClasses.Emplace(UEventNode_Action::StaticClass(), UEdGraphNode_Action::StaticClass());

		// Dialog
		AssignedEdGraphNodeClasses.Emplace(UEventNode_Dialog::StaticClass(), UEdGraphNode_Dialog::StaticClass());

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

	OnNodeListChanged.Broadcast();
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
			|| ChildClass->IsChildOf(UBlueprint_EventNode_Output::StaticClass())
			|| ChildClass->IsChildOf(UBlueprint_EventNode_Action::StaticClass()))
		{
			BlueprintEventNodes.Emplace(AssetData.PackageName, AssetData);

			UE_LOG(LogTemp, Log, TEXT("编辑器开着的时候，节点资产创建，添加进节点列表"));
		}

		OnNodeListChanged.Broadcast();
	}
}

void UEventGraphSchema::OnAssetRemoved(const FAssetData& AssetData)
{
	if (BlueprintEventNodes.Contains(AssetData.PackageName))
	{
		BlueprintEventNodes.Remove(AssetData.PackageName);
		BlueprintEventNodes.Shrink(); // 移除容器末端未使用的内存

		OnNodeListChanged.Broadcast();
	}
}

#undef LOCTEXT_NAMESPACE
