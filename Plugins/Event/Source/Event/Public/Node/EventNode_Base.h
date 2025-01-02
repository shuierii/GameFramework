#pragma once
#include "EventTypes.h"

#include "EventNode_Base.generated.h"

UCLASS(Abstract)
class EVENT_API UEventNode_Base : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	void SetEdGraphNode(UEdGraphNode* NewGraphNode);
	UEdGraphNode* GetEdGraphNode();

	virtual FString GetNodeCategory() const;
	virtual FText GetNodeTitle() const;
	virtual FText GetNodeToolTip() const;

	EEventNodeStyle GetNodeStyle() const { return NodeStyle; }

protected:
	UPROPERTY()
	FString Category;

	UPROPERTY(VisibleDefaultsOnly, Category = "EventNode")
	EEventNodeStyle NodeStyle;

private:
	UPROPERTY()
	UEdGraphNode* EventEdGraphNode;
};
