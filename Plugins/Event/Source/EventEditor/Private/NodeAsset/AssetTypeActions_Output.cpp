#include "NodeAsset/AssetTypeActions_Output.h"

#include "EventEditor.h"
#include "Blueprint/Blueprint_EventNode_Output.h"

#define LOCTEXT_NAMESPACE "FAssetTypeActions_Output"

FText FAssetTypeActions_Output::GetName() const
{
	return LOCTEXT("FAssetTypeActions_Output_Name", "输出");
}

uint32 FAssetTypeActions_Output::GetCategories()
{
	return FEventEditorModule::EventAssetCategory;
}

FColor FAssetTypeActions_Output::GetTypeColor() const
{
	return FColor(255, 196, 128);
}

UClass* FAssetTypeActions_Output::GetSupportedClass() const
{
	return UBlueprint_EventNode_Output::StaticClass();
}

#undef LOCTEXT_NAMESPACE
