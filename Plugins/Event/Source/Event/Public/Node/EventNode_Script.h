#pragma once
#include "EventNode_Base.h"
#include "EventNode_Script.generated.h"

class UEventNode_Action;
class UEventNode_Dialog;

UCLASS(DisplayName = "剧本")
class EVENT_API UEventNode_Script : public UEventNode_Base
{
	GENERATED_UCLASS_BODY() // 需要在.cpp实现构造函数，类成员对象默认是public
public:
	virtual FString GetNodeCategory() const override;
	virtual FString GetNodeType() override { return "E_Script"; };

	virtual void ResetConnectData() override
	{
		Super::ResetConnectData();

		ActionOfStartScript = nullptr;
		Dialog = nullptr;
	};

public:
	UPROPERTY()
	UEventNode_Action* ActionOfStartScript;

	UPROPERTY()
	UEventNode_Dialog* Dialog;
};
