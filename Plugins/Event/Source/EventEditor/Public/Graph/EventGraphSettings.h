#pragma once
#include "Engine/DeveloperSettings.h"
#include "EventTypes.h"
#include "EventGraphSettings.generated.h"

UCLASS(Config = Editor, DefaultConfig, meta = (DisplayName = "Event Graph"))
class EVENTEDITOR_API UEventGraphSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

public:
	static UEventGraphSettings* Get() { return StaticClass()->GetDefaultObject<UEventGraphSettings>(); }

public:
	/** Hide specific nodes from the Flow Palette without changing the source code.
    * Requires restart after making a change. */
	UPROPERTY(EditAnywhere, config, Category = "Nodes")
	TArray<TSubclassOf<class UEventNode_Base>> NodesHiddenFromPalette;
	
	/** Hide default pin names on simple nodes, reduces UI clutter */
	UPROPERTY(EditAnywhere, config, Category = "Nodes")
	bool bShowDefaultPinNames;
	
	UPROPERTY(EditAnywhere, config, Category = "Nodes")
	TMap<EEventNodeStyle, FLinearColor> NodeTitleColors;
	
	UPROPERTY(Config, EditAnywhere, Category = "Nodes")
	TMap<TSubclassOf<UEventNode_Base>, FLinearColor> NodeSpecificColors;
	
	UPROPERTY(EditAnywhere, config, Category = "Nodes")
	FLinearColor ExecPinColorModifier;
	
	UPROPERTY(EditAnywhere, config, Category = "NodePopups")
	FLinearColor NodeDescriptionBackground;
	
	UPROPERTY(EditAnywhere, config, Category = "NodePopups")
	FLinearColor NodeStatusBackground;
	
	UPROPERTY(EditAnywhere, config, Category = "NodePopups")
	FLinearColor NodePreloadedBackground;
	
	UPROPERTY(config, EditAnywhere, Category = "Wires")
	float CircuitConnectionAngle;
	
	UPROPERTY(config, EditAnywhere, Category = "Wires")
	FVector2D CircuitConnectionSpacing;
	
	UPROPERTY(EditAnywhere, config, Category = "Wires")
	FLinearColor InactiveWireColor;
	
	UPROPERTY(EditAnywhere, config, Category = "Wires", meta = (ClampMin = 0.0f))
	float InactiveWireThickness;
	
	UPROPERTY(EditAnywhere, config, Category = "Wires", meta = (ClampMin = 1.0f))
	float RecentWireDuration;
	
	/** The color to display execution wires that were just executed */
	UPROPERTY(EditAnywhere, config, Category = "Wires")
	FLinearColor RecentWireColor;
	
	UPROPERTY(EditAnywhere, config, Category = "Wires", meta = (ClampMin = 0.0f))
	float RecentWireThickness;
	
	UPROPERTY(EditAnywhere, config, Category = "Wires")
	FLinearColor RecordedWireColor;
	
	UPROPERTY(EditAnywhere, config, Category = "Wires", meta = (ClampMin = 0.0f))
	float RecordedWireThickness;
	
	UPROPERTY(EditAnywhere, config, Category = "Wires")
	FLinearColor SelectedWireColor;
	
	UPROPERTY(EditAnywhere, config, Category = "Wires", meta = (ClampMin = 0.0f))
	float SelectedWireThickness;
};
