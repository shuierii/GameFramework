#include "Graph/Node/EdGraphNode_DialogEvent.h"

#include "Graph/Widget/GraphNode_DialogEvent.h"

void UEdGraphNode_DialogEvent::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	// 引脚
	{
		// input
		{
		}

		// output
		{
			CreateOutputPin(TEXT("前置条件"), FEventNodeTypes::NODE_TYPE_PRECONDITION, false, false, FEventNodeTypes::PIN_SUB_TYPE_PUBLIC);
			CreateOutputPin(TEXT("剧本"), FEventNodeTypes::NODE_TYPE_SCRIPT, false, false);
		}
	}
}

TSharedPtr<SGraphNode> UEdGraphNode_DialogEvent::CreateVisualWidget()
{
	return SNew(SGraphNode_DialogEvent, this);
}
