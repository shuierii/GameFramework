#include "Graph/Widget/EventPalette.h"

#include "Graph/EventGraphSchema.h"
#include "Widgets/Input/STextComboBox.h"

void SEventPaletteItem::Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateWidgetForActionData)
{
	const FSlateFontInfo NameFont = FCoreStyle::GetDefaultFontStyle("Regular", 10);

	check(InCreateWidgetForActionData->Action.IsValid())

	const TSharedPtr<FEdGraphSchemaAction> GraphSchemaAction = InCreateWidgetForActionData->Action;
	ActionPtr = InCreateWidgetForActionData->Action;

	TSharedPtr<const FInputChord> HotkeyChord;
	const FSlateBrush* IconBrush = FEditorStyle::GetBrush(TEXT("NoBrush"));
	const FSlateColor IconColor = FSlateColor::UseForeground();
	const FText IconToolTip = GraphSchemaAction->GetTooltipDescription();
	constexpr bool bIsReadOnly = false;

	const TSharedRef<SWidget> IconWidget = CreateIconWidget(IconToolTip, IconBrush, IconColor);
	const TSharedRef<SWidget> NameSlotWidget = CreateTextSlotWidget(NameFont, InCreateWidgetForActionData, bIsReadOnly);
	const TSharedRef<SWidget> HotkeyDisplayWidget = CreateHotkeyDisplayWidget(NameFont, HotkeyChord);

	ChildSlot[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			IconWidget
		]
		+ SHorizontalBox::Slot()
		  .FillWidth(1.f)
		  .VAlign(VAlign_Center)
		  .Padding(3, 0)
		[
			NameSlotWidget
		]
		+ SHorizontalBox::Slot()
		  .AutoWidth()
		  .HAlign(HAlign_Right)
		[
			HotkeyDisplayWidget
		]
	];
}

TSharedRef<SWidget> SEventPaletteItem::CreateHotkeyDisplayWidget(const FSlateFontInfo& NameFont, const TSharedPtr<const FInputChord> HotkeyChord) const
{
	FText HotkeyText;
	if (HotkeyChord.IsValid())
	{
		HotkeyText = HotkeyChord->GetInputText();
	}

	return SNew(STextBlock)
		.Text(HotkeyText)
		.Font(NameFont);
}

void SEventPalette::Construct(const FArguments& InArgs, TWeakPtr<FEventAssetEditor> InEventAssetEditor)
{
	EventAssetEditorPtr = InEventAssetEditor;
	CategoryNames = {MakeShareable(new FString(TEXT("全部")))};
	CategoryNames.Append(UEventGraphSchema::GetEventNodeCategories());

	// 监听刷新
	UEventGraphSchema::OnNodeListChanged.AddSP(this, &SEventPalette::Refresh);

	ChildSlot
	[
		SNew(SBorder)
		.Padding(2.0f)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot() // Filter UI
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				[
					SAssignNew(CategoryComboBox, STextComboBox)
					.OptionsSource(&CategoryNames)
					// .OnSelectionChanged(this,  ()[this] { RefreshActionsList(true); })
					.InitiallySelectedItem(CategoryNames[0])
				]
			]
			+ SVerticalBox::Slot() // Content list
			  .HAlign(HAlign_Fill)
			  .VAlign(VAlign_Fill)
			[
				SAssignNew(GraphActionMenu, SGraphActionMenu)
				.OnActionDragged(this, &SEventPalette::OnActionDragged)
				.OnActionSelected(this, &SEventPalette::OnActionSelected)
				.OnCreateWidgetForAction(this, &SEventPalette::OnCreateWidgetForAction)
				.OnCollectAllActions(this, &SEventPalette::CollectAllActions)
				.AutoExpandActionMenu(true)
			]
		]
	];
}

SEventPalette::~SEventPalette()
{
	UEventGraphSchema::OnNodeListChanged.RemoveAll(this);
}

void SEventPalette::CollectAllActions(FGraphActionListBuilderBase& OutAllActions)
{
	FGraphActionMenuBuilder ActionMenuBuilder;
	UEventGraphSchema::GetPaletteActions(ActionMenuBuilder);
	OutAllActions.Append(ActionMenuBuilder);
}

TSharedRef<SWidget> SEventPalette::OnCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData)
{
	return SNew(SEventPaletteItem, InCreateData);
}

void SEventPalette::OnActionSelected(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions, ESelectInfo::Type InSelectionType) const
{
	if (InSelectionType == ESelectInfo::OnMouseClick || InSelectionType == ESelectInfo::OnKeyPress || InSelectionType == ESelectInfo::OnNavigation || InActions.Num() == 0)
	{
		const TSharedPtr<FEventAssetEditor> EventAssetEditor = EventAssetEditorPtr.Pin();
		if (EventAssetEditor)
		{
			// EventAssetEditor->SetUISelectionState(FEventAssetEditor::PaletteTab);
		}
	}
}

void SEventPalette::Refresh()
{
	const FString LastSelectedCategory = CategoryComboBox->GetSelectedItem().IsValid() ? *CategoryComboBox->GetSelectedItem().Get() : FString();

	CategoryNames = {MakeShareable(new FString(TEXT("全部")))};
	CategoryNames.Append(UEventGraphSchema::GetEventNodeCategories());
	RefreshActionsList(true);

	// refresh list of category and currently selected category
	CategoryComboBox->RefreshOptions();
	TSharedPtr<FString> SelectedCategory = CategoryNames[0];
	if (!LastSelectedCategory.IsEmpty())
	{
		for (const TSharedPtr<FString>& CategoryName : CategoryNames)
		{
			if (*CategoryName.Get() == LastSelectedCategory)
			{
				SelectedCategory = CategoryName;
				break;
			}
		}
	}

	CategoryComboBox->SetSelectedItem(SelectedCategory);
}

FString SEventPalette::GetFilterCategoryName() const
{
	if (CategoryComboBox.IsValid() && CategoryComboBox->GetSelectedItem() != CategoryNames[0])
	{
		return *CategoryComboBox->GetSelectedItem();
	}

	return FString();
}
