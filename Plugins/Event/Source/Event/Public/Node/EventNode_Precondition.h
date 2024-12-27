#pragma once
#include "Node/EventNode_Base.h"

#include "EventNode_Precondition.generated.h"

UCLASS(Abstract, Blueprintable)
class EVENT_API UEventNode_Precondition : public UEventNode_Base
{
	GENERATED_UCLASS_BODY()
public:
	virtual FString GetNodeCategory() const override;
};
