#pragma once

#include "AssetTypeActions/AssetTypeActions_Blueprint.h"

class EVENTEDITOR_API FAssetTypeActions_Trigger : public FAssetTypeActions_Blueprint
{
public:
	virtual FText GetName() const override;
	virtual uint32 GetCategories() override;
	virtual FColor GetTypeColor() const override;

	virtual UClass* GetSupportedClass() const override;
};
