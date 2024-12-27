#include "Graph/Node/EdGraphNode_Trigger.h"

#include "Graph/Widget/GraphNode_Trigger.h"

void UEdGraphNode_Trigger::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	// 引脚
	{
		// input
		{
		}

		// output
		{
			// precondition
			CreateOutputPin(TEXT("前置条件"), FEventNodeTypes::NODE_TYPE_PRECONDITION, false, false, FEventNodeTypes::PIN_SUB_TYPE_PUBLIC);
			CreateOutputPin(TEXT("触发器"), FEventNodeTypes::NODE_TYPE_TRIGGER, false, false);
		}
	}
}

TSharedPtr<SGraphNode> UEdGraphNode_Trigger::CreateVisualWidget()
{
	return SNew(SGraphNode_Trigger, this);
}
