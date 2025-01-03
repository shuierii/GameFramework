#pragma once
#include "EdGraphNode_EventRoot.h"
#include "EdGraphNode_DialogEvent.generated.h"

UCLASS()
class EVENTEDITOR_API UEdGraphNode_DialogEvent : public UEdGraphNode_EventRoot
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
};
