#include "NodeAsset/AssetTypeActions_Action.h"
#include "EventEditor.h"
#include "Blueprint/Blueprint_EventNode_Action.h"

#define LOCTEXT_NAMESPACE "FAssetTypeActions_Action"

FText FAssetTypeActions_Action::GetName() const
{
	return LOCTEXT("FAssetTypeActions_Action_Name", "行动");
}

uint32 FAssetTypeActions_Action::GetCategories()
{
	return FEventEditorModule::EventAssetCategory;
}

FColor FAssetTypeActions_Action::GetTypeColor() const
{
	return FColor(255, 196, 128);
}

UClass* FAssetTypeActions_Action::GetSupportedClass() const
{
	return UBlueprint_EventNode_Action::StaticClass();
}

#undef LOCTEXT_NAMESPACE
