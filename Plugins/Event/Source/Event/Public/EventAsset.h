#pragma once

#include "EventAsset.generated.h"

UCLASS(BlueprintType)
class EVENT_API UEventAsset : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UEdGraph* GetGraph() const { return EventGraph; }

public:
	UPROPERTY()
	UEdGraph* EventGraph;
};
