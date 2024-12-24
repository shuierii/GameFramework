#include "EventAsset/EventAssetEditor.h"

#include "EventAsset.h"
#include "ToolMenus.h"

#define LOCTEXT_NAMESPACE "FEventAssetEditor"

const FName FEventAssetEditor::GraphTab = FName(TEXT("Graph"));
const FName FEventAssetEditor::DetailsTab = FName(TEXT("Details"));
const FName FEventAssetEditor::PaletteTab = FName(TEXT("Palette"));

void FEventAssetEditor::InitEventAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEditor)
{
	EventAsset = CastChecked<UEventAsset>(ObjectToEditor);

	// 创建编辑器界面
	CreateWidgets();

	// 绑定指令


	// 工具栏
	CreateToolbar();

	// 绘制内容分块
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("EventAssetEditor_Layout_v2")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			                             ->Split
			                             (
				                             // Toolbar
				                             FTabManager::NewStack()
				                             ->SetSizeCoefficient(0.1f)
				                             ->AddTab(GetToolbarTabId(), ETabState::OpenedTab)->SetHideTabWell(true)
			                             )
			                             ->Split
			                             (
				                             FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)->SetSizeCoefficient(0.9f)
				                                                       ->Split
				                                                       (
					                                                       // Details
					                                                       FTabManager::NewStack()
					                                                       ->SetSizeCoefficient(0.125f)
					                                                       ->AddTab(DetailsTab, ETabState::OpenedTab)
				                                                       )
				                                                       ->Split
				                                                       (
					                                                       // Graph
					                                                       FTabManager::NewStack()
					                                                       ->SetSizeCoefficient(0.75f)
					                                                       ->AddTab(GraphTab, ETabState::OpenedTab)->SetHideTabWell(true)
				                                                       )
				                                                       ->Split
				                                                       (
					                                                       // Palette
					                                                       FTabManager::NewStack()
					                                                       ->SetSizeCoefficient(0.125f)
					                                                       ->AddTab(PaletteTab, ETabState::OpenedTab)
				                                                       )
			                             )
		);

	// 关键步骤
	InitAssetEditor(Mode, InitToolkitHost,TEXT("EventEditorApp"), StandaloneDefaultLayout, true, true, ObjectToEditor, false);

	RegenerateMenusAndToolbars();
}

void FEventAssetEditor::CreateWidgets()
{
	// 图标编辑面板
	CreateGraphWidget();

	// 细节面板
	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;
	Args.bShowPropertyMatrixButton = false;
	Args.DefaultsOnlyVisibility = EEditDefaultsOnlyNodeVisibility::Hide;

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	DetailsView = PropertyEditorModule.CreateDetailView(Args);
	DetailsView->SetIsPropertyEditingEnabledDelegate(FIsPropertyEditingEnabled::CreateLambda([]() { return true; }));
	DetailsView->SetObject(EventAsset);

	// 节点列表
	// TODO
}

void FEventAssetEditor::CreateToolbar()
{
	FName ParentToolbarName;
	const FName ToolbarName = GetToolMenuToolbarName(ParentToolbarName);

	UToolMenus* ToolMenus = UToolMenus::Get();
	UToolMenu* ToolMenu = ToolMenus->FindMenu(ToolbarName);
	if (!ToolMenu || !ToolMenu->IsRegistered())
	{
		ToolMenu = ToolMenus->RegisterMenu(ToolbarName, ParentToolbarName, EMultiBoxType::ToolBar);
	}

	if (ToolMenu)
	{
		// TODO
	}
}

TSharedRef<SGraphEditor> FEventAssetEditor::CreateGraphWidget()
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText_EventAsset", "Event");

	// TODO

	return SNew(SGraphEditor)
	.AdditionalCommands(ToolkitCommands)
	.IsEditable(true)
	.Appearance(AppearanceInfo)
	.GraphToEdit(EventAsset->GetGraph())
	.AutoExpandActionMenu(true)
	.ShowGraphStateOverlay(false);
}

void FEventAssetEditor::BindGraphCommands()
{
}

FEventAssetEditor::FEventAssetEditor(): EventAsset(nullptr)
{
}

FEventAssetEditor::~FEventAssetEditor()
{
}

FName FEventAssetEditor::GetToolkitFName() const
{
	return FName("EventEditor");
}

FText FEventAssetEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "EventAsset Editor");
}

FString FEventAssetEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "EventAsset").ToString();
}

FLinearColor FEventAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

void FEventAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_EventAssetEditor", "Event Editor"));
	const auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	InTabManager->RegisterTabSpawner(GraphTab, FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& Args)
	            {
		            return SNew(SDockTab).Label(LOCTEXT("EventGraphTitle", "图表"));
	            }))
	            .SetDisplayName(LOCTEXT("GraphTab", "图表"))
	            .SetGroup(WorkspaceMenuCategoryRef)
	            .SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "GraphEditor.EventGraph_16x"));

	InTabManager->RegisterTabSpawner(DetailsTab, FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& Args)
	            {
		            return SNew(SDockTab)
							.Icon(FEditorStyle::GetBrush("LevelEditor.Tabs.Details"))
							.Label(LOCTEXT("EventDetailsTitle", "细节"))
							[
								DetailsView.ToSharedRef()
							];
	            }))
	            .SetDisplayName(LOCTEXT("DetailsTab", "细节"))
	            .SetGroup(WorkspaceMenuCategoryRef)
	            .SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner(PaletteTab, FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& Args)
	            {
		            return SNew(SDockTab)
							.Icon(FEditorStyle::GetBrush("Kismet.Tabs.Palette"))
							.Label(LOCTEXT("EventPaletteTitle", "节点列表"));
	            }))
	            .SetDisplayName(LOCTEXT("PaletteTab", "节点列表"))
	            .SetGroup(WorkspaceMenuCategoryRef)
	            .SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "Kismet.Tabs.Palette"));
}

void FEventAssetEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(GraphTab);
	InTabManager->UnregisterTabSpawner(DetailsTab);
	InTabManager->UnregisterTabSpawner(PaletteTab);
}

#undef LOCTEXT_NAMESPACE
