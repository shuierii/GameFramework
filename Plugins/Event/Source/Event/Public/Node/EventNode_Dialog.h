#pragma once
#include "EventNode_Base.h"
#include "EventNode_Dialog.generated.h"

class UEventNode_Action;

UCLASS(DisplayName = "对话")
class EVENT_API UEventNode_Dialog : public UEventNode_Base
{
	GENERATED_UCLASS_BODY()
public:
	virtual FString GetNodeType() override { return "E_Dialog"; };

	FDialogText GetOptionContent(FGuid PinID);

	virtual void ResetConnectData() override
	{
		Super::ResetConnectData();

		ActionOfEnter = nullptr;
		ActionOfExit = nullptr;
		DialogOptionList.Empty();
	};

public:
	UPROPERTY()
	UEventNode_Action* ActionOfEnter;

	UPROPERTY()
	UEventNode_Action* ActionOfExit;
	
	UPROPERTY()
	TArray<FDialogOption> DialogOptionList;
};
