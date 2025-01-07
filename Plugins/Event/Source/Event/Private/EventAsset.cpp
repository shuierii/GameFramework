#include "EventAsset.h"

UEventAsset::UEventAsset(const FObjectInitializer& ObjectInitializer)
{
	Root = nullptr;
	EventGraph = nullptr;
}

UEventNode_Base* UEventAsset::CreateNode(const UClass* NodeClass, UEdGraphNode* EdGraphNode)
{
	UEventNode_Base* NewNode = NewObject<UEventNode_Base>(this, NodeClass, NAME_None, RF_Transactional);

	NewNode->SetEdGraphNode(EdGraphNode);

	// TODO

	return NewNode;
}
