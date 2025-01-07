#pragma once
#include "EventAssetEditor.h"

class EVENTEDITOR_API FEventAssetToolbar final : public TSharedFromThis<FEventAssetToolbar>
{
public:
	explicit FEventAssetToolbar(UToolMenu* ToolMenu);

private:
	void BuildAssetToolbar(UToolMenu* ToolbarMenu) const;
};
