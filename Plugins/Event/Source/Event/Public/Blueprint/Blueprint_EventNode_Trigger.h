#pragma once

#include "Blueprint_EventNode_Trigger.generated.h"

/*
 * 和 FAssetTypeActions_Trigger 关联
 */

UCLASS()
class EVENT_API UBlueprint_EventNode_Trigger : public UBlueprint
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
