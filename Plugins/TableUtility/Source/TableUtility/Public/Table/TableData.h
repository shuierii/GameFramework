// Copyright HuanMos. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TableData.generated.h"

class URowData;
struct FFieldInfo;

/// <summary>
/// 表格数据
/// </summary>
UCLASS(BlueprintType)
class TABLEUTILITY_API UTableData : public UObject
{
    GENERATED_BODY()

public:
    /// <summary>
    /// 设置表名
    /// </summary>
    /// <param name="tableName">表名</param>
    /// <returns></returns>
    void SetTableName(FString tableName);

    /// <summary>
    /// 设置列字段
    /// </summary>
    /// <param name="fieldInfos">列字段信息</param>
    /// <returns></returns>
    void SetFields(TArray<FFieldInfo>& fieldInfos);

    /// <summary>
    /// 设置主键字段
    /// </summary>
    /// <param name="primaryKey">主键</param>
    /// <returns></returns>
    void SetPrimaryKey(FString primaryKey);

    /// <summary>
    /// 添加行数据
    /// </summary>
    /// <param name="primaryKey">主键</param>
    /// <param name="row">行数据</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    bool AddRowBySKey(FString primaryKey, URowData* row);

    /// <summary>
    /// 添加行数据
    /// </summary>
    /// <param name="primaryKey">主键</param>
    /// <param name="row">行数据</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    bool AddRowByIKey(int32 primaryKey, URowData* row);

    /// <summary>
    /// 移除行数据
    /// </summary>
    /// <param name="primaryKey">主键</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    bool RemoveRowBySKey(FString primaryKey);

    /// <summary>
    /// 移除行数据
    /// </summary>
    /// <param name="primaryKey">主键</param>
    UFUNCTION(BlueprintCallable, Category = TableData)
    bool RemoveRowByIKey(int32 primaryKey);

public:

    /// <summary>
    /// 设置列字段
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    TArray<FString> GetFields();

    /// <summary>
    /// 获取行数据
    /// </summary>
    /// <param name="primaryKey">主键</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    URowData* GetRowBySKey(FString primaryKey);

    /// <summary>
    /// 获取行数据
    /// </summary>
    /// <param name="primaryKey">主键</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    URowData* GetRowByIKey(int32 primaryKey);

    /// <summary>
    /// 是否包含指定key数据
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    bool ContainsBySKey(FString primaryKey);

    /// <summary>
    /// 是否包含指定key数据
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    bool ContainsByIKey(int32 primaryKey);

    /// <summary>
    /// 获取RowMapOfSKey
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    TMap<FString, URowData*> GetRowMapOfSKey();

    /// <summary>
    /// 获取RowMapOfIKey
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    TMap<int32, URowData*> GetRowMapOfIKey();

    /// <summary>
    /// 获取RowMapOfSKey的所有PrimaryKeys
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    TArray<FString> GetPrimaryKeysOfSKey();

    /// <summary>
    /// 获取RowMapOfSKey的所有Row
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    TArray<URowData*> GetRowsOfSKey();

    /// <summary>
    /// 获取RowMapOfIKey的所有PrimaryKeys
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    TArray<int32> GetPrimaryKeysOfIKey();

    /// <summary>
    /// 获取RowMapOfIKey的所有Row
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    TArray<URowData*> GetRowsOfIKey();

    /// <summary>
    /// 获取表名
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    FString GetTableName();

    /// <summary>
    /// 获取主键字段
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    FString GetPrimaryKey();

    /// <summary>
    /// 吸收同结构配置表
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    bool AppendTable(UTableData* table);

    /// <summary>
    /// 获取数据描述
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableData)
    FString GetDesc();

private:
    /// <summary>
    /// 表名
    /// </summary>
    UPROPERTY()
    FString mTableName;

    /// <summary>
    /// 表名
    /// </summary>
    UPROPERTY()
    TArray<FString> mFields;

    /// <summary>
    /// 主键字段
    /// </summary>
    UPROPERTY()
    FString mPrimaryKey;

    /// <summary>
    /// key为String数据映射
    /// </summary>
    UPROPERTY()
    TMap<FString, URowData*> mRowMapOfSKey;

    /// <summary>
    /// key为int32数据映射
    /// </summary>
    UPROPERTY()
    TMap<int32, URowData*> mRowMapOfIKey;
};
