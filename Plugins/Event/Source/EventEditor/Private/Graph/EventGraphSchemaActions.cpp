﻿#include "Graph/EventGraphSchemaActions.h"

#include "EventAsset.h"
#include "Graph/EventGraph.h"
#include "Graph/EventGraphSchema.h"

#define LOCTEXT_NAMESPACE "FEventGraphSchema_Actions"

UEdGraphNode* FEventGraphSchemaActions_NewNode::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	if (GEditor && GEditor->PlayWorld)
	{
		return nullptr;
	}

	if (NodeClass)
	{
		UE_LOG(LogTemp, Log, TEXT("节点列表点击创建节点"));

		return CreateEdGraphNode(NodeClass, ParentGraph, FromPin, Location, bSelectNewNode);
	}

	return nullptr;
}

UEdGraphNode_Base* FEventGraphSchemaActions_NewNode::CreateEdGraphNode(const UClass* InNodeClass, UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, const bool bSelectNewNode)
{
	check(InNodeClass);

	UEventAsset* EventAsset = CastChecked<UEventGraph>(ParentGraph)->GetEventAsset();

	if (NodeClass->IsChildOf(UEventNode_EventRoot::StaticClass()) && EventAsset->Root != nullptr)
	{
		FString Msg = TEXT("已经存在【事件】，如果需要更改的话，请先删除再添加!");
		EventAsset->OnGraphEditorNotification.ExecuteIfBound(Msg);
		
		return nullptr;
	}

	UE_LOG(LogTemp, Log, TEXT("创建编辑器节点"));
	
	GEditor->BeginTransaction(LOCTEXT("AddNode", "Add Node"));
	ParentGraph->Modify();
	if (FromPin)
	{
		FromPin->Modify();
	}

	EventAsset->Modify();

	// 创建EdGraphNode
	const UClass* EdGraphNodeClass = UEventGraphSchema::GetAssignedEdGraphNodeClass(InNodeClass);
	UEdGraphNode_Base* NewEdGraphNode = NewObject<UEdGraphNode_Base>(ParentGraph, EdGraphNodeClass, NAME_None, RF_Transactional);
	NewEdGraphNode->CreateNewGuid();
	NewEdGraphNode->NodePosX = Location.X;
	NewEdGraphNode->NodePosY = Location.Y;
	ParentGraph->AddNode(NewEdGraphNode, false, bSelectNewNode);

	// 创建EventNode
	UEventNode_Base* NewNode = EventAsset->CreateNode(InNodeClass, NewEdGraphNode);
	NewEdGraphNode->SetEventNode(NewNode);

	if (NodeClass->IsChildOf(UEventNode_EventRoot::StaticClass()))
	{
		EventAsset->Root = CastChecked<UEventNode_EventRoot>(NewNode);
	}

	// 属性规则
	NewEdGraphNode->PostPlacedNewNode();
	NewEdGraphNode->AllocateDefaultPins();
	NewEdGraphNode->AutowireNewNode(FromPin);

	ParentGraph->NotifyGraphChanged();

	// TODO

	return NewEdGraphNode;
}

#undef LOCTEXT_NAMESPACE
