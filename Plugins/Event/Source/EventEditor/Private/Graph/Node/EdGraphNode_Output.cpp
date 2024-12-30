#include "Graph/Node/EdGraphNode_Output.h"

#include "Graph/Widget/GraphNode_Output.h"

void UEdGraphNode_Output::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	// 引脚
	{
		// input
		{
			// precondition
			CreateInputPin(TEXT("输出器"), FEventNodeTypes::NODE_TYPE_OUTPUT, false, false);
		}

		// output
		{
		}
	}
}

TSharedPtr<SGraphNode> UEdGraphNode_Output::CreateVisualWidget()
{
	return SNew(SGraphNode_Output, this);
}
