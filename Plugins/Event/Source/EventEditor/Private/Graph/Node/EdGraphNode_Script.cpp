#include "Graph/Node/EdGraphNode_Script.h"

#include "Graph/Widget/GraphNode_Script.h"

void UEdGraphNode_Script::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	// 引脚
	{
		// input
		{
			CreateInputPin(TEXT("剧本"), FEventNodeTypes::NODE_TYPE_SCRIPT, false, false);
		}

		// output
		{
			CreateOutputPin(TEXT("行动_开始剧本前"), FEventNodeTypes::NODE_TYPE_ACTION, false, false);
			CreateOutputPin(TEXT("对话"), FEventNodeTypes::NODE_TYPE_DIALOG, false, false);
		}
	}
}

TSharedPtr<SGraphNode> UEdGraphNode_Script::CreateVisualWidget()
{
	return SNew(SGraphNode_Script, this);
}
