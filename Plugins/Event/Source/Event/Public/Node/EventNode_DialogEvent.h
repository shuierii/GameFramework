#pragma once
#include "EventNode_EventRoot.h"
#include "EventNode_DialogEvent.generated.h"

class UEventNode_Script;

UCLASS(DisplayName = "对话事件")
class EVENT_API UEventNode_DialogEvent : public UEventNode_EventRoot
{
	GENERATED_UCLASS_BODY()
public:
	virtual FString GetNodeType() override { return "E_DialogEvent"; };

	virtual void ResetConnectData() override
	{
		Super::ResetConnectData();

		ScriptList.Empty();
	};

public:
	UPROPERTY()
	TArray<UEventNode_Script*> ScriptList;
};
