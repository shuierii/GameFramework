#pragma once
#include "EventNode_Base.h"
#include "EventNode_Script.generated.h"

UCLASS(DisplayName = "剧本")
class EVENT_API UEventNode_Script : public UEventNode_Base
{
	GENERATED_UCLASS_BODY() // 需要在.cpp实现构造函数，类成员对象默认是public
public:
	virtual FString GetNodeCategory() const override;
	virtual FString GetNodeType() override { return "E_Script"; };
};
