#include "TS_GameInstance.h"

void UTS_GameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("hello world"));
	this->TSReceiveInit();
}
