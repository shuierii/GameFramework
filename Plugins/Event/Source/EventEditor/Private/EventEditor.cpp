#include "EventEditor.h"

#include "IAssetTypeActions.h"
#include "NodeAsset/AssetTypeActions_Input.h"
#include "NodeAsset/AssetTypeActions_Output.h"
#include "NodeAsset/AssetTypeActions_Precondition.h"
#include "NodeAsset/AssetTypeActions_Trigger.h"
#include "EventEditorStyle.h"
#include "EventAsset/AssetTypeActions_EventAsset.h"

#define LOCTEXT_NAMESPACE "FEventEditorModule"

EAssetTypeCategories::Type FEventEditorModule::EventAssetCategory =  static_cast<EAssetTypeCategories::Type>(0);

void FEventEditorModule::StartupModule()
{
	// 初始化编辑器样式
	FEventEditorStyle::Initialize();

	// 注册资源
	RegisterAsset();
}

void FEventEditorModule::ShutdownModule()
{
	FEventEditorStyle::Shutdown();

	UnregisterAsset();
}

TSharedRef<FEventAssetEditor> FEventEditorModule::CreateEventAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UEventAsset* EventAsset)
{
	TSharedRef<FEventAssetEditor> NewEventAssetEditor(new FEventAssetEditor());

	NewEventAssetEditor->InitEventAssetEditor(Mode, InitToolkitHost, EventAsset);

	return NewEventAssetEditor;
}

void FEventEditorModule::RegisterAsset()
{
	// 获取资源工具模块
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	// 注册到内容右键显示资产
	EventAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Event")), LOCTEXT("EventAssetCategory", "Event"));
	
	// 注册资产
	TSharedPtr<IAssetTypeActions> AssetTypeActions_Event = MakeShareable(new FAssetTypeActions_EventAsset());
	AssetTools.RegisterAssetTypeActions(AssetTypeActions_Event.ToSharedRef());
	RegisteredAssetActionsArr.Add(AssetTypeActions_Event);
	
	TSharedPtr<IAssetTypeActions> AssetTypeActions_Trigger = MakeShareable(new FAssetTypeActions_Trigger());
	AssetTools.RegisterAssetTypeActions(AssetTypeActions_Trigger.ToSharedRef());
	RegisteredAssetActionsArr.Add(AssetTypeActions_Trigger);

	TSharedPtr<IAssetTypeActions> AssetTypeActions_Precondition = MakeShareable(new FAssetTypeActions_Precondition());
	AssetTools.RegisterAssetTypeActions(AssetTypeActions_Precondition.ToSharedRef());
	RegisteredAssetActionsArr.Add(AssetTypeActions_Precondition);

	TSharedPtr<IAssetTypeActions> AssetTypeActions_Input = MakeShareable(new FAssetTypeActions_Input());
	AssetTools.RegisterAssetTypeActions(AssetTypeActions_Input.ToSharedRef());
	RegisteredAssetActionsArr.Add(AssetTypeActions_Input);

	TSharedPtr<IAssetTypeActions> AssetTypeActions_Output = MakeShareable(new FAssetTypeActions_Output());
	AssetTools.RegisterAssetTypeActions(AssetTypeActions_Output.ToSharedRef());
	RegisteredAssetActionsArr.Add(AssetTypeActions_Output);
	
	UE_LOG(LogTemp, Log, TEXT("FEventEditorModule::RegisterAsset 注册资产"));
}

void FEventEditorModule::UnregisterAsset()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEventEditorModule, EventEditor)
