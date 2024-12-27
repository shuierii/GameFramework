#pragma once

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

protected:
	UPROPERTY()
	FString Category;

private:
	UPROPERTY()
	UEdGraphNode* EventEdGraphNode;
};
