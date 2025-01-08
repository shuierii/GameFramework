#pragma once
#include "EventAssetToolbar.h"
#include "..\Graph\Node\EdGraphNode_Base.h"
#include "Graph/Widget/EventPalette.h"
#include "Value/NIMap.h"

class UEventAsset;
struct FEdGraphEditAction;
class UNIMap;
class SEventPalette;

class EVENTEDITOR_API FEventAssetEditor : public FAssetEditorToolkit, public FNotifyHook
{
public:
	FEventAssetEditor();
	~FEventAssetEditor();

	// FAssetEditorToolkit
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	// END

	// FNotifyHook
	virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;
	// END

public:
	void InitEventAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEditor);
	UEventAsset* GetEventAsset() const { return EventAsset; }
	TSet<UEdGraphNode_Base*> GetSelectedEventNodes() const;

private:
	void CreateWidgets(); // 创建事件编辑器界面
	TSharedRef<SGraphEditor> CreateGraphWidget(); // 创建图表面板
	void BindGraphCommands(); // 绑定图标操作指令，如复制,跳转蓝图定义等
	void OnPinConnectionFunc(UEdGraphPin* A, UEdGraphPin* B);

	void OnSelectedNodesChanged(const TSet<UObject*>& Nodes);
	void OnNodeDoubleClicked(UEdGraphNode* Node);
	void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);

	bool CanSelectAllNodes() const;
	void SelectAllNodes() const;

	bool CanDeleteNodes() const;
	void DeleteSelectedNodes();
	void DeleteSelectedDuplicableNodes();

	bool CanCopyNodes() const;
	void CopySelectedNodes() const;

	bool CanCutNodes() const;
	void CutSelectedNodes();

	bool CanPasteNodes() const;
	void PasteNodes();

	bool CanDuplicateNodes() const;
	void DuplicateNodes();

	bool CanJumpToNodeDefinition() const;
	void JumpToNodeDefinition() const;

	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args) const;
	TSharedRef<SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& Args) const;
	TSharedRef<SDockTab> SpawnTab_Palette(const FSpawnTabArgs& Args) const;

	// 工具栏
	void CreateToolbar(); // 创建工具栏
	void BindToolbarCommands();
	void OnExportData();
	// END

	// 收集数据
	void CollectEvent(const FEdGraphEditAction& Action);
	void CollectNode(UEdGraphNode_Base* EdGraphNode);
	UEdGraphNode_Base* GetConnectEdGraphNode(UEdGraphPin* Pin);

	bool ExportData(TArray<FNotificationInfo>& MsgList);
	UNIMap* ExportData_Node(UEventNode_Base* Node, TArray<FNotificationInfo>& MsgList);
	// END

	void OnGraphEditorNotification(FString& Msg);

public:
	static const FName GraphTab;
	static const FName DetailsTab;
	static const FName PaletteTab;

private:
	UEventAsset* EventAsset;
	TSharedPtr<IDetailsView> DetailsView;
	TSharedPtr<SEventPalette> Palette;
	TSharedPtr<SGraphEditor> FocusedGraphEditor;

	TSharedPtr<class FEventAssetToolbar> EventToolbar;
};
