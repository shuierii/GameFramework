#include "NodeAsset/AssetTypeActions_Input.h"

#include "EventEditor.h"
#include "Blueprint/Blueprint_EventNode_Input.h"

#define LOCTEXT_NAMESPACE "FAssetTypeActions_Input"

FText FAssetTypeActions_Input::GetName() const
{
	return LOCTEXT("FAssetTypeActions_Input_Name", "输入");
}

uint32 FAssetTypeActions_Input::GetCategories()
{
	return FEventEditorModule::EventAssetCategory;
}

FColor FAssetTypeActions_Input::GetTypeColor() const
{
	return FColor(255, 196, 128);
}

UClass* FAssetTypeActions_Input::GetSupportedClass() const
{
	return UBlueprint_EventNode_Input::StaticClass();
}

#undef LOCTEXT_NAMESPACE
