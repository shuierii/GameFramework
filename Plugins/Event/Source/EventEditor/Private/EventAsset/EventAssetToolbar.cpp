#include "EventAsset/EventAssetToolbar.h"
#include "ToolMenu.h"
#include "EventEditorCommands.h"
#include "ToolMenuEntry.h"

FEventAssetToolbar::FEventAssetToolbar(UToolMenu* ToolMenu)
{
	BuildAssetToolbar(ToolMenu);
}

void FEventAssetToolbar::BuildAssetToolbar(UToolMenu* ToolbarMenu) const
{
	FToolMenuSection& Section = ToolbarMenu->AddSection("Event Editing");
	Section.InsertPosition = FToolMenuInsert("Asset", EToolMenuInsertType::After);

	Section.AddEntry(FToolMenuEntry::InitToolBarButton(FEventToolbarCommands::Get().ExportData));
}
