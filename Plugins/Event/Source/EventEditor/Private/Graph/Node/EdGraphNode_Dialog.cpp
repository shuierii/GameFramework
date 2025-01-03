#include "Graph/Node/EdGraphNode_Dialog.h"

#include "Graph/Widget/GraphNode_Dialog.h"

void UEdGraphNode_Dialog::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	// 引脚
	{
		// input
		{
			CreateInputPin(TEXT("对话"), FEventNodeTypes::NODE_TYPE_DIALOG, false, false);
		}

		// output
		{
			CreateOutputPin(TEXT("行动_进入节点"), FEventNodeTypes::NODE_TYPE_ACTION, false, false, FEventNodeTypes::PIN_DIALOG_ACTION_OF_ENTER);
			CreateOutputPin(TEXT("行动_退出节点"), FEventNodeTypes::NODE_TYPE_ACTION, false, false, FEventNodeTypes::PIN_DIALOG_ACTION_OF_EXIT);
		}
	}
}

TSharedPtr<SGraphNode> UEdGraphNode_Dialog::CreateVisualWidget()
{
	return SNew(SGraphNode_Dialog, this);
}
