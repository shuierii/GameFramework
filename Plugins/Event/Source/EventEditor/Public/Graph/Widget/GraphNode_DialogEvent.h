#pragma once
#include "GraphNode_Base.h"

class EVENTEDITOR_API SGraphNode_DialogEvent : public SGraphNode_Base
{
public:
	virtual void CreateInputAddButton() override;
	virtual void CreateOutputAddButton() override;
};
