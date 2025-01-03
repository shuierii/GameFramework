#include "EventAsset/EventAssetEditor.h"

#include "EdGraphUtilities.h"
#include "EventAsset.h"
#include "EventEditorCommands.h"
#include "GraphEditorActions.h"
#include "ToolMenus.h"
#include "Framework/Commands/GenericCommands.h"
#include "Graph/EventGraphSchema.h"
#include "..\..\Public\Graph\Node\EdGraphNode_Base.h"
#include "Kismet2/BlueprintEditorUtils.h"

#define LOCTEXT_NAMESPACE "FEventAssetEditor"

const FName FEventAssetEditor::GraphTab = FName(TEXT("Graph"));
const FName FEventAssetEditor::DetailsTab = FName(TEXT("Details"));
const FName FEventAssetEditor::PaletteTab = FName(TEXT("Palette"));

void FEventAssetEditor::InitEventAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEditor)
{
	UE_LOG(LogTemp, Log, TEXT("初始化编辑器"));

	EventAsset = CastChecked<UEventAsset>(ObjectToEditor);

	// 注册引脚连接委托
	UEventGraphSchema::OnPinConnection.BindSP(this, &FEventAssetEditor::OnPinConnectionFunc);

	// 创建编辑器界面
	CreateWidgets();

	// 绑定指令
	UEventGraphSchema::BindAssetChangeActions();

	// 绑定复制删除等指令
	BindGraphCommands();

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

TSet<UEdGraphNode_Base*> FEventAssetEditor::GetSelectedEventNodes() const
{
	TSet<UEdGraphNode_Base*> Result;

	const FGraphPanelSelectionSet SelectedNodes = FocusedGraphEditor->GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
	{
		if (UEdGraphNode_Base* SelectedNode = Cast<UEdGraphNode_Base>(*NodeIt))
		{
			Result.Emplace(SelectedNode);
		}
	}

	return Result;
}

void FEventAssetEditor::CreateWidgets()
{
	// 图标编辑面板
	FocusedGraphEditor = CreateGraphWidget();

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

	// 绑定事件
	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FEventAssetEditor::OnNodeDoubleClicked);
	InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &FEventAssetEditor::OnNodeTitleCommitted);

	UE_LOG(LogTemp, Log, TEXT("绑定编辑器事件"));

	return SNew(SGraphEditor)
	.AdditionalCommands(ToolkitCommands)
	.IsEditable(true)
	.Appearance(AppearanceInfo)
	.GraphToEdit(EventAsset->GetGraph())
	.GraphEvents(InEvents)
	.AutoExpandActionMenu(true)
	.ShowGraphStateOverlay(false);
}

void FEventAssetEditor::BindGraphCommands()
{
	FGraphEditorCommands::Register();
	FEventGraphCommands::Register();

	const FGenericCommands& GenericCommands = FGenericCommands::Get();
	const FGraphEditorCommandsImpl& GraphEditorCommands = FGraphEditorCommands::Get();
	const FEventGraphCommands& EventGraphCommands = FEventGraphCommands::Get();

	ToolkitCommands->MapAction(GenericCommands.SelectAll,
	                           FExecuteAction::CreateSP(this, &FEventAssetEditor::SelectAllNodes),
	                           FCanExecuteAction::CreateSP(this, &FEventAssetEditor::CanSelectAllNodes));

	ToolkitCommands->MapAction(GenericCommands.Delete,
	                           FExecuteAction::CreateSP(this, &FEventAssetEditor::DeleteSelectedNodes),
	                           FCanExecuteAction::CreateSP(this, &FEventAssetEditor::CanDeleteNodes));

	ToolkitCommands->MapAction(GenericCommands.Copy,
	                           FExecuteAction::CreateSP(this, &FEventAssetEditor::CopySelectedNodes),
	                           FCanExecuteAction::CreateSP(this, &FEventAssetEditor::CanCopyNodes));

	ToolkitCommands->MapAction(GenericCommands.Cut,
	                           FExecuteAction::CreateSP(this, &FEventAssetEditor::CutSelectedNodes),
	                           FCanExecuteAction::CreateSP(this, &FEventAssetEditor::CanCutNodes));

	ToolkitCommands->MapAction(GenericCommands.Paste,
	                           FExecuteAction::CreateSP(this, &FEventAssetEditor::PasteNodes),
	                           FCanExecuteAction::CreateSP(this, &FEventAssetEditor::CanPasteNodes));

	ToolkitCommands->MapAction(GenericCommands.Duplicate,
	                           FExecuteAction::CreateSP(this, &FEventAssetEditor::DuplicateNodes),
	                           FCanExecuteAction::CreateSP(this, &FEventAssetEditor::CanDuplicateNodes));

	// Jump commands
	ToolkitCommands->MapAction(EventGraphCommands.JumpToNodeDefinition,
	                           FExecuteAction::CreateSP(this, &FEventAssetEditor::JumpToNodeDefinition),
	                           FCanExecuteAction::CreateSP(this, &FEventAssetEditor::CanJumpToNodeDefinition));

	UE_LOG(LogTemp, Log, TEXT("注册节点操作指令"));
}

void FEventAssetEditor::OnPinConnectionFunc(UEdGraphPin* A, UEdGraphPin* B)
{
}

void FEventAssetEditor::OnNodeDoubleClicked(UEdGraphNode* Node)
{
	UEventNode_Base* EventNode = Cast<UEdGraphNode_Base>(Node)->GetEventNode();

	if (EventNode)
	{
		Node->JumpToDefinition();
	}
}

void FEventAssetEditor::OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged)
{
	if (NodeBeingChanged)
	{
		const FScopedTransaction Transaction(LOCTEXT("RenameNode", "Rename Node"));
		NodeBeingChanged->Modify();
		NodeBeingChanged->OnRenameNode(NewText.ToString());
	}
}

bool FEventAssetEditor::CanSelectAllNodes() const
{
	return true;
}

void FEventAssetEditor::SelectAllNodes() const
{
	FocusedGraphEditor->SelectAllNodes();
}

bool FEventAssetEditor::CanDeleteNodes() const
{
	const FGraphPanelSelectionSet SelectedNodes = FocusedGraphEditor->GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
	{
		if (const UEdGraphNode* Node = Cast<UEdGraphNode>(*NodeIt))
		{
			if (!Node->CanUserDeleteNode())
			{
				return false;
			}
		}
	}

	return SelectedNodes.Num() > 0;
}

void FEventAssetEditor::DeleteSelectedNodes()
{
	const FScopedTransaction Transaction(LOCTEXT("DeleteSelectedNode", "Delete Selected Node"));
	FocusedGraphEditor->GetCurrentGraph()->Modify(); // 标记图表为修改状态
	EventAsset->Modify(); // 标记资产为修改状态

	const FGraphPanelSelectionSet SelectedNodes = FocusedGraphEditor->GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
	{
		UEdGraphNode* GraphNode = CastChecked<UEdGraphNode>(*NodeIt);

		if (GraphNode->CanUserDeleteNode())
		{
			if (const UEdGraphNode_Base* EventEdGraphNode = Cast<UEdGraphNode_Base>(GraphNode))
			{
				if (UEventNode_Base* EventNode = EventEdGraphNode->GetEventNode())
				{
					// TODO

					FBlueprintEditorUtils::RemoveNode(nullptr, GraphNode, true);
					continue;
				}
			}

			FBlueprintEditorUtils::RemoveNode(nullptr, GraphNode, true);
		}
	}
}

void FEventAssetEditor::DeleteSelectedDuplicableNodes()
{
	// Cache off the old selection
	const FGraphPanelSelectionSet OldSelectedNodes = FocusedGraphEditor->GetSelectedNodes();

	// Clear the selection and only select the nodes that can be duplicated
	FGraphPanelSelectionSet RemainingNodes;
	FocusedGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator SelectedIt(OldSelectedNodes); SelectedIt; ++SelectedIt)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIt))
		{
			if (Node->CanDuplicateNode())
			{
				FocusedGraphEditor->SetNodeSelection(Node, true);
			}
			else
			{
				RemainingNodes.Add(Node);
			}
		}
	}

	// Delete the duplicable nodes
	DeleteSelectedNodes();

	for (FGraphPanelSelectionSet::TConstIterator SelectedIt(RemainingNodes); SelectedIt; ++SelectedIt)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIt))
		{
			FocusedGraphEditor->SetNodeSelection(Node, true);
		}
	}
}

bool FEventAssetEditor::CanCopyNodes() const
{
	const FGraphPanelSelectionSet SelectedNodes = FocusedGraphEditor->GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator SelectedIt(SelectedNodes); SelectedIt; ++SelectedIt)
	{
		const UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIt);
		if (Node && Node->CanDuplicateNode())
		{
			return true;
		}
	}

	return false;
}

void FEventAssetEditor::CopySelectedNodes() const
{
}

bool FEventAssetEditor::CanCutNodes() const
{
	return true;
}

void FEventAssetEditor::CutSelectedNodes()
{
}

bool FEventAssetEditor::CanPasteNodes() const
{
	return true;
}

void FEventAssetEditor::PasteNodes()
{
}

bool FEventAssetEditor::CanDuplicateNodes() const
{
	return true;
}

void FEventAssetEditor::DuplicateNodes()
{
}

bool FEventAssetEditor::CanJumpToNodeDefinition() const
{
	return GetSelectedEventNodes().Num() == 1;
}

void FEventAssetEditor::JumpToNodeDefinition() const
{
	for (const UEdGraphNode_Base* SelectedNode : GetSelectedEventNodes())
	{
		SelectedNode->JumpToDefinition();
		return;
	}
}

TSharedRef<SDockTab> FEventAssetEditor::SpawnTab_Details(const FSpawnTabArgs& Args) const
{
	check(Args.GetTabId() == DetailsTab);

	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("LevelEditor.Tabs.Details"))
		.Label(LOCTEXT("EventDetailsTitle", "细节"))
	[
		DetailsView.ToSharedRef()
	];
}

TSharedRef<SDockTab> FEventAssetEditor::SpawnTab_GraphCanvas(const FSpawnTabArgs& Args) const
{
	check(Args.GetTabId() == GraphTab);

	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.Label(LOCTEXT("EventGraphTitle", "图表"));

	if (FocusedGraphEditor.IsValid())
	{
		SpawnedTab->SetContent(FocusedGraphEditor.ToSharedRef());
	}

	return SpawnedTab;
}

TSharedRef<SDockTab> FEventAssetEditor::SpawnTab_Palette(const FSpawnTabArgs& Args) const
{
	check(Args.GetTabId() == PaletteTab);

	return SNew(SDockTab)
	.Icon(FEditorStyle::GetBrush("Kismet.Tabs.Palette"))
	.Label(LOCTEXT("EventPaletteTitle", "节点列表"));
	// TODO
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

	InTabManager->RegisterTabSpawner(GraphTab, FOnSpawnTab::CreateSP(this, &FEventAssetEditor::SpawnTab_GraphCanvas))
	            .SetDisplayName(LOCTEXT("GraphTab", "图表"))
	            .SetGroup(WorkspaceMenuCategoryRef)
	            .SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "GraphEditor.EventGraph_16x"));

	InTabManager->RegisterTabSpawner(DetailsTab, FOnSpawnTab::CreateSP(this, &FEventAssetEditor::SpawnTab_Details))
	            .SetDisplayName(LOCTEXT("DetailsTab", "细节"))
	            .SetGroup(WorkspaceMenuCategoryRef)
	            .SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner(PaletteTab, FOnSpawnTab::CreateSP(this, &FEventAssetEditor::SpawnTab_Palette))
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
