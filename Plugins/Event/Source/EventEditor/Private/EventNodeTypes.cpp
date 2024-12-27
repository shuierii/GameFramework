#include "EventNodeTypes.h"

const FName FEventNodeTypes::NODE_TYPE_TRIGGER = FName(TEXT("Trigger"));
const FName FEventNodeTypes::NODE_TYPE_PRECONDITION = FName(TEXT("Precondition"));
const FName FEventNodeTypes::NODE_TYPE_INPUT = FName(TEXT("Input"));
const FName FEventNodeTypes::NODE_TYPE_OUTPUT = FName(TEXT("Output"));

const FName FEventNodeTypes::PIN_SUB_TYPE_PUBLIC = FName(TEXT("Public"));
const FName FEventNodeTypes::PIN_SUB_TYPE_PRIVATE = FName(TEXT("Private"));