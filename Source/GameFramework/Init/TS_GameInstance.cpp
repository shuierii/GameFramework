#include "TS_GameInstance.h"

void UTS_GameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("C++ GameInstance init"));
	this->TSReceiveInit();
}

void UTS_GameInstance::Shutdown()
{
	Super::Shutdown();
	UE_LOG(LogTemp, Warning, TEXT("C++ GameInstance Shutdown"));
	this->TSReceiveShutdown();
}
