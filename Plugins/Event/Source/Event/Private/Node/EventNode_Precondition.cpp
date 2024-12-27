#include "Node/EventNode_Precondition.h"

UEventNode_Precondition::UEventNode_Precondition(const FObjectInitializer& ObjectInitializer)
{
}

FString UEventNode_Precondition::GetNodeCategory() const
{
	return TEXT("前置条件");
}
