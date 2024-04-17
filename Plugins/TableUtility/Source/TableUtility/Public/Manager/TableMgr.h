// Copyright HuanMos. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerBase.h"
#include "TableMgr.generated.h"

class UTableData;

/// <summary>
/// 配置表管理类
/// </summary>
UCLASS(BlueprintType)
class TABLEUTILITY_API UTableMgr : public UManagerBase
{
    GENERATED_BODY()

public:

    /// <summary>
    /// 加载配置表
    /// </summary>
    /// <param name="tablePath">配置表路径</param>
    /// <param name="tablePath">配置表名称</param>
    /// <returns>配置表数据</returns>
    UFUNCTION(BlueprintCallable, Category = TableMgr)
    UTableData* LoadTable(FString tablePath, FString tableName);
};
