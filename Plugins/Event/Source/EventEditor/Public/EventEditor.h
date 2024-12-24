#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IAssetTypeActions.h"
#include "EventAsset/EventAssetEditor.h"
#include "AssetTypeCategories.h"
#include "EventAsset.h"

class EVENTEDITOR_API FEventEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static TSharedRef<FEventAssetEditor> CreateEventAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UEventAsset* EventAsset);

private:
	void RegisterAsset();
	void UnregisterAsset();

public:
	static EAssetTypeCategories::Type EventAssetCategory;

private:
	// 已注册资源列表
	TArray<TSharedPtr<IAssetTypeActions>> RegisteredAssetActionsArr;
};
