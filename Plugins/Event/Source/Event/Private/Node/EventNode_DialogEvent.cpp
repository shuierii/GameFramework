﻿#include "Node/EventNode_DialogEvent.h"

UEventNode_DialogEvent::UEventNode_DialogEvent(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	Category = TEXT("DialogEvent");
	NodeStyle = EEventNodeStyle::DialogEvent;
}
