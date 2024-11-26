// Copyright HuanMos. All Rights Reserved.


#include "Manager/TickMgr.h"


void UTickMgr::Deinitialize()
{
    this->Release();
}

void UTickMgr::Tick(float deltaTime)
{
    // 没有需要驱动的事件
    if (this->mTickMap.Num() <= 0)
        return;

    // 收集本次需要驱动列表
    TArray<UTickDelegater*> tickList;
    for (TPair<FString, UTickDelegater*>& kvMap : this->mTickMap)
    {
        if (kvMap.Value == nullptr)
            continue;

        tickList.Add(kvMap.Value);
    }

    if (tickList.Num() <= 0)
    {
        return;
    }

    // 驱动列表
    for (UTickDelegater* delegater : tickList)
    {
        if (delegater == nullptr)
            continue;

        delegater->OnTick.ExecuteIfBound(deltaTime);
    }
}

TStatId UTickMgr::GetStatId() const
{
     return Super::GetStatID();
}

void UTickMgr::Release()
{
    this->mTickMap.Empty();
}

UTickDelegater* UTickMgr::CreateTickDelegater()
{
    return NewObject<UTickDelegater>(this);
}

bool UTickMgr::RegisterTick(FString listenerID, UTickDelegater* delegater)
{
    // 监听者id/委托者不存在
    if (listenerID.IsEmpty() || delegater == nullptr)
    {

        return false;
    }

    // 已经注册过了
    if (this->mTickMap.Contains(listenerID))
    {

        return false;
    }

    // 注册到触发器映射表中
    this->mTickMap.Add(listenerID, delegater);

    // 返回成功
    return true;
}

bool UTickMgr::ContainTick(FString listenerID)
{
    return this->mTickMap.Contains(listenerID);
}

bool UTickMgr::UnregisterTick(FString listenerID)
{
    // 监听者id不存在
    if (listenerID.IsEmpty())
        return false;

    // Tick驱动中不包含此监听者
    if (!this->mTickMap.Contains(listenerID))
    {

        return false;
    }

    // 从驱动表中移除
    this->mTickMap.Remove(listenerID);

    // 返回成功
    return true;
}

