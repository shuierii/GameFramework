#pragma once

class UEventAsset;

class EVENTEDITOR_API FEventAssetEditor : public FAssetEditorToolkit
{
public:
	FEventAssetEditor();
	~FEventAssetEditor();

	// AssetEditorToolkit
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	// END

public:
	void InitEventAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEditor);

private:
	void CreateWidgets(); // 创建事件编辑器界面
	void CreateToolbar(); // 创建工具栏
	TSharedRef<SGraphEditor> CreateGraphWidget(); // 创建图表面板
	void BindGraphCommands(); // 绑定图标操作指令，如复制等

	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args) const;
	TSharedRef<SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& Args) const;
	TSharedRef<SDockTab> SpawnTab_Palette(const FSpawnTabArgs& Args) const;

public:
	static const FName GraphTab;
	static const FName DetailsTab;
	static const FName PaletteTab;

private:
	UEventAsset* EventAsset;
	TSharedPtr<IDetailsView> DetailsView;
	TSharedPtr<SGraphEditor> FocusedGraphEditor;
};
