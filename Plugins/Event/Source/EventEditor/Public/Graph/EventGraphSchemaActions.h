#pragma once
#include "Node/EdGraphNode_Event.h"

#include "EventGraphSchemaActions.generated.h"

USTRUCT()
struct EVENTEDITOR_API FEventGraphSchemaActions_NewNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY()

public:
	FEventGraphSchemaActions_NewNode(): FEdGraphSchemaAction(), NodeClass(nullptr)
	{
	}

	FEventGraphSchemaActions_NewNode(UClass* Node): FEdGraphSchemaAction(), NodeClass(Node)
	{
	}

	FEventGraphSchemaActions_NewNode(const UEventNode_Base* Node)
		: FEdGraphSchemaAction(FText::FromString(Node->GetNodeCategory()), Node->GetNodeTitle(), Node->GetNodeToolTip(), 0, FText::FromString(Node->GetClass()->GetMetaData("Keywords")))
		, NodeClass(Node->GetClass())
	{
	}

	// FEdGraphSchemaAction
	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	// END

	UEdGraphNode_Event* CreateEdGraphNode(const UClass* InNodeClass, UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, const bool bSelectNewNode = true);

public:
	UPROPERTY()
	UClass* NodeClass;
};
