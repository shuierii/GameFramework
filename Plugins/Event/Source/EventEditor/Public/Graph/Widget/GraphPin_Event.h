#pragma once

#include "SGraphPin.h"

class EVENTEDITOR_API SGraphPin_Event : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SGraphPin_Event)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);
};
