#pragma once

#include "Event/Public/Node/EventNode_Base.h"
#include "NodeAssetFactory_Precondition.generated.h"

UCLASS()
class EVENTEDITOR_API UNodeAssetFactory_Precondition : public UFactory
{
	GENERATED_UCLASS_BODY()
public:
	// UFactory
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// END
	
public:
	UPROPERTY(EditAnywhere, Category = "资产工厂")
	TSubclassOf<UEventNode_Base> ParentClass;
};
