#include "Graph/Node/EdGraphNode_Action.h"

#include "Graph/Widget/GraphNode_Action.h"

void UEdGraphNode_Action::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	// 引脚
	{
		// input
		{
			CreateInputPin(TEXT("行动"), FEventNodeTypes::NODE_TYPE_ACTION, false, false);
		}

		// output
		{
		}
	}
}

TSharedPtr<SGraphNode> UEdGraphNode_Action::CreateVisualWidget()
{
	return SNew(SGraphNode_Action, this);
}
