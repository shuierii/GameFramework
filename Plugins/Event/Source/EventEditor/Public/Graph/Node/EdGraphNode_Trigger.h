﻿#pragma once
#include "EdGraphNode_Event.h"
#include "EdGraphNode_Trigger.generated.h"

UCLASS()
class EVENTEDITOR_API UEdGraphNode_Trigger : public UEdGraphNode_Event
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
};
