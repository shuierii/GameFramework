#include "Node/EventNode_Output.h"

UEventNode_Output::UEventNode_Output(const FObjectInitializer& ObjectInitializer)
{
	Category = TEXT("Output");
	NodeStyle = EEventNodeStyle::Output;
}

FString UEventNode_Output::GetNodeCategory() const
{
	return TEXT("输出");
}
