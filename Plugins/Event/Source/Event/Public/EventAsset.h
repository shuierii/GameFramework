#pragma once
#include "Node/EventNode_Base.h"

#include "EventAsset.generated.h"

UCLASS(BlueprintType)
class EVENT_API UEventAsset : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UEdGraph* GetGraph() const { return EventGraph; }
	UEventNode_Base* CreateNode(const UClass* NodeClass, UEdGraphNode* EdGraphNode);

public:
	UPROPERTY()
	UEdGraph* EventGraph;
};
