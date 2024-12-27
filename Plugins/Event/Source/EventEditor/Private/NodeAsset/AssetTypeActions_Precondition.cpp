#include "NodeAsset/AssetTypeActions_Precondition.h"
#include "EventEditor.h"
#include "Blueprint/Blueprint_EventNode_Precondition.h"

#define LOCTEXT_NAMESPACE "FAssetTypeActions_Precondition"

FText FAssetTypeActions_Precondition::GetName() const
{
	return LOCTEXT("FAssetTypeActions_Precondition_Name", "前置条件");
}

uint32 FAssetTypeActions_Precondition::GetCategories()
{
	return FEventEditorModule::EventAssetCategory;
}

FColor FAssetTypeActions_Precondition::GetTypeColor() const
{
	return FColor(255, 196, 128);
}

UClass* FAssetTypeActions_Precondition::GetSupportedClass() const
{
	return UBlueprint_EventNode_Precondition::StaticClass();
}

#undef LOCTEXT_NAMESPACE
