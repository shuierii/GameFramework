#include "Graph/Node/EdGraphNode_Input.h"

#include "Graph/Widget/GraphNode_Input.h"

void UEdGraphNode_Input::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	// 引脚
	{
		// input
		{
		}

		// output
		{
			CreateOutputPin(TEXT("输入器"), FEventNodeTypes::NODE_TYPE_INPUT, false, false);
		}
	}
}

TSharedPtr<SGraphNode> UEdGraphNode_Input::CreateVisualWidget()
{
	return SNew(SGraphNode_Input, this);
}
