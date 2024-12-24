#pragma once

#include "EventAssetFactory.generated.h"

UCLASS(HideCategories= Object)
class EVENTEDITOR_API UEventAssetFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
public:
	// 创建资产
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
