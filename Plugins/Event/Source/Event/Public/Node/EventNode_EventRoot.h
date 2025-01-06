#pragma once
#include "EventNode_Base.h"
#include "EventNode_EventRoot.generated.h"

class UEventNode_Trigger;

UCLASS(Abstract, Blueprintable)
class EVENT_API UEventNode_EventRoot : public UEventNode_Base
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void ResetConnectData() override
	{
		Super::ResetConnectData();

		TriggerList.Empty();
	};

public:
	UPROPERTY()
	TArray<UEventNode_Trigger*> TriggerList;
};
