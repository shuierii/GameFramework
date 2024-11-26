// Copyright HuanMos. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Manager/MgrBase.h"
#include "TickMgr.generated.h"

// 声明回调函数委托
// 必须使用动态委托,动态委托能序列化，才能给蓝图使用
DECLARE_DYNAMIC_DELEGATE_OneParam(FTickDelegate, float, deltaTime);

/// <summary>
/// 委托者
/// </summary>
UCLASS(BlueprintType)
class GAMEFRAMEWORK_API UTickDelegater : public UObject
{
    GENERATED_BODY()

public:

    /// <summary>
    /// 回调函数委托
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FTickDelegate OnTick;
};

/// <summary>
/// Created by zhangwm 2020/12/06
/// Tick管理模块
/// </summary>
UCLASS(BlueprintType)
class GAMEFRAMEWORK_API UTickMgr : public UMgrBase, public FTickableGameObject
{
    GENERATED_BODY()

public:

    /** Implement this for deinitialization of instances of the system */
    virtual void Deinitialize() override;

    /// <summary>
    /// 重写Tick
    /// </summary>
    virtual void Tick( float deltaTime ) override;

    /// <summary>
    /// 重写GetStatId
    /// </summary>
    /// <returns></returns>
    virtual TStatId GetStatId() const override;

public:

    /// <summary>
    /// 释放清理模块
    /// </summary>
    UFUNCTION(BlueprintCallable, Category = "TickMgr")
    void Release();

    /// <summary>
    /// 生成tick委托者
    /// </summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = "TickMgr")
    UTickDelegater* CreateTickDelegater();

    /// <summary>
    /// 注册Tick
    /// </summary>
    /// <param name="listenerID">监听者ID</param>
    /// <param name="delegater">委托者</param>
    UFUNCTION(BlueprintCallable, Category = "TickMgr")
    bool RegisterTick(FString listenerID, UTickDelegater* delegater);

    /// <summary>
    /// 是否包含此监听者委托
    /// </summary>
    /// <param name="listenerID">监听者ID</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = "TickMgr")
    bool ContainTick(FString listenerID);

    /// <summary>
    /// 注销Tick
    /// </summary>
    /// <param name="listenerID">监听者ID</param>
    UFUNCTION(BlueprintCallable, Category = "TickMgr")
    bool UnregisterTick(FString listenerID);

private:

    /// <summary>
    /// Tick映射表
    /// </summary>
    UPROPERTY()
    TMap<FString, UTickDelegater*> mTickMap;
};
