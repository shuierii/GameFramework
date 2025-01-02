#pragma once

UENUM(BlueprintType)
enum class EEventNodeStyle : uint8
{
    None UMETA(DisplayName = "无"),
    Trigger UMETA(DisplayName = "触发器"),
    Precondition UMETA(DisplayName = "前置条件"),
    Input UMETA(DisplayName = "输入器"),
    Output UMETA(DisplayName = "输出器"),
};
