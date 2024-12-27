#pragma once

class EVENTEDITOR_API FEventNodeTypes
{
public:
	// 触发器
	static const FName NODE_TYPE_TRIGGER;

	// 前置条件
	static const FName NODE_TYPE_PRECONDITION;

	// 输入
	static const FName NODE_TYPE_INPUT;

	// 输出
	static const FName NODE_TYPE_OUTPUT;

	// Pin子类型: 共有
	static const FName PIN_SUB_TYPE_PUBLIC;

	// Pin子类型: 私有
	static const FName PIN_SUB_TYPE_PRIVATE;
};
