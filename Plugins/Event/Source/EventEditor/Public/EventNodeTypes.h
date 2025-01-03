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

	// 输出
	static const FName NODE_TYPE_SCRIPT;

	// 行动
	static const FName NODE_TYPE_ACTION;

	// 对话
	static const FName NODE_TYPE_DIALOG;
	
	// Pin子类型: 共有
	static const FName PIN_SUB_TYPE_PUBLIC;

	// Pin子类型: 私有
	static const FName PIN_SUB_TYPE_PRIVATE;

	// Pin子类型: 对话节点-进入节点动作
	static const FName PIN_DIALOG_ACTION_OF_ENTER;

	// Pin子类型: 对话节点-退出节点动作
	static const FName PIN_DIALOG_ACTION_OF_EXIT;
};
