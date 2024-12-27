#include "EventAsset/AssetTypeActions_EventAsset.h"

#include "EventAsset.h"
#include "EventEditor.h"

#define LOCTEXT_NAMESPACE "FAssetTypeAction_EventAsset"

FText FAssetTypeActions_EventAsset::GetName() const
{
	return LOCTEXT("FAssetTypeAction_EventAsset_Name", "事件");
}

FColor FAssetTypeActions_EventAsset::GetTypeColor() const
{
	return FColor(255, 196, 128);
}

uint32 FAssetTypeActions_EventAsset::GetCategories()
{
	return FEventEditorModule::EventAssetCategory;
}

UClass* FAssetTypeActions_EventAsset::GetSupportedClass() const
{
	return UEventAsset::StaticClass();
}

void FAssetTypeActions_EventAsset::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	UE_LOG(LogTemp, Log, TEXT("打开编辑器"));
	
	// InObjects 是指由哪个资产点击打开的
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UEventAsset* EventAsset = Cast<UEventAsset>(*ObjIt))
		{
			FEventEditorModule* EventEditorModule = &FModuleManager::LoadModuleChecked<FEventEditorModule>("EventEditor");
			EventEditorModule->CreateEventAssetEditor(Mode, EditWithinLevelEditor, EventAsset);
		}
	}
}

#undef LOCTEXT_NAMESPACE
