#pragma once
#include "EventNode_Base.h"
#include "EventNode_Input.generated.h"

UCLASS(Abstract, Blueprintable)
class EVENT_API UEventNode_Input : public UEventNode_Base
{
	GENERATED_UCLASS_BODY()
public:
	virtual FString GetNodeCategory() const override;
	virtual FString GetNodeType() override { return "E_Input"; };
};
