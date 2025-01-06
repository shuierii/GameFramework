#include "Graph/EventGraphSettings.h"

UEventGraphSettings::UEventGraphSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	  , bShowDefaultPinNames(false)
	  , ExecPinColorModifier(0.75f, 0.75f, 0.75f, 1.0f)
	  , NodeDescriptionBackground(FLinearColor(0.0625f, 0.0625f, 0.0625f, 1.0f))
	  , NodeStatusBackground(FLinearColor(0.12f, 0.12f, 0.12f, 1.0f))
	  , NodePreloadedBackground(FLinearColor(0.12f, 0.12f, 0.12f, 1.0f))
	  , CircuitConnectionAngle(45.f)
	  , CircuitConnectionSpacing(FVector2D(30.f))
	  , InactiveWireColor(FLinearColor(0.364f, 0.364f, 0.364f, 1.0f))
	  , InactiveWireThickness(1.5f)
	  , RecentWireDuration(3.0f)
	  , RecentWireColor(FLinearColor(1.0f, 0.05f, 0.0f, 1.0f))
	  , RecentWireThickness(6.0f)
	  , RecordedWireColor(FLinearColor(0.432f, 0.258f, 0.096f, 1.0f))
	  , RecordedWireThickness(3.5f)
	  , SelectedWireColor(FLinearColor(0.984f, 0.482f, 0.010f, 1.0f))
	  , SelectedWireThickness(1.5f)
{
	NodeTitleColors.Emplace(EEventNodeStyle::Trigger, FColor::FromHex("ffd400")); // 黄色
	
	NodeTitleColors.Emplace(EEventNodeStyle::Precondition, FColor::FromHex("ffB6c1")); // 浅粉红
	
	NodeTitleColors.Emplace(EEventNodeStyle::Input, FColor::FromHex("00ff7f")); // 适中的春天的绿色
	NodeTitleColors.Emplace(EEventNodeStyle::Output, FColor::FromHex("ff00ff")); // 洋红

	NodeTitleColors.Emplace(EEventNodeStyle::DialogEvent, FColor::FromHex("d71345")); // 红色

	NodeTitleColors.Emplace(EEventNodeStyle::Dialog, FColor::FromHex("40e0D0")); // 绿宝石
	
	NodeTitleColors.Emplace(EEventNodeStyle::Action, FColor::FromHex("8552a1")); // 紫

	NodeTitleColors.Emplace(EEventNodeStyle::Script, FColor::FromHex("ffff00")); // 纯黄
}
