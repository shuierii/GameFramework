#pragma once

#include "Blueprint_EventNode_Input.generated.h"

UCLASS()
class EVENT_API UBlueprint_EventNode_Input : public UBlueprint
{
	GENERATED_BODY()

public:
	// UBlueprint
	virtual bool SupportedByDefaultBlueprintFactory() const override { return false; }
	virtual bool SupportsDelegates() const override { return false; }
	virtual bool SupportsEventGraphs() const override { return false; }
	virtual bool SupportsAnimLayers() const override { return false; }
	// END
};
