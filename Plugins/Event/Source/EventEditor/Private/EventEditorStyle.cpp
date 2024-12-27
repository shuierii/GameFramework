#include "EventEditorStyle.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( StyleSet->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( StyleSet->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( StyleSet->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )

TSharedPtr<FSlateStyleSet> FEventEditorStyle::StyleSet = nullptr;

void FEventEditorStyle::Initialize()
{
	StyleSet = MakeShareable(new FSlateStyleSet(TEXT("EventEditorStyle")));

	const FVector2D Icon16(16.0f, 16.0f);
	const FVector2D Icon20(20.0f, 20.0f);
	const FVector2D Icon40(40.0f, 40.0f);
	const FVector2D Icon64(64.0f, 64.0f);

	// engine assets
	StyleSet->SetContentRoot(FPaths::EngineContentDir() / TEXT("Editor/Slate/"));

	StyleSet->Set("EventToolbar.RefreshAsset", new IMAGE_BRUSH("Automation/RefreshTests", Icon40));
	StyleSet->Set("EventToolbar.RefreshAsset.Small", new IMAGE_BRUSH("Automation/RefreshTests", Icon20));
	StyleSet->Set("EventToolbar.ExportData", new IMAGE_BRUSH("Icons/icon_FontEd_Export_40x", Icon40));
	StyleSet->Set("EventToolbar.ExportData.Small", new IMAGE_BRUSH("Icons/icon_FontEd_Export_40x", Icon20));
	StyleSet->Set("EventToolbar.RefreshTables", new IMAGE_BRUSH("Automation/RefreshTests", Icon40));
	StyleSet->Set("EventToolbar.RefreshTables.Small", new IMAGE_BRUSH("Automation/RefreshTests", Icon20));

	StyleSet->Set("RefreshTablesToolbar.RefreshTables", new IMAGE_BRUSH("Automation/RefreshTests", Icon40));
	StyleSet->Set("RefreshTablesToolbar.RefreshTables.Small", new IMAGE_BRUSH("Automation/RefreshTests", Icon20));

	StyleSet->Set("DialogFlowToolbar.RefreshAsset", new IMAGE_BRUSH("Automation/RefreshTests", Icon40));
	StyleSet->Set("DialogFlowToolbar.RefreshAsset.Small", new IMAGE_BRUSH("Automation/RefreshTests", Icon20));
	StyleSet->Set("DialogFlowToolbar.RefreshTables", new IMAGE_BRUSH("Automation/RefreshTests", Icon40));
	StyleSet->Set("DialogFlowToolbar.RefreshTables.Small", new IMAGE_BRUSH("Automation/RefreshTests", Icon20));
	StyleSet->Set("DialogFlowToolbar.ExportData", new IMAGE_BRUSH("Icons/icon_FontEd_Export_40x", Icon40));
	StyleSet->Set("DialogFlowToolbar.ExportData.Small", new IMAGE_BRUSH("Icons/icon_FontEd_Export_40x", Icon20));
	StyleSet->Set("DialogFlowToolbar.OpenEventAsset", new IMAGE_BRUSH("Icons/icon_FontEd_Export_40x", Icon40));
	StyleSet->Set("DialogFlowToolbar.OpenEventAsset.Small", new IMAGE_BRUSH("Icons/icon_FontEd_Export_40x", Icon20));

	// event assets
	StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin(TEXT("Event"))->GetBaseDir() / TEXT("Resources"));

	StyleSet->Set("ClassIcon.EventAsset", new IMAGE_BRUSH(TEXT("Icons/EventAsset_16x"), Icon16));
	StyleSet->Set("ClassThumbnail.EventAsset", new IMAGE_BRUSH(TEXT("Icons/EventAsset_64x"), Icon64));

	StyleSet->Set("Event.Node.Title", new BOX_BRUSH("Icons/EventNode_Title", FMargin(8.0f / 64.0f, 0, 0, 0)));
	StyleSet->Set("Event.Node.Desc", new BOX_BRUSH("Icons/CommonButton_16x", FMargin(16.f / 64.f)));
	StyleSet->Set("Event.Node.Body", new BOX_BRUSH("Icons/EventNode_Body", FMargin(16.f / 64.f)));

	StyleSet->Set("EventToolbar.ModExportData", new IMAGE_BRUSH("Icons/ModExport_40x", Icon40));

	const FButtonStyle CommonButtonStyle = FButtonStyle()
	                                       .SetNormal(BOX_BRUSH("Icons/CommonButton_16x", 4.0f / 16.0f))
	                                       .SetHovered(BOX_BRUSH("Icons/CommonButton_16x", 4.0f / 16.0f))
	                                       .SetPressed(BOX_BRUSH("Icons/CommonButton_16x", 4.0f / 16.0f));
	StyleSet->Set("CommonButton", CommonButtonStyle);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void FEventEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
	StyleSet.Reset();
}

FName FEventEditorStyle::GetStyleSetName()
{
	static FName EventEditorStyleName(TEXT("EventEditorStyle"));

	return EventEditorStyleName;
}
