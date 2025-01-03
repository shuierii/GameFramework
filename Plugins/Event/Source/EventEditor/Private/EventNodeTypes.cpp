#include "EventNodeTypes.h"

const FName FEventNodeTypes::NODE_TYPE_TRIGGER = FName(TEXT("Trigger"));
const FName FEventNodeTypes::NODE_TYPE_PRECONDITION = FName(TEXT("Precondition"));
const FName FEventNodeTypes::NODE_TYPE_INPUT = FName(TEXT("Input"));
const FName FEventNodeTypes::NODE_TYPE_OUTPUT = FName(TEXT("Output"));
const FName FEventNodeTypes::NODE_TYPE_SCRIPT = FName(TEXT("Script"));
const FName FEventNodeTypes::NODE_TYPE_ACTION = FName(TEXT("Action"));
const FName FEventNodeTypes::NODE_TYPE_DIALOG = FName(TEXT("Dialog"));

const FName FEventNodeTypes::PIN_SUB_TYPE_PUBLIC = FName(TEXT("Public"));
const FName FEventNodeTypes::PIN_SUB_TYPE_PRIVATE = FName(TEXT("Private"));

const FName FEventNodeTypes::PIN_DIALOG_ACTION_OF_ENTER = FName(TEXT("DialogActionOfEnter"));
const FName FEventNodeTypes::PIN_DIALOG_ACTION_OF_EXIT = FName(TEXT("DialogActionOfExit"));