#pragma once

#include "EventTypes.generated.h"

class UEventNode_Dialog;

UENUM(BlueprintType)
enum class EEventNodeStyle : uint8
{
	None UMETA(DisplayName = "无"),
	Trigger UMETA(DisplayName = "触发器"),
	Precondition UMETA(DisplayName = "前置条件"),
	Input UMETA(DisplayName = "输入器"),
	Output UMETA(DisplayName = "输出器"),
	DialogEvent UMETA(DisplayName = "对话事件"),
	Action UMETA(DisplayName = "行动"),
	Dialog UMETA(DisplayName = "对话"),
	Script UMETA(DisplayName = "剧本"),
};

USTRUCT(BlueprintType)
struct FDialogText
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, DisplayName = "选项ID")
	FString OptionID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "对话内容")
	FString Content;
};

USTRUCT()
struct FDialogOption
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FDialogText DialogText;

	UPROPERTY()
	UEventNode_Dialog* Dialog = nullptr;
};
