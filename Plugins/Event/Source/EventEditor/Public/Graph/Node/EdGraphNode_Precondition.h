#pragma once
#include "EdGraphNode_Event.h"

#include "EdGraphNode_Precondition.generated.h"

UCLASS()
class UEdGraphNode_Precondition : public UEdGraphNode_Event
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
};
