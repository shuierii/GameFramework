#pragma once

#include "Styling/SlateStyle.h"

struct EVENTEDITOR_API FEventEditorStyle
{
public:
	static void Initialize();
	static void Shutdown();
	static FName GetStyleSetName();
	static TSharedPtr<ISlateStyle> Get() { return SlateStyleSet; };

private:
	static TSharedPtr<FSlateStyleSet> SlateStyleSet;
};
