#include "EventAsset/EventAssetFactory.h"

#include "EventAsset.h"
#include "Graph/EventGraph.h"

UEventAssetFactory::UEventAssetFactory(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	SupportedClass = UEventAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UEventAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(InClass->IsChildOf(UEventAsset::StaticClass()));

	UEventAsset* NewEventAsset = NewObject<UEventAsset>(InParent, InClass, InName, Flags, Context);
	UEventGraph::CreateGraph(NewEventAsset);

	return NewEventAsset;
}
