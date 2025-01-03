#pragma once
#include "EdGraphNode_Base.h"
#include "EdGraphNode_Script.generated.h"

UCLASS()
class EVENTEDITOR_API UEdGraphNode_Script : public UEdGraphNode_Base
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
};
