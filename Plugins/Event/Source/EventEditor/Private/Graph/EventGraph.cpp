#include "Graph/EventGraph.h"

#include "Graph/EventGraphSchema.h"
#include "Kismet2/BlueprintEditorUtils.h"

void UEventGraph::NotifyGraphChanged()
{
	this->GetEventAsset()->MarkPackageDirty();

	Super::NotifyGraphChanged();
}

UEdGraph* UEventGraph::CreateGraph(UEventAsset* InEventAsset)
{
	UEventGraph* NewGraph = CastChecked<UEventGraph>(FBlueprintEditorUtils::CreateNewGraph(InEventAsset, NAME_None, StaticClass(), UEventGraphSchema::StaticClass()));

	NewGraph->bAllowDeletion = false;
	InEventAsset->EventGraph = NewGraph;

	return NewGraph;
}

UEventAsset* UEventGraph::GetEventAsset() const
{
	return CastChecked<UEventAsset>(GetOuter());
}
