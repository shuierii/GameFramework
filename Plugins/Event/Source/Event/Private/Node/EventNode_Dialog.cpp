#include "Node/EventNode_Dialog.h"

UEventNode_Dialog::UEventNode_Dialog(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	Category = TEXT("Dialog");
	NodeStyle = EEventNodeStyle::Dialog;
}

FDialogText UEventNode_Dialog::GetOptionContent(FGuid PinID)
{
	return FDialogText();
}
