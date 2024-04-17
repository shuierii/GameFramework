// Copyright HuanMos. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NIUtility.generated.h"

class UNIValue;
class UNIMap;

/// <summary>
/// NIValue工具集
/// </summary>
UCLASS(Blueprintable)
class TABLEUTILITY_API UNIUtility : public UObject
{
    GENERATED_BODY()

public:
#pragma region 混合数据转换

    /// <summary>
    /// NIValue转换为String
    /// </summary>
    UFUNCTION(BlueprintCallable, Category = NIUtility)
    static FString ConvertToString(UNIValue* value);

    /// <summary>
    /// 从String还原NIValue
    /// </summary>
    /// <param name="content"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = NIUtility)
    static UNIValue* RestoreFromString(FString content);

#pragma endregion

#pragma region 混合数据操作

    /// <summary>
    /// 设置数据
    /// </summary>
    /// <param name="path"></param>
    /// <param name="dbase"></param>
    /// <param name="value"></param>
    UFUNCTION(BlueprintCallable, Category = NIUtility)
    static bool ExpressSet(const FString& path, UNIMap* dbase, UNIValue* value);

    /// <summary>
    /// 查询数据
    /// </summary>
    /// <param name="path"></param>
    /// <param name="dbase"></param>
    UFUNCTION(BlueprintPure, Category = NIUtility)
    static UNIValue* ExpressQuery(const FString& path, UNIMap* dbase);

    /// <summary>
    /// 存在数据
    /// </summary>
    /// <param name="path"></param>
    /// <param name="dbase"></param>
    UFUNCTION(BlueprintPure, Category = NIUtility)
    static bool ExpressContains(const FString& path, UNIMap* dbase);

    /// <summary>
    /// 删除数据
    /// </summary>
    /// <param name="path"></param>
    /// <param name="dbase"></param>
    UFUNCTION(BlueprintCallable, Category = NIUtility)
    static bool ExpressDelete(const FString& path, UNIMap* dbase);

#pragma endregion

private:
    /// <summary>
    /// 从String还原NIArray
    /// </summary>
    /// <param name="content"></param>
    /// <param name="offset"></param>
    /// <returns></returns>
    static UNIValue* RestoreArray(FString& content, int32& offset);

    /// <summary>
    /// 从String还原NIMap
    /// </summary>
    /// <param name="content"></param>
    /// <param name="offset"></param>
    /// <returns></returns>
    static UNIValue* RestoreMap(FString& content, int32& offset);

    /// <summary>
    /// 从String还原NIString
    /// </summary>
    /// <param name="content"></param>
    /// <param name="offset"></param>
    /// <returns></returns>
    static UNIValue* RestoreString(FString& content, int32& offset);

    /// <summary>
    /// 从String还原NIInt
    /// </summary>
    /// <param name="content"></param>
    /// <param name="offset"></param>
    /// <returns></returns>
    static UNIValue* RestoreNumber(FString& content, int32& offset);

    /// <summary>
    /// 从String还原NIInt
    /// </summary>
    /// <param name="content"></param>
    /// <param name="offset"></param>
    /// <returns></returns>
    static UNIValue* RestoreAlias(FString& content, int32& offset);

    /// <summary>
    /// 跳过空格字符
    /// </summary>
    /// <param name="content"></param>
    /// <param name="offset"></param>
    static void SkipSpaceChar(FString& content, int32& offset);

    /// <summary>
    /// 是否Map的key标识":"
    /// </summary>
    /// <param name="content"></param>
    /// <param name="offset"></param>
    /// <returns></returns>
    static bool CheckKeyCompleted(FString& content, int32& offset);

    /// <summary>
    /// 是否Map的value
    /// </summary>
    /// <param name="content"></param>
    /// <param name="offset"></param>
    /// <returns></returns>
    static bool CheckValueCompleted(FString& content, int32& offset);

private:
    /// <summary>
    /// 路径切割记录
    /// 作用 : 减少由FString产生GC问题
    /// </summary>
    static TMap<FString, TArray<FString>> mPathSplits;
};
