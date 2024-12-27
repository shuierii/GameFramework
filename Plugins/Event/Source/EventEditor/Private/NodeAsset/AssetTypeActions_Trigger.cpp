#include "NodeAsset/AssetTypeActions_Trigger.h"

#include "EventEditor.h"
#include "Blueprint/Blueprint_EventNode_Trigger.h"

#define LOCTEXT_NAMESPACE "FAssetTypeActions_Trigger"

FText FAssetTypeActions_Trigger::GetName() const
{
	return LOCTEXT("FAssetTypeActions_Trigger_Name", "触发器");
}

uint32 FAssetTypeActions_Trigger::GetCategories()
{
	return FEventEditorModule::EventAssetCategory;
}

FColor FAssetTypeActions_Trigger::GetTypeColor() const
{
	return FColor(255, 196, 128);
}

UClass* FAssetTypeActions_Trigger::GetSupportedClass() const
{
	return UBlueprint_EventNode_Trigger::StaticClass();
}

#undef LOCTEXT_NAMESPACE
