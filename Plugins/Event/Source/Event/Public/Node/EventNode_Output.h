#pragma once
#include "EventNode_Base.h"

#include "EventNode_Output.generated.h"

UCLASS(Abstract, Blueprintable)
class EVENT_API UEventNode_Output : public UEventNode_Base
{
	GENERATED_UCLASS_BODY()
public:
	virtual FString GetNodeCategory() const override;
	virtual FString GetNodeType() override { return "E_Output"; };
};
