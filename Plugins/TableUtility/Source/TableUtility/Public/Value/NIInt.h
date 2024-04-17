// Copyright HuanMos. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Value/NIValue.h"
#include "NIInt.generated.h"

/// <summary>
/// 自定义数据类型-Int
/// 内部使用int32
/// </summary>
UCLASS(BlueprintType)
class TABLEUTILITY_API UNIInt : public UNIValue
{
    GENERATED_BODY()

public:

    /// <summary>
    /// 构造函数
    /// </summary>
    UNIInt();

public:

    /// <summary>
    /// 设置值
    /// </summary>
    /// <param name="value"></param>
    UFUNCTION(BlueprintCallable, Category = NIInt)
    void SetValue(int32 value);

    /// <summary>
    /// 获取值
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIInt)
    int32 GetValue();

private:

    /// <summary>
    /// 值
    /// </summary>
    UPROPERTY()
    int32 mValue;
};
