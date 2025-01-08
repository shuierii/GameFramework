#include "..\..\..\Public\Graph\Node\EdGraphNode_Base.h"

#include "EventEditorCommands.h"
#include "GraphEditorActions.h"
#include "ToolMenu.h"
#include "Framework/Commands/GenericCommands.h"
#include "Graph/EventGraph.h"
#include "Graph/EventGraphSettings.h"
#include "Graph/Widget/GraphNode_Base.h"
#include "Kismet2/KismetEditorUtilities.h"

#define LOCTEXT_NAMESPACE "UEventGraphNode"

void UEdGraphNode_Base::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
}

TSharedPtr<SGraphNode> UEdGraphNode_Base::CreateVisualWidget()
{
	return SNew(SGraphNode_Base, this);
}

void UEdGraphNode_Base::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	const FGenericCommands& GenericCommands = FGenericCommands::Get();
	const FGraphEditorCommandsImpl& GraphCommands = FGraphEditorCommands::Get();

	auto Graph = GetGraph();
	if (Graph->GetClass()->IsChildOf(UEventGraph::StaticClass()))
	{
		const FEventGraphCommands& EventGraphCommands = FEventGraphCommands::Get();

		if (Context->Pin)
		{
			FToolMenuSection& Section = Menu->AddSection("EventGraphPinActions", LOCTEXT("PinActionsMenuHeader", "Pin Actions"));
			if (Context->Pin->Direction == EGPD_Input)
			{
				Section.AddMenuEntry(EventGraphCommands.RemovePin);
			}
			else if (Context->Pin->Direction == EGPD_Output)
			{
				Section.AddMenuEntry(EventGraphCommands.RemovePin);
			}
		}
		else if (Context->Node)
		{
			FToolMenuSection& Section = Menu->AddSection("EventGraphNodeActions", LOCTEXT("PinActionsMenuHeader", "Pin Actions"));
			Section.AddMenuEntry(GenericCommands.Delete);
			Section.AddMenuEntry(GenericCommands.Cut);
			Section.AddMenuEntry(GenericCommands.Copy);
			Section.AddMenuEntry(GenericCommands.Duplicate);

			Section.AddMenuEntry(GraphCommands.BreakNodeLinks);

			Section.AddMenuEntry(EventGraphCommands.JumpToNodeDefinition);
		}
		
		UE_LOG(LogTemp, Log, TEXT("编辑节点/引脚右键操作菜单"));
	}
}

bool UEdGraphNode_Base::CanJumpToDefinition() const
{
	return IsValid(this->EventNode);
}

void UEdGraphNode_Base::JumpToDefinition() const
{
	if (this->EventNode == nullptr)
	{
		return;
	}

	// 区别是C++还是蓝图
	if (this->EventNode->GetClass()->IsNative())
	{
		return;
	}

	// blueprint
	FKismetEditorUtilities::BringKismetToFocusAttentionOnObject(this->EventNode->GetClass());
}

bool UEdGraphNode_Base::CanUserDeleteNode() const
{
	return true;
}

bool UEdGraphNode_Base::CanDuplicateNode() const
{
	return true;
}

FText UEdGraphNode_Base::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (this->EventNode == nullptr)
	{
		return Super::GetNodeTitle(TitleType);
	}

	return this->EventNode->GetNodeTitle();
}

FLinearColor UEdGraphNode_Base::GetNodeTitleColor() const
{
	if (this->EventNode == nullptr)
	{
		return Super::GetNodeTitleColor();
	}

	UEventGraphSettings* GraphSettings = UEventGraphSettings::Get();
	if (const FLinearColor* NodeSpecificColor = GraphSettings->NodeSpecificColors.Find(this->EventNode->GetClass()))
	{
		return *NodeSpecificColor;
	}

	if (const FLinearColor* StyleColor = GraphSettings->NodeTitleColors.Find(this->EventNode->GetNodeStyle()))
	{
		return *StyleColor;
	}

	return Super::GetNodeTitleColor();
}

FSlateIcon UEdGraphNode_Base::GetIconAndTint(FLinearColor& OutColor) const
{
	return FSlateIcon();
}

FText UEdGraphNode_Base::GetTooltipText() const
{
	FText Tooltip;
	if (this->EventNode)
	{
		Tooltip = this->EventNode->GetClass()->GetToolTipText();
	}

	if (Tooltip.IsEmpty())
	{
		Tooltip = GetNodeTitle(ENodeTitleType::ListView);
	}

	return Tooltip;
}

void UEdGraphNode_Base::PrepareForCopying()
{
	Super::PrepareForCopying();

	if (this->EventNode)
	{
		this->EventNode->Rename(nullptr, this,REN_DontCreateRedirectors);
	}
}

void UEdGraphNode_Base::CreateInputPin(const FName& PinName, const FName& PinType, bool bIsTransaction, bool bIsRefreshGraph, const FName& PinSubCategory)
{
	if (PinName.IsNone() || PinType.IsNone())
	{
		return;
	}

	if (bIsTransaction)
	{
		GEditor->BeginTransaction(LOCTEXT("CreateInputPin", "Create Input Pin"));
	}

	ensure(CreatePin(EEdGraphPinDirection::EGPD_Input,PinType,PinSubCategory,PinName));

	UE_LOG(LogTemp, Log, TEXT("编辑节点：创建输入引脚"));

	if (bIsRefreshGraph)
	{
		GetGraph()->NotifyGraphChanged();
	}

	if (bIsTransaction)
	{
		GEditor->EndTransaction();
	}
}

void UEdGraphNode_Base::CreateOutputPin(const FName& PinName, const FName& PinType, bool bIsTransaction, bool bIsRefreshGraph, const FName& PinSubCategory)
{
	if (PinName.IsNone() || PinType.IsNone())
	{
		return;
	}

	if (bIsTransaction)
	{
		GEditor->BeginTransaction(LOCTEXT("CreateOutputPin", "Create Output Pin"));
	}

	ensure(CreatePin(EEdGraphPinDirection::EGPD_Output, PinType, PinSubCategory, PinName));

	UE_LOG(LogTemp, Log, TEXT("编辑节点：创建输出引脚"));

	if (bIsRefreshGraph)
	{
		GetGraph()->NotifyGraphChanged();
	}

	if (bIsTransaction)
	{
		GEditor->EndTransaction();
	}
}

void UEdGraphNode_Base::CreateOutputPin(const FName& PinName, const FName& PinType, const FName& InsertPinType, bool bIsTransaction, bool bIsRefreshGraph)
{
	if (PinName.IsNone() || PinType.IsNone() || InsertPinType.IsNone())
	{
		return;
	}

	if (bIsTransaction)
	{
		GEditor->BeginTransaction(LOCTEXT("CreateInputPin", "Create Input Pin"));
	}

	const int32 InsertIndex = FindPinLastIndex(InsertPinType, EEdGraphPinDirection::EGPD_Output);
	const FEdGraphPinType EdGraphPinType = FEdGraphPinType(PinType, FName(NAME_None), nullptr, EPinContainerType::None, false, FEdGraphTerminalType());
	ensure(CreatePin(EEdGraphPinDirection::EGPD_Output, EdGraphPinType, PinName, InsertIndex + 1));

	UE_LOG(LogTemp, Log, TEXT("编辑节点：插入输出引脚"));

	if (bIsRefreshGraph)
	{
		GetGraph()->NotifyGraphChanged();
	}

	if (bIsTransaction)
	{
		GEditor->EndTransaction();
	}
}

int32 UEdGraphNode_Base::FindPinLastIndex(const FName& PinType, EEdGraphPinDirection Dir)
{
	if (PinType.IsNone())
	{
		return -2;
	}

	// for (int i = 0; i < Pins.Num(); ++i)
	for (int i = Pins.Num() - 1; i >= 0; --i)
	{
		const auto Pin = Pins[i];
		if (Pin == nullptr || Pin->Direction != Dir)
		{
			continue;
		}

		if (Pin->PinType.PinCategory.IsEqual(PinType))
		{
			return i;
		}
	}

	return -2;
}

void UEdGraphNode_Base::SetEventNode(UEventNode_Base* InEventNode)
{
	this->EventNode = InEventNode;
}

UEventNode_Base* UEdGraphNode_Base::GetEventNode() const
{
	return this->EventNode;
}

#undef LOCTEXT_NAMESPACE
