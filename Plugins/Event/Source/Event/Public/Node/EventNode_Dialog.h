#pragma once
#include "EventNode_Base.h"
#include "EventNode_Dialog.generated.h"

UCLASS(DisplayName = "对话")
class EVENT_API UEventNode_Dialog : public UEventNode_Base
{
	GENERATED_UCLASS_BODY()
public:
	virtual FString GetNodeType() override { return "E_Dialog"; };
};
