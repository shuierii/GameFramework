// Copyright HuanMos. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TableParser.generated.h"

class UTableData;
class UNIValue;

#pragma region Struct

/// <summary>
/// 配置表行数据信息结构体
/// </summary>
USTRUCT()
struct FRowInfo
{
    GENERATED_USTRUCT_BODY()

public:
    /// <summary>
    /// 配置表行数据
    /// </summary>
    UPROPERTY()
    TMap<FString, FString> InfoMap;
};

/// <summary>
/// 表格字段信息结构体
/// </summary>
USTRUCT()
struct FFieldInfo
{
    GENERATED_USTRUCT_BODY()

public:
    /// <summary>
    /// 字段名
    /// </summary>
    UPROPERTY()
    FString Name;

    /// <summary>
    /// 字段类型
    /// </summary>
    UPROPERTY()
    FString Type;
};

#pragma endregion

/// <summary>
/// 表解析器
/// </summary>

UCLASS(BlueprintType)
class TABLEUTILITY_API UTableParser : public UObject
{
    GENERATED_BODY()

public:
    /// <summary>
    /// 解析表格数据
    /// </summary>
    /// <param name="tableName">表名</param>
    /// <param name="lines">行数据</param>
    /// <param name="ignoreCommentCol">是否忽视注释列</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = TableParser)
    UTableData* ParseTable(FString tableName, TArray<FString>& lines, bool ignoreCommentCol = true);

private:
    /// <summary>
    /// 提取配置表信息
    /// </summary>
    /// <param name="tableName">表名</param>
    /// <param name="lines">行数据</param>
    /// <param name="ignoreCommentCol">是否忽视注释列</param>
    /// <returns></returns>
    bool FetchTableInfo(FString tableName, TArray<FString>& lines, bool ignoreCommentCol = true);

    /// <summary>
    /// 构建表格数据
    /// </summary>
    /// <param name="tableName">表名</param>
    /// <returns></returns>
    UTableData* CreateTableData(FString tableName);

    /// <summary>
    /// 是否是注释行
    /// </summary>
    /// <param name="line"></param>
    /// <returns></returns>
    bool IsAnnotationLine(const TCHAR* line);

    /// <summary>
    /// 提取行字段数据
    /// </summary>
    /// <param name="line"></param>
    /// <returns></returns>
    TArray<FString> FetchFields(const TCHAR* line);

    /// <summary>
    /// 提取字段数据
    /// </summary>
    /// <param name="line"></param>
    /// <param name="startPos"></param>
    /// <param name="length"></param>
    /// <returns></returns>
    FString FetchField(FString line, int32 startPos, int32 length);

    /// <summary>
    /// 是否是空行
    /// </summary>
    /// <param name="fields"></param>
    /// <returns></returns>
    bool IsEmptyLine(TArray<FString>& fields);

    /// <summary>
    /// 提取有效列字段下标集
    /// </summary>
    /// <param name="fields"></param>
    /// <param name="ignoreCommentCol"></param>
    /// <returns></returns>
    TArray<int32> FetchValidFieldIndexs(TArray<FString>& fields, bool ignoreCommentCol = true);

    /// <summary>
    /// 解析字段值
    /// </summary>
    /// <param name="valueType"></param>
    /// <param name="valueStr"></param>
    /// <returns></returns>
    UNIValue* ParseFieldValue(FString valueType, FString valueStr);

    /// <summary>
    /// 解析auto类型字段值
    /// </summary>
    /// <param name="valueStr"></param>
    /// <returns></returns>
    UNIValue* ParseAutoType(FString valueStr);

    /// <summary>
    /// 解析int类型字段值
    /// </summary>
    /// <param name="valueStr"></param>
    /// <returns></returns>
    UNIValue* ParseIntType(FString valueStr);

    /// <summary>
    /// 解析string类型字段值
    /// </summary>
    /// <param name="valueStr"></param>
    /// <returns></returns>
    UNIValue* ParseStringType(FString valueStr);

    /// <summary>
    /// 解析map类型字段值
    /// </summary>
    /// <param name="valueStr"></param>
    /// <returns></returns>
    UNIValue* ParseMapType(FString valueStr);

    /// <summary>
    /// 解析array类型字段值
    /// </summary>
    /// <param name="valueStr"></param>
    /// <returns></returns>
    UNIValue* ParseArrayType(FString valueStr);

public:
    /// <summary>
    /// 配置表名
    /// </summary>
    UPROPERTY()
    FString mTableName;

    /// <summary>
    /// 主键字段
    /// </summary>
    UPROPERTY()
    FString mPrimaryKey;

    /// <summary>
    /// 配置表列字段数据
    /// key-field value-type
    /// </summary>
    UPROPERTY()
    TArray<FFieldInfo> mFieldInfos;

    /// <summary>
    /// 配置表数据
    /// </summary>
    UPROPERTY()
    TArray<FRowInfo> mTableInfo;
};
