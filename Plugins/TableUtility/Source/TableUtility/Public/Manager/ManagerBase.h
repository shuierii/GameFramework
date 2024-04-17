// Copyright HuanMos. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ManagerBase.generated.h"

/// <summary>
/// 管理模块基类
/// </summary>
UCLASS(Abstract)
class TABLEUTILITY_API UManagerBase : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:

    /// <summary>
    /// 初始化管理类
    /// 注意：引擎自动调用
    /// </summary>
    /// <param name="Collection"></param>
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    /// <summary>
    /// 初始化管理类-TS实现
    /// </summary>
    UFUNCTION(BlueprintImplementableEvent)
    void InitializeEvent();
};
