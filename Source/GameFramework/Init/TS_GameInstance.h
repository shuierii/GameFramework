#pragma once
#include "TS_GameInstance.generated.h"

UCLASS()
class GAMEFRAMEWORK_API UTS_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;;

	UFUNCTION(BlueprintImplementableEvent, Category="TS_GameInstance")
	void TSReceiveInit();
};
