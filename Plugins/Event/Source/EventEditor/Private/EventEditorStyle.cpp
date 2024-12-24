#include "EventEditorStyle.h"

TSharedPtr<FSlateStyleSet> FEventEditorStyle::SlateStyleSet = nullptr;

void FEventEditorStyle::Initialize()
{
}

void FEventEditorStyle::Shutdown()
{
}

FName FEventEditorStyle::GetStyleSetName()
{
	static FName EventEditorStyleName(TEXT("EventEditorStyle"));

	return EventEditorStyleName;
}
