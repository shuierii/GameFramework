#include "Node/EventNode_Action.h"

UEventNode_Action::UEventNode_Action(const FObjectInitializer& ObjectInitializer)
{
	Category = TEXT("Action");
	NodeStyle = EEventNodeStyle::Action;
}
