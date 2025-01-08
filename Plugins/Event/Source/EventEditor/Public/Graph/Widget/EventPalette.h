#pragma once
#include "SGraphPalette.h"
#include "EventAsset/EventAssetEditor.h"

class FEventAssetEditor;

class EVENTEDITOR_API SEventPaletteItem : public SGraphPaletteItem
{
public:
	SLATE_BEGIN_ARGS(SEventPaletteItem)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateWidgetForActionData);

private:
	TSharedRef<SWidget> CreateHotkeyDisplayWidget(const FSlateFontInfo& NameFont, const TSharedPtr<const FInputChord> HotkeyChord) const;
};

class EVENTEDITOR_API SEventPalette : public SGraphPalette
{
public:
	SLATE_BEGIN_ARGS(SEventPalette)
		{
		}

	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs, TWeakPtr<FEventAssetEditor> InEventAssetEditor);
	virtual ~SEventPalette() override;

protected:
	// SGraphPalette
	virtual void CollectAllActions(FGraphActionListBuilderBase& OutAllActions) override;
	virtual TSharedRef<SWidget> OnCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData) override;
	// END
private:
	void OnActionSelected(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions, ESelectInfo::Type InSelectionType) const;
	void Refresh();
	FString GetFilterCategoryName() const;

private:
	TWeakPtr<FEventAssetEditor> EventAssetEditorPtr;
	TArray<TSharedPtr<FString>> CategoryNames;
	TSharedPtr<STextComboBox> CategoryComboBox;
};
