#include "Node/EventNode_Script.h"

UEventNode_Script::UEventNode_Script(const FObjectInitializer& ObjectInitializer)
{
	Category = TEXT("Script");
	NodeStyle = EEventNodeStyle::Script;
}

FString UEventNode_Script::GetNodeCategory() const
{
	return TEXT("剧本");
}
