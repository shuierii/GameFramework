#include "Node/EventNode_Base.h"

UEventNode_Base::UEventNode_Base(const FObjectInitializer& ObjectInitializer)
{
	Category = TEXT("None");
	NodeStyle = EEventNodeStyle::None;
}

void UEventNode_Base::SetEdGraphNode(UEdGraphNode* NewGraphNode)
{
	EventEdGraphNode = NewGraphNode;
}

UEdGraphNode* UEventNode_Base::GetEdGraphNode()
{
	return EventEdGraphNode;
}

FString UEventNode_Base::GetNodeCategory() const
{
	if (GetClass()->ClassGeneratedBy)
	{
		const FString& BlueprintCategory = Cast<UBlueprint>(GetClass()->ClassGeneratedBy)->BlueprintCategory;
		if (!BlueprintCategory.IsEmpty())
		{
			return BlueprintCategory;
		}
	}

	return Category;
}

FText UEventNode_Base::GetNodeTitle() const
{
	return GetClass()->GetDisplayNameText();
}

FText UEventNode_Base::GetNodeToolTip() const
{
	if (GetClass()->ClassGeneratedBy)
	{
		const FString& BlueprintToolTip = Cast<UBlueprint>(GetClass()->ClassGeneratedBy)->BlueprintDescription;
		if (!BlueprintToolTip.IsEmpty())
		{
			return FText::FromString(BlueprintToolTip);
		}
	}

	return GetClass()->GetToolTipText();
}

FString UEventNode_Base::GetNodeType()
{
	int32 lastIndex;
	FString nodeName = GetClass()->GetName();
	nodeName.FindLastChar('_', lastIndex);
	nodeName.RemoveAt(lastIndex, nodeName.Len() - lastIndex);

	return nodeName;
}
