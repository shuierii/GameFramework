#include "EventAsset/EventAssetEditor.h"

#include <string>

#include "EdGraphUtilities.h"
#include "EventAsset.h"
#include "EventEditorCommands.h"
#include "GraphEditAction.h"
#include "GraphEditorActions.h"
#include "ToolMenus.h"
#include "Framework/Commands/GenericCommands.h"
#include "Graph/EventGraphSchema.h"
#include "..\..\Public\Graph\Node\EdGraphNode_Base.h"
#include "Graph/Node/EdGraphNode_Dialog.h"
#include "Graph/Node/EdGraphNode_DialogEvent.h"
#include "Graph/Node/EdGraphNode_Script.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Misc/FileHelper.h"
#include "Node/EventNode_Action.h"
#include "Node/EventNode_Dialog.h"
#include "Node/EventNode_DialogEvent.h"
#include "Node/EventNode_Input.h"
#include "Node/EventNode_Output.h"
#include "Node/EventNode_Precondition.h"
#include "Node/EventNode_Script.h"
#include "Node/EventNode_Trigger.h"
#include "Value/NIArray.h"
#include "Value/NIInt.h"
#include "Value/NIString.h"
#include "Value/NIUtility.h"
#include "Widgets/Notifications/SNotificationList.h"

#define LOCTEXT_NAMESPACE "FEventAssetEditor"

const FName FEventAssetEditor::GraphTab = FName(TEXT("Graph"));
const FName FEventAssetEditor::DetailsTab = FName(TEXT("Details"));
const FName FEventAssetEditor::PaletteTab = FName(TEXT("Palette"));

void FEventAssetEditor::InitEventAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEditor)
{
	UE_LOG(LogTemp, Log, TEXT("初始化编辑器"));

	EventAsset = CastChecked<UEventAsset>(ObjectToEditor);

	// TIPS提示
	EventAsset->OnGraphEditorNotification.BindSP(this, &FEventAssetEditor::OnGraphEditorNotification);

	// 注册引脚连接委托
	UEventGraphSchema::OnPinConnection.BindSP(this, &FEventAssetEditor::OnPinConnectionFunc);

	// 创建编辑器界面
	CreateWidgets();

	// 绑定指令
	UEventGraphSchema::BindAssetChangeActions();

	// 绑定复制删除等指令
	BindGraphCommands();

	// 工具栏
	BindToolbarCommands();
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
		EventToolbar = MakeShareable(new FEventAssetToolbar(ToolMenu));
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

void FEventAssetEditor::BindToolbarCommands()
{
	FEventToolbarCommands::Register();
	const FEventToolbarCommands& ToolbarCommands = FEventToolbarCommands::Get();

	// ExportData
	ToolkitCommands->MapAction(ToolbarCommands.ExportData, FExecuteAction::CreateSP(this,
	                                                                                &FEventAssetEditor::OnExportData));
}

void FEventAssetEditor::OnExportData()
{
	FEdGraphEditAction Action;
	CollectEvent(Action);

	FAssetEditorToolkit::SaveAsset_Execute(); // 执行工具栏保存按钮操作

	TArray<FNotificationInfo> MsgList;
	bool Ret = ExportData(MsgList);
	for (auto Msg : MsgList)
	{
		FocusedGraphEditor->AddNotification(Msg, Ret);
	}
}

void FEventAssetEditor::CollectEvent(const FEdGraphEditAction& Action)
{
	if (EventAsset == nullptr || EventAsset->Root == nullptr)
	{
		return;
	}

	UEdGraphNode_Base* UEdGraphNode_Root = CastChecked<UEdGraphNode_Base>(EventAsset->Root->GetEdGraphNode());
	if (UEdGraphNode_Root == nullptr)
	{
		return;
	}

	// 节点数据重置
	for (auto EdGraphNode : EventAsset->GetGraph()->Nodes)
	{
		if (EdGraphNode == nullptr)
		{
			continue;
		}

		auto EventEdGraphNode = Cast<UEdGraphNode_Base>(EdGraphNode);
		if (EventEdGraphNode == nullptr || EventEdGraphNode->EventNode == nullptr)
		{
			continue;
		}

		EventEdGraphNode->EventNode->ResetConnectData();
	}

	// collect
	CollectNode(UEdGraphNode_Root);
}

void FEventAssetEditor::CollectNode(UEdGraphNode_Base* EdGraphNode)
{
	if (EdGraphNode == nullptr || EdGraphNode->EventNode == nullptr)
	{
		return;
	}

	for (auto Pin : EdGraphNode->Pins)
	{
		if (Pin == nullptr)
		{
			continue;
		}

		UEdGraphNode_Base* ConnectEdGraphNode = GetConnectEdGraphNode(Pin);
		if (ConnectEdGraphNode == nullptr)
		{
			continue;
		}

		// 共有部分
		if (Pin->Direction == EGPD_Input && Pin->PinType.PinSubCategory.IsEqual(FEventNodeTypes::PIN_SUB_TYPE_PUBLIC))
		{
			// Input
			if (ConnectEdGraphNode->EventNode->GetClass()->IsChildOf(UEventNode_Input::StaticClass()))
			{
				// 确认 EventNode 的父子关系 EdGraph携带的是父 Pin连线的是子
				// 子
				UEventNode_Input* EventNode_Input = CastChecked<UEventNode_Input>(ConnectEdGraphNode->EventNode);
				EdGraphNode->EventNode->InputList.Add(EventNode_Input);
				ConnectEdGraphNode->EventNode->Parent = EdGraphNode->EventNode;

				CollectNode(ConnectEdGraphNode);
			}
			else
			{
				continue;
			}
		}
		else if (Pin->Direction == EGPD_Output && Pin->PinType.PinSubCategory.IsEqual(FEventNodeTypes::PIN_SUB_TYPE_PUBLIC))
		{
			// Precondition
			if (ConnectEdGraphNode->EventNode->GetClass()->IsChildOf(UEventNode_Precondition::StaticClass()))
			{
				// 确认 EventNode 的父子关系 EdGraph携带的是父 Pin连线的是子
				// 子
				UEventNode_Precondition* EventNode_Precondition = CastChecked<UEventNode_Precondition>(ConnectEdGraphNode->EventNode);
				EdGraphNode->EventNode->Precondition = EventNode_Precondition;
				ConnectEdGraphNode->EventNode->Parent = EdGraphNode->EventNode;

				CollectNode(ConnectEdGraphNode);
			}

			// Output
			else if (ConnectEdGraphNode->EventNode->GetClass()->IsChildOf(UEventNode_Output::StaticClass()))
			{
				// 确认 EventNode 的父子关系 EdGraph携带的是父 Pin连线的是子
				// 子
				UEventNode_Output* EventNode_Output = CastChecked<UEventNode_Output>(ConnectEdGraphNode->EventNode);
				EdGraphNode->EventNode->OutputList.Add(EventNode_Output);
				ConnectEdGraphNode->EventNode->Parent = EdGraphNode->EventNode;

				CollectNode(ConnectEdGraphNode);
			}
			else
			{
				continue;
			}
		}

		// 私有部分
		// DialogEvent
		if (EdGraphNode->GetClass()->IsChildOf(UEdGraphNode_DialogEvent::StaticClass()))
		{
			// 确认 EventNode 的父子关系 EdGraph携带的是父 Pin连线的是子
			// 父
			UEventNode_DialogEvent* EventNode_DialogEvent = CastChecked<UEventNode_DialogEvent>(EdGraphNode->EventNode);

			// TriggerList
			if (Pin->PinType.PinCategory.IsEqual(FEventNodeTypes::NODE_TYPE_TRIGGER))
			{
				UEventNode_Trigger* EventNode_Trigger = CastChecked<UEventNode_Trigger>(ConnectEdGraphNode->EventNode);
				EventNode_DialogEvent->TriggerList.Add(EventNode_Trigger);
			}
			// ScriptList
			else if (Pin->PinType.PinCategory.IsEqual(FEventNodeTypes::NODE_TYPE_SCRIPT))
			{
				UEventNode_Script* EventNode_Script = CastChecked<UEventNode_Script>(ConnectEdGraphNode->EventNode);
				EventNode_DialogEvent->ScriptList.Add(EventNode_Script);
			}
			else
			{
				continue;
			}

			ConnectEdGraphNode->EventNode->Parent = EventNode_DialogEvent;

			CollectNode(ConnectEdGraphNode);
		}
		// Script
		else if (EdGraphNode->GetClass()->IsChildOf(UEdGraphNode_Script::StaticClass()))
		{
			// 确认 EventNode 的父子关系 EdGraph携带的是父 Pin连线的是子
			// 父
			UEventNode_Script* EventNode_Script = CastChecked<UEventNode_Script>(EdGraphNode->EventNode);

			// Action
			if (Pin->PinType.PinCategory.IsEqual(FEventNodeTypes::NODE_TYPE_ACTION))
			{
				UEventNode_Action* EventNode_Action = CastChecked<UEventNode_Action>(ConnectEdGraphNode->EventNode);
				EventNode_Script->ActionOfStartScript = EventNode_Action;
			}
			// Dialog
			else if (Pin->PinType.PinCategory.IsEqual(FEventNodeTypes::NODE_TYPE_DIALOG))
			{
				UEventNode_Dialog* EventNode_Dialog = CastChecked<UEventNode_Dialog>(ConnectEdGraphNode->EventNode);
				EventNode_Script->Dialog = EventNode_Dialog;
			}
			else
			{
				continue;
			}

			ConnectEdGraphNode->EventNode->Parent = EventNode_Script;

			CollectNode(ConnectEdGraphNode);
		}
		// Dialog
		else if (EdGraphNode->GetClass()->IsChildOf(UEdGraphNode_Dialog::StaticClass()))
		{
			// 确认 EventNode 的父子关系 EdGraph携带的是父 Pin连线的是子
			// 父
			UEventNode_Dialog* EventNode_Dialog = CastChecked<UEventNode_Dialog>(EdGraphNode->EventNode);

			ConnectEdGraphNode->EventNode->Parent = EventNode_Dialog;

			// Action-Enter
			if (Pin->PinType.PinCategory.IsEqual(FEventNodeTypes::PIN_DIALOG_ACTION_OF_ENTER))
			{
				UEventNode_Action* EventNode_Action = CastChecked<UEventNode_Action>(ConnectEdGraphNode->EventNode);
				EventNode_Dialog->ActionOfEnter = EventNode_Action;

				EventNode_Action->Parent = EventNode_Dialog;
				CollectNode(ConnectEdGraphNode);
			}
			// Action-Exit
			else if (Pin->PinType.PinCategory.IsEqual(FEventNodeTypes::PIN_DIALOG_ACTION_OF_EXIT))
			{
				UEventNode_Action* EventNode_Action = CastChecked<UEventNode_Action>(ConnectEdGraphNode->EventNode);
				EventNode_Dialog->ActionOfExit = EventNode_Action;

				EventNode_Action->Parent = EventNode_Dialog;
				CollectNode(ConnectEdGraphNode);
			}

			// option
			if (Pin->PinType.PinCategory.IsEqual(FEventNodeTypes::NODE_TYPE_DIALOG))
			{
				FDialogOption DialogOption;
				DialogOption.DialogText = EventNode_Dialog->GetOptionContent(Pin->PinId);
				EventNode_Dialog->DialogOptionList.Add(DialogOption);
			}
		}
	}
}

UEdGraphNode_Base* FEventAssetEditor::GetConnectEdGraphNode(UEdGraphPin* Pin)
{
	if (Pin->LinkedTo.Num() <= 0)
	{
		return nullptr;
	}

	if (Pin->LinkedTo.Num() != 1)
	{
		UE_LOG(LogTemp, Error, TEXT("the Pin->LinkedTo.Num() is unvalid."));

		return nullptr;
	}

	UEdGraphPin* ConnectPin = Pin->LinkedTo[0];
	if (ConnectPin == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("the TriggerOutPin is unvalid."));

		return nullptr;
	}

	UEdGraphNode_Base* ConnectEdGraphNode = CastChecked<UEdGraphNode_Base>(ConnectPin->GetOwningNode());
	if (ConnectEdGraphNode == nullptr || ConnectEdGraphNode->EventNode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("the ConnectEdGraphNode is unvalid."));

		return nullptr;
	}

	return ConnectEdGraphNode;
}

bool FEventAssetEditor::ExportData(TArray<FNotificationInfo>& MsgList)
{
	if (EventAsset == nullptr || EventAsset->Root == nullptr)
	{
		FNotificationInfo Info(LOCTEXT("ExportData_Root", "没有Root节点"));
		Info.bUseLargeFont = true;
		Info.ExpireDuration = 3.0f;

		MsgList.Add(Info);

		return false;
	}

	UEventNode_EventRoot* EventNode_Root = CastChecked<UEventNode_EventRoot>(EventAsset->Root);
	if (EventNode_Root == nullptr)
	{
		FNotificationInfo Info(LOCTEXT("ExportData_Root", "Root节点无效"));
		Info.bUseLargeFont = true;
		Info.ExpireDuration = 3.0f;

		MsgList.Add(Info);

		return false;
	}

	UNIMap* EventData = ExportData_Node(EventNode_Root, MsgList);
	if (EventData == nullptr)
	{
		return false;
	}

	// 数据转成json
	FString DataStr = UNIUtility::ConvertToString(EventData);
	if (DataStr.Len() <= 0)
	{
		FNotificationInfo Info(LOCTEXT("ExportData_To_Json", "转换json文件失败,存在格式不正确"));
		Info.bUseLargeFont = true;
		Info.ExpireDuration = 3.0f;

		MsgList.Add(Info);

		return false;
	}

	// 保存文件到路径
	// "../../../../Etc/Event/Event_1.json"
	FString FileName = EventAsset->GetName();
	FString FilePath = FPaths::ProjectContentDir() + "Etc/Event/" + FileName + ".json";

	if (!FFileHelper::SaveStringToFile(DataStr, *FilePath))
	{
		FNotificationInfo Info(FText::Format(LOCTEXT("ExportData_Save_File", "事件文件({0}) 存储失败."), FText::FromString(EventAsset->GetName())));
		Info.bUseLargeFont = true;
		Info.ExpireDuration = 3.0f;

		MsgList.Add(Info);

		return false;
	}

	FNotificationInfo Info(FText::Format(LOCTEXT("ExportData_Save_File", "事件文件({0}) 导出成功."), FText::FromString(EventAsset->GetName())));
	Info.bUseLargeFont = true;
	Info.ExpireDuration = 3.0f;

	MsgList.Add(Info);

	return true;
}

UNIMap* FEventAssetEditor::ExportData_Node(UEventNode_Base* Node, TArray<FNotificationInfo>& MsgList)
{
	if (Node == nullptr)
	{
		return nullptr;
	}

	UNIMap* NodeData = UNIValue::CreateMap();

	// type
	FString NodeType = Node->GetNodeType();
	if (NodeType.Len() <= 0)
	{
		FNotificationInfo Info(FText::Format(LOCTEXT("ExportData_Node_Type", "节点({0})： type 无效."), FText::FromString(Node->GetClass()->GetDisplayNameText().ToString())));
		Info.bUseLargeFont = true;
		Info.ExpireDuration = 3.0f;

		MsgList.Add(Info);

		return nullptr;
	}

	NodeData->AddBySKey("type", UNIValue::CreateString(NodeType));

	// field

	// properties

	// input_list
	UNIArray* InputDataList = UNIValue::CreateArray();
	for (auto ChildNode : Node->InputList)
	{
		if (ChildNode == nullptr)
		{
			FNotificationInfo Info(LOCTEXT("ExportData_Node_Input", "输入器无效"));
			Info.bUseLargeFont = true;
			Info.ExpireDuration = 3.0f;

			MsgList.Add(Info);

			return nullptr;
		}

		auto ChildNodeData = ExportData_Node(ChildNode, MsgList);
		if (ChildNodeData == nullptr)
		{
			FNotificationInfo Info(LOCTEXT("ExportData_Node_Input", "输入器导出失败"));
			Info.bUseLargeFont = true;
			Info.ExpireDuration = 3.0f;

			MsgList.Add(Info);

			return nullptr;
		}

		InputDataList->Add(ChildNodeData);
	}

	NodeData->AddBySKey("input_list", InputDataList);

	// precondition
	if (Node->Precondition)
	{
		auto PreconditionNodeData = ExportData_Node(Node->Precondition, MsgList);
		if (PreconditionNodeData == nullptr)
		{
			FNotificationInfo Info(FText::Format(LOCTEXT("ExportData_Node_Precondition", "节点({0})： 前置条件导出失败."), FText::FromString(Node->GetClass()->GetDisplayNameText().ToString())));
			Info.bUseLargeFont = true;
			Info.ExpireDuration = 3.0f;

			MsgList.Add(Info);

			return nullptr;
		}

		NodeData->AddBySKey("precondition", PreconditionNodeData);
	}

	// output_list
	UNIArray* OutputDataList = UNIValue::CreateArray();
	for (auto ChildNode : Node->OutputList)
	{
		if (ChildNode == nullptr)
		{
			FNotificationInfo Info(LOCTEXT("ExportData_Node_Output", "输出器无效"));
			Info.bUseLargeFont = true;
			Info.ExpireDuration = 3.0f;

			MsgList.Add(Info);

			return nullptr;
		}

		auto ChildNodeData = ExportData_Node(ChildNode, MsgList);
		if (ChildNodeData == nullptr)
		{
			FNotificationInfo Info(LOCTEXT("ExportData_Node_Output", "输出器导出失败"));
			Info.bUseLargeFont = true;
			Info.ExpireDuration = 3.0f;

			MsgList.Add(Info);

			return nullptr;
		}

		OutputDataList->Add(ChildNodeData);
	}

	NodeData->AddBySKey("output_list", OutputDataList);

	// Root
	if (Node->GetClass()->IsChildOf(UEventNode_EventRoot::StaticClass()))
	{
		UEventNode_EventRoot* EventNode_Root = CastChecked<UEventNode_EventRoot>(Node);

		// id
		FString NameStr;
		FString EventIDStr;
		EventAsset->GetName().Split(TEXT("_"), &NameStr, &EventIDStr);
		int32 EventID = FCString::Atoi(*EventIDStr);
		NodeData->AddBySKey("id", UNIValue::CreateInt(EventID));

		// trigger_list
		UNIArray* TriggerDataList = UNIValue::CreateArray();
		if (EventNode_Root->TriggerList.Num() > 0)
		{
			for (auto TriggerNode : EventNode_Root->TriggerList)
			{
				if (TriggerNode == nullptr)
				{
					continue;
				}

				auto TriggerNodeData = ExportData_Node(TriggerNode, MsgList);
				if (TriggerNodeData == nullptr)
				{
					FNotificationInfo Info(LOCTEXT("ExportData_Node_Trigger", "【触发器】数据导出失败"));
					Info.bUseLargeFont = true;
					Info.ExpireDuration = 3.0f;

					MsgList.Add(Info);

					return nullptr;
				}

				TriggerDataList->Add(TriggerNodeData);
			}

			NodeData->AddBySKey("trigger_list", TriggerDataList);
		}

		// dialog_event
		if (Node->GetClass()->IsChildOf(UEventNode_DialogEvent::StaticClass()))
		{
			UEventNode_DialogEvent* EventNode_DialogEvent = CastChecked<UEventNode_DialogEvent>(Node);
			// script_list
			UNIArray* ScriptDataList = UNIValue::CreateArray();
			if (EventNode_DialogEvent->ScriptList.Num() > 0)
			{
				for (auto ScriptNode : EventNode_DialogEvent->ScriptList)
				{
					if (ScriptNode == nullptr)
					{
						continue;
					}

					auto ScriptNodeData = ExportData_Node(ScriptNode, MsgList);
					if (ScriptNodeData == nullptr)
					{
						FNotificationInfo Info(LOCTEXT("ExportData_Node_Script", "【剧本】数据导出失败"));
						Info.bUseLargeFont = true;
						Info.ExpireDuration = 3.0f;

						MsgList.Add(Info);

						return nullptr;
					}

					ScriptDataList->Add(ScriptNodeData);
				}

				NodeData->AddBySKey("script_list", ScriptDataList);
			}
		}
	}
	else if (Node->GetClass()->IsChildOf(UEventNode_Input::StaticClass()))
	{
		UEventNode_Input* EventNode_Input = CastChecked<UEventNode_Input>(Node);

		// field
		if (EventNode_Input->Field.IsEmpty())
		{
			FNotificationInfo Info(LOCTEXT("ExportData_Node_Input", "【输入器】field是空的"));
			Info.bUseLargeFont = true;
			Info.ExpireDuration = 3.0f;

			MsgList.Add(Info);

			return nullptr;
		}

		NodeData->AddBySKey("field", UNIValue::CreateString(EventNode_Input->Field));
	}
	// Output
	else if (Node->GetClass()->IsChildOf(UEventNode_Output::StaticClass()))
	{
		UEventNode_Output* EventNode_Output = CastChecked<UEventNode_Output>(Node);

		// field
		if (EventNode_Output->Field.IsEmpty())
		{
			FNotificationInfo Info(LOCTEXT("ExportData_Node_Output", "【输出器】field是空的"));
			Info.bUseLargeFont = true;
			Info.ExpireDuration = 3.0f;

			MsgList.Add(Info);

			return nullptr;
		}

		NodeData->AddBySKey("field", UNIValue::CreateString(EventNode_Output->Field));
	}
	// Script
	else if (Node->GetClass()->IsChildOf(UEventNode_Script::StaticClass()))
	{
		UEventNode_Script* EventNode_Script = CastChecked<UEventNode_Script>(Node);

		// action_of_start_script
		if (EventNode_Script->ActionOfStartScript != nullptr)
		{
			auto ActionOfStartScriptData = ExportData_Node(EventNode_Script->ActionOfStartScript, MsgList);
			if (ActionOfStartScriptData == nullptr)
			{
				FNotificationInfo Info(LOCTEXT("ExportData_Node_Script", "【剧本】行动导出数据错误."));
				Info.bUseLargeFont = true;
				Info.ExpireDuration = 3.0f;

				MsgList.Add(Info);

				return nullptr;
			}

			NodeData->AddBySKey("action_of_start_script", ActionOfStartScriptData);
		}

		// dialog
		if (EventNode_Script->Dialog != nullptr)
		{
			auto DialogNodData = ExportData_Node(EventNode_Script->Dialog, MsgList);
			if (DialogNodData == nullptr)
			{
				FNotificationInfo Info(LOCTEXT("ExportData_Node_Script", "【对话】数据导出失败."));
				Info.bUseLargeFont = true;
				Info.ExpireDuration = 3.0f;

				MsgList.Add(Info);

				return nullptr;
			}

			NodeData->AddBySKey("dialog", DialogNodData);
		}
	}
	// Dialog
	else if (Node->GetClass()->IsChildOf(UEventNode_Dialog::StaticClass()))
	{
		UEventNode_Dialog* EventNode_Dialog = CastChecked<UEventNode_Dialog>(Node);

		// action_of_enter
		if (EventNode_Dialog->ActionOfEnter != nullptr)
		{
			auto ActionOfEnterData = ExportData_Node(EventNode_Dialog->ActionOfEnter, MsgList);
			if (ActionOfEnterData == nullptr)
			{
				FNotificationInfo Info(LOCTEXT("ExportData_Node_Dialog", "【对话】行动导出数据错误."));
				Info.bUseLargeFont = true;
				Info.ExpireDuration = 3.0f;

				MsgList.Add(Info);

				return nullptr;
			}

			NodeData->AddBySKey("action_of_enter", ActionOfEnterData);
		}

		// action_of_exit
		if (EventNode_Dialog->ActionOfExit != nullptr)
		{
			auto ActionOfExitData = ExportData_Node(EventNode_Dialog->ActionOfExit, MsgList);
			if (ActionOfExitData == nullptr)
			{
				FNotificationInfo Info(LOCTEXT("ExportData_Node_Dialog", "【对话】行动导出数据错误."));
				Info.bUseLargeFont = true;
				Info.ExpireDuration = 3.0f;

				MsgList.Add(Info);

				return nullptr;
			}

			NodeData->AddBySKey("action_of_exit", ActionOfExitData);
		}

		// option_list
		if (EventNode_Dialog->DialogOptionList.Num() > 0)
		{
		}
	}

	return NodeData;
}

void FEventAssetEditor::OnGraphEditorNotification(FString& Msg)
{
	FNotificationInfo Info(FText::Format(LOCTEXT("Common_Tips", "{0}"), FText::FromString(Msg)));
	Info.bUseLargeFont = true;
	Info.ExpireDuration = 3.0f;

	FocusedGraphEditor->AddNotification(Info, false);
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
