#pragma once
#include "ExtensionMethods.h"
#include "Blueprint/UserWidget.h"
#include "WidgetExtensionMethods.generated.h"

UCLASS(BlueprintType)
class GAMEFRAMEWORK_API UWidgetExtensionMethods : public UExtensionMethods
{
	GENERATED_BODY()

public:
	/// <summary>
	/// 创建UserWidget
	/// </summary>
	/// <param name="world">世界对象</param>
	/// <param name="widgetClass">窗口类对象</param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "UserWidgetExtension")
	static UUserWidget* CreateWidget(UWorld* World, UClass* WidgetClass);

	/// <summary>
	/// 通过控件名称获取控件
	/// </summary>
	/// <param name="userWidget">页面对象</param>
	/// <param name="name">控件名称</param>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable, Category = "UserWidgetExtension")
	static UWidget* GetWidgetFromName(UUserWidget* UserWidget, const FName& Name);
};
