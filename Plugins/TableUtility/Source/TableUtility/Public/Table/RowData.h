// Copyright HuanMos. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RowData.generated.h"

class UNIMap;
class UNIValue;
class UNIArray;

/// <summary>
/// 表格行数据
/// </summary>
UCLASS(BlueprintType)
class TABLEUTILITY_API URowData : public UObject
{
    GENERATED_BODY()

public:

    /// <summary>
    /// 添加数据
    /// </summary>
    /// <param name="field">列名</param>
    /// <param name="data">数据</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = RowData)
    bool AddData(FString field, UNIValue* data);

    /// <summary>
    /// 移除数据
    /// </summary>
    /// <param name="field">列名</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = RowData)
    bool RemoveData(FString field);

public:

    /// <summary>
    /// 根据列名获取数据
    /// </summary>
    /// <param name="field">列名</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = RowData)
    UNIValue* GetData(FString field);

    /// <summary>
    /// 根据列名获取int类型数据
    /// </summary>
    /// <param name="field"></param>
    /// <param name="defaultData"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = RowData)
    int32 GetDataOfInt(FString field, int32 defaultData = 0);

    /// <summary>
    /// 根据列名获取string类型数据
    /// </summary>
    /// <param name="field"></param>
    /// <param name="defaultData"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = RowData)
    FString GetDataOfString(FString field, FString defaultData = "");

    /// <summary>
    /// 根据列名获取NIMap类型数据
    /// </summary>
    /// <param name="field"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = RowData)
    UNIMap* GetDataOfMap(FString field);

    /// <summary>
    /// 根据列名获取NIArray类型数据
    /// </summary>
    /// <param name="field"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = RowData)
    UNIArray* GetDataOfArray(FString field);

    /// <summary>
    /// 是否包含指定key
    /// </summary>
    /// <param name="field"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = RowData)
    bool Contains(FString field);

    /// <summary>
    /// 获取所有字段
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = RowData)
    TArray<FString> GetAllFields();

    /// <summary>
    /// 获取数据描述
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = RowData)
    FString GetDesc();

private:

    /// <summary>
    /// 列数据
    /// </summary>
    UPROPERTY()
    TMap<FString, UNIValue*> mDataMap;
};
