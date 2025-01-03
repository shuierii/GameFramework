#pragma once
#include "EdGraphNode_Base.h"
#include "EdGraphNode_Trigger.generated.h"

UCLASS()
class EVENTEDITOR_API UEdGraphNode_Trigger : public UEdGraphNode_Base
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
};
