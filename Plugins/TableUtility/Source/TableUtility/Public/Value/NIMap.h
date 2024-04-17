// Copyright HuanMos. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Value/NIValue.h"
#include "NIMap.generated.h"

/// <summary>
/// 自定义数据类型-Map
/// 内部使用TMap
/// </summary>
UCLASS(BlueprintType)
class TABLEUTILITY_API UNIMap : public UNIValue
{
    GENERATED_BODY()

public:

    /// <summary>
    /// 构造函数
    /// </summary>
    UNIMap();

public:

    /// <summary>
    /// 添加值
    ///     已存在,覆盖
    ///     不存在，新增
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = NIMap)
    void AddBySKey(FString key, UNIValue* value);

    /// <summary>
    /// 添加值
    ///     已存在,覆盖
    ///     不存在，新增
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = NIMap)
    void AddByIKey(int32 key, UNIValue* value);

    /// <summary>
    /// 移除数据
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = NIMap)
    bool RemoveBySKey(FString key);

    /// <summary>
    /// 移除数据
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = NIMap)
    bool RemoveByIKey(int32 key);

    /// <summary>
    /// 获取数值
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    template<typename T>
    T* GetValue(FString key);

    /// <summary>
    /// 获取数值
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    template<typename T>
    T* GetValue(int32 key);

    /// <summary>
    /// 获取值
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    UNIValue* GetValueBySKey(FString key);

    /// <summary>
    ///  获取int数值
    /// </summary>
    /// <param name="key"></param>
    /// <param name="defaultValue"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    int32 GetValueOfIntBySKey(FString key, int32 defaultValue = 0);

    /// <summary>
    /// 获取string值
    /// </summary>
    /// <param name="key"></param>
    /// <param name="defaultValue"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    FString GetValueOfStringBySKey(FString key, FString defaultValue = "");

    /// <summary>
    /// 获取NIMap值
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    UNIMap* GetValueOfMapBySKey(FString key);

    /// <summary>
    /// 获取NIArray值
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    UNIArray* GetValueOfArrayBySKey(FString key);

    /// <summary>
    /// 获取值
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    UNIValue* GetValueByIKey(int32 key);

    /// <summary>
    ///  获取int数值
    /// </summary>
    /// <param name="key"></param>
    /// <param name="defaultValue"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    int32 GetValueOfIntByIKey(int32 key, int32 defaultValue);

    /// <summary>
    /// 获取string值
    /// </summary>
    /// <param name="key"></param>
    /// <param name="defaultValue"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    FString GetValueOfStringByIKey(int32 key, FString defaultValue);

    /// <summary>
    /// 获取NIMap值
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    UNIMap* GetValueOfMapByIKey(int32 key);

    /// <summary>
    /// 获取NIArray值
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    UNIArray* GetValueOfArrayByIKey(int32 key);

    /// <summary>
    /// 是否包含指定key数据
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    bool ContainsBySKey(FString key);

    /// <summary>
    /// 是否包含指定key数据
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    bool ContainsByIKey(int32 key);

    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="map"></param>
    UFUNCTION(BlueprintCallable, Category = NIMap)
    void Append(UNIMap* map);

    /// <summary>
    /// 浅拷贝
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = NIMap)
    UNIMap* ShallowCopy();

    /// <summary>
    /// 清理
    /// </summary>
    UFUNCTION(BlueprintCallable, Category = NIMap)
    void Clear();

    /// <summary>
    /// 获取数目 : string + int
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    int32 Num();

    /// <summary>
    /// 获取数目
    /// </summary>
    UFUNCTION(BlueprintPure, Category = NIMap)
    int32 NumOfSKey();

    /// <summary>
    /// 获取数目
    /// </summary>
    UFUNCTION(BlueprintPure, Category = NIMap)
    int32 NumOfIKey();

    /// <summary>
    /// 获取mValueMapOfSKey
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    TMap<FString, UNIValue*> GetValueMapOfSKey();

    /// <summary>
    /// 获取mValueMapOfIKey
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    TMap<int32, UNIValue*> GetValueMapOfIKey();

    /// <summary>
    /// 获取mValueMapOfSKey的所有key
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    TArray<FString> GetKeysOfSKey();

    /// <summary>
    /// 获取mValueMapOfSKey的所有value
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    TArray<UNIValue*> GetValuesOfSKey();

    /// <summary>
    /// 获取mValueMapOfIKey的所有key
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    TArray<int32> GetKeysOfIKey();

    /// <summary>
    /// 获取mValueMapOfIKey的所有value
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    TArray<UNIValue*> GetValuesOfIKey();

    /// <summary>
    /// 获取数据描述
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIMap)
    FString GetDesc();

private:

    /// <summary>
    /// key为String值映射
    /// </summary>
    UPROPERTY()
    TMap<FString, UNIValue*> mValueMapOfSKey;

    /// <summary>
    /// key为int值映射
    /// </summary>
    UPROPERTY()
    TMap<int32, UNIValue*> mValueMapOfIKey;
};

template<typename T>
T* UNIMap::GetValue(FString key)
{
    if (!this->mValueMapOfSKey.Contains(key))
        return nullptr;

    return Cast<T>(this->mValueMapOfSKey[key]);
}

template<typename T>
T* UNIMap::GetValue(int32 key)
{
    if (!this->mValueMapOfIKey.Contains(key))
        return nullptr;

    return Cast<T>(this->mValueMapOfIKey[key]);
}