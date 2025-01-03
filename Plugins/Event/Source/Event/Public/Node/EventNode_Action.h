#pragma once
#include "EventNode_Base.h"
#include "EventNode_Action.generated.h"

UCLASS(Abstract, Blueprintable)
class EVENT_API UEventNode_Action : public UEventNode_Base
{
	GENERATED_UCLASS_BODY()
public:
	virtual FString GetNodeCategory() const override { return TEXT("行动"); };
	virtual FString GetNodeType() override { return "E_Action"; };
};
