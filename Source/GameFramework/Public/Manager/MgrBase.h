// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MgrBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFRAMEWORK_API UMgrBase : public UGameInstanceSubsystem
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
