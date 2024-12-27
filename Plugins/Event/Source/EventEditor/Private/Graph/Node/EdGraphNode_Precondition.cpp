#include "Graph/Node/EdGraphNode_Precondition.h"

#include "Graph/Widget/GraphNode_Precondition.h"

void UEdGraphNode_Precondition::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	// 引脚
	{
		// input
		{
			CreateInputPin(TEXT("前置条件"), FEventNodeTypes::NODE_TYPE_PRECONDITION, false, false);
		}

		// output
		{
		}
	}
}

TSharedPtr<SGraphNode> UEdGraphNode_Precondition::CreateVisualWidget()
{
	return SNew(SGraphNode_Precondition, this);
}
