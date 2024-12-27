#include "Node/EventNode_Trigger.h"

UEventNode_Trigger::UEventNode_Trigger(const FObjectInitializer& ObjectInitializer)
{
}

FString UEventNode_Trigger::GetNodeCategory() const
{
	return TEXT("触发器");
}
