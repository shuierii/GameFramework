#include "Extension/WidgetExtensionMethods.h"

UUserWidget* UWidgetExtensionMethods::CreateWidget(UWorld* World, UClass* WidgetClass)
{
	return ::CreateWidget<UUserWidget>(World, WidgetClass);
}

UWidget* UWidgetExtensionMethods::GetWidgetFromName(UUserWidget* UserWidget, const FName& Name)
{
	return UserWidget->GetWidgetFromName(Name);
}
