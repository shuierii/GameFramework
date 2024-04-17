// Copyright HuanMos. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NIValue.generated.h"

class UNIInt;
class UNIString;
class UNINumber;
class UNIMap;
class UNIArray;

#pragma region ValueType

/// <summary>
/// 值类型枚举
/// </summary>
UENUM(BlueprintType)
enum class EValueType : uint8
{
    None,

    /// <summary>
    /// int32
    /// </summary>
    Int,

    /// <summary>
    /// FString
    /// </summary>
    String,

    /// <summary>
    /// TMap
    /// </summary>
    Map,

    /// <summary>
    /// TArray
    /// </summary>
    Array,
};

#pragma endregion

/// <summary>
/// 自定义数据类型基类
/// </summary>
UCLASS(Abstract, BlueprintType)
class TABLEUTILITY_API UNIValue : public UObject
{
    GENERATED_BODY()

public:

#pragma region 构建接口

    /// <summary>
    /// 构建NIInt
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIValue)
    static UNIInt* CreateInt(int32 value = 0);

    /// <summary>
    /// 构建NIString
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIValue)
    static UNIString* CreateString(FString value = "");

    /// <summary>
    /// 构建NIMap
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIValue)
    static UNIMap* CreateMap();

    /// <summary>
    /// 构建NIArray
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIValue)
    static UNIArray* CreateArray();

#pragma endregion

#pragma region 类型判断接口

    /// <summary>
    /// 是否是int
    /// </summary>
    UFUNCTION(BlueprintPure, Category = NIValue)
    bool IsInt() const;

    /// <summary>
    /// 是否是FString
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIValue)
    bool IsString() const;

    /// <summary>
    /// 是否是Map
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIValue)
    bool IsMap() const;

    /// <summary>
    /// 是否是Array
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIValue)
    bool IsArray() const;

#pragma endregion

#pragma region 类型转换接口

    /// <summary>
    /// 转换为NIInt
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIValue)
    UNIInt* AsInt();

    /// <summary>
    /// 转换为NIString
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIValue)
    UNIString* AsString();

    /// <summary>
    /// 转换为NIMap
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIValue)
    UNIMap* AsMap();

    /// <summary>
    /// 转换为NIArray
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintPure, Category = NIValue)
    UNIArray* AsArray();

#pragma endregion

    /// <summary>
    /// 深拷贝
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = NIValue)
    static UNIValue* DeepCopy(UNIValue* value);

protected:

    /// <summary>
    /// 数据类型
    /// </summary>
    UPROPERTY()
    EValueType mType = EValueType::None;
};
