#pragma once

#include "Styling/SlateStyle.h"

struct EVENTEDITOR_API FEventEditorStyle
{
public:
	static void Initialize();
	static void Shutdown();
	static FName GetStyleSetName();
	static TSharedPtr<ISlateStyle> Get() { return StyleSet; };

	static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = nullptr)
	{
		return Get()->GetBrush(PropertyName, Specifier);
	}

private:
	static TSharedPtr<FSlateStyleSet> StyleSet;
};
