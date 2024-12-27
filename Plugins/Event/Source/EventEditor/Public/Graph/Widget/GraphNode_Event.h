#pragma once
#include "SGraphNode.h"
#include "Graph/Node/EdGraphNode_Event.h"

class EVENTEDITOR_API SGraphNode_Event : public SGraphNode
{
public:
	// slate必须有
	SLATE_BEGIN_ARGS(SGraphNode_Event)
		{
		}

	SLATE_END_ARGS()

	// 必须有，widget创建从这里入
	void Construct(const FArguments& InArgs, UEdGraphNode_Event* InNode);

protected:
	// SGraphNode
	virtual void UpdateGraphNode() override;
	virtual void CreateStandardPinWidget(UEdGraphPin* Pin) override;
	// END

	virtual TSharedRef<SWidget> CreateCommentBubble();
	virtual TSharedRef<SWidget> CreateNodeTitle();
	virtual TSharedRef<SWidget> CreateNodeBody();

	virtual void CreateInputAddButton()
	{
	};

	virtual void CreateOutputAddButton()
	{
	};

protected:
	UEdGraphNode_Event* EventGraphNode = nullptr;
};
