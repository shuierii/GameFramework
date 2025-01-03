#pragma once
#include "EventNode_EventRoot.h"
#include "EventNode_DialogEvent.generated.h"

UCLASS(DisplayName = "对话事件")
class EVENT_API UEventNode_DialogEvent : public UEventNode_EventRoot
{
	GENERATED_UCLASS_BODY()
public:
	virtual FString GetNodeType() override { return "E_DialogEvent"; };
};
