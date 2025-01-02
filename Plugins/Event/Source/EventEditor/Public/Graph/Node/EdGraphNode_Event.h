#pragma once

#include "EventNodeTypes.h"
#include "Event/Public/Node/EventNode_Base.h"
#include "EdGraphNode_Event.generated.h"

UCLASS()
class EVENTEDITOR_API UEdGraphNode_Event : public UEdGraphNode
{
	GENERATED_BODY()

public:
	// UEdGraphNode
	virtual void AllocateDefaultPins() override; // 默认引脚
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override; // 创建节点widget
	virtual bool CanJumpToDefinition() const override;
	virtual void JumpToDefinition() const override;
	virtual bool CanUserDeleteNode() const override;
	virtual bool CanDuplicateNode() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
	virtual FText GetTooltipText() const override;
	virtual void PrepareForCopying() override;
	// END

	// Pin
	void CreateInputPin(const FName& PinName, const FName& PinType, bool bIsTransaction = false, bool bIsRefreshGraph = true, const FName& PinSubCategory = FEventNodeTypes::PIN_SUB_TYPE_PRIVATE);
	void CreateOutputPin(const FName& PinName, const FName& PinType, bool bIsTransaction = false, bool bIsRefreshGraph = true, const FName& PinSubCategory = FEventNodeTypes::PIN_SUB_TYPE_PRIVATE);
	void CreateOutputPin(const FName& PinName, const FName& PinType, const FName& InsertPinType, bool bIsTransaction = false, bool bIsRefreshGraph = true);
	int32 FindPinLastIndex(const FName& PinType, EEdGraphPinDirection Dir);
	// END

public:
	void SetEventNode(UEventNode_Base* InEventNode);
	UEventNode_Base* GetEventNode() const;

public:
	// 绑定的数据节点
	UPROPERTY()
	UEventNode_Base* EventNode;
};
