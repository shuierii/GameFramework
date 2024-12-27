#include "Graph/Node/EdGraphNode_Event.h"

#include "Graph/Widget/GraphNode_Event.h"

#define LOCTEXT_NAMESPACE "UEventGraphNode"

void UEdGraphNode_Event::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
}

TSharedPtr<SGraphNode> UEdGraphNode_Event::CreateVisualWidget()
{
	return SNew(SGraphNode_Event, this);
}

void UEdGraphNode_Event::CreateInputPin(const FName& PinName, const FName& PinType, bool bIsTransaction, bool bIsRefreshGraph, const FName& PinSubCategory)
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

void UEdGraphNode_Event::CreateOutputPin(const FName& PinName, const FName& PinType, bool bIsTransaction, bool bIsRefreshGraph, const FName& PinSubCategory)
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

void UEdGraphNode_Event::CreateOutputPin(const FName& PinName, const FName& PinType, const FName& InsertPinType, bool bIsTransaction, bool bIsRefreshGraph)
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

int32 UEdGraphNode_Event::FindPinLastIndex(const FName& PinType, EEdGraphPinDirection Dir)
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

void UEdGraphNode_Event::SetEventNode(UEventNode_Base* InEventNode)
{
	EventNode = InEventNode;
}

UEventNode_Base* UEdGraphNode_Event::GetEventNode()
{
	return EventNode;
}

#undef LOCTEXT_NAMESPACE
