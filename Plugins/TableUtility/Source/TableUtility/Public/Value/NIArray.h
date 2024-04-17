// Copyright HuanMos. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Value/NIValue.h"
#include "NIArray.generated.h"

/// <summary>
/// 自定义数据类型-Array
/// 内部使用TArray
/// </summary>
UCLASS(BlueprintType)
class TABLEUTILITY_API UNIArray : public UNIValue
{
    GENERATED_BODY()

public:

    /// <summary>
    /// 构造函数
    /// </summary>
    UNIArray();

public:

    /// <summary>
    /// 添加元素
    /// </summary>
    /// <param name="element"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = NIArray)
    int32 Add(UNIValue* element);

    /// <summary>
    /// 移除元素
    /// </summary>
    /// <param name="element"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = NIArray)
    int32 Remove(UNIValue* element);

    /// <summary>
    /// 根据索引移除元素
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = NIArray)
    bool RemoveAt(int32 index);

    /// <summary>
    /// 根据索引设置元素
    /// </summary>
    /// <param name="index"></param>
    /// <param name="value"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = NIArray)
    bool Set(int32 index, UNIValue* value);

    /// <summary>
    /// 根据索引获取值
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIArray)
    UNIValue* Get(int32 index);

    /// <summary>
    /// 数组长度
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIArray)
    int32 Num();

    /// <summary>
    /// 获取值
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIArray)
    TArray<UNIValue*> GetValue();

    /// <summary>
    /// 查找元素
    /// 注意:
    ///     1.无法查找NIValue里的值
    ///     2.需对象一样(内存地址)
    /// </summary>
    /// <param name="element"></param>
    /// <returns>元素下标索引</returns>
    UFUNCTION(BlueprintPure, Category = NIArray)
    int32 Find(UNIValue* element);

    /// <summary>
    /// 查找元素
    /// 注意:查找NIValue里的值
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIArray)
    int32 FindValueOfInt(int32 value);

    /// <summary>
    /// 查找元素
    /// 注意:查找NIValue里的值
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIArray)
    int32 FindValueOfString(FString value);

    /// <summary>
    /// 通过TArray追加
    /// </summary>
    /// <param name="list"></param>
    UFUNCTION(BlueprintCallable, Category = NIArray)
    void AppendByTArray(TArray<UNIValue*> value);

    /// <summary>
    /// 通过NIArray追加
    /// </summary>
    /// <param name="value"></param>
    UFUNCTION(BlueprintCallable, Category = NIArray)
    bool AppendByNIArray(UNIArray* value);

    /// <summary>
    /// 获取数据描述
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIArray)
    FString GetDesc();

private:

    /// <summary>
    /// 值
    /// </summary>
    UPROPERTY()
    TArray<UNIValue*> mValue;
};
