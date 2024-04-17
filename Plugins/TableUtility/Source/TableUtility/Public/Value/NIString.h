// Copyright HuanMos. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Value/NIValue.h"
#include "NIString.generated.h"

/// <summary>
/// 自定义数据类型-String
/// 内部使用FString
/// </summary>
UCLASS(BlueprintType)
class TABLEUTILITY_API UNIString : public UNIValue
{
    GENERATED_BODY()

public:

    /// <summary>
    /// 构造函数
    /// </summary>
    UNIString();

public:

    /// <summary>
    /// 设置值
    /// </summary>
    /// <param name="value"></param>
    UFUNCTION(BlueprintCallable, Category = NIString)
    void SetValue(FString value);

    /// <summary>
    /// 获取值
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIString)
    FString GetValue();

private:

    /// <summary>
    /// 值
    /// </summary>
    UPROPERTY()
    FString mValue;
};
