#include "Node/EventNode_Input.h"

UEventNode_Input::UEventNode_Input(const FObjectInitializer& ObjectInitializer)
{
	Category = TEXT("Input");
	NodeStyle = EEventNodeStyle::Input;
}

FString UEventNode_Input::GetNodeCategory() const
{
	return TEXT("输入");
}
