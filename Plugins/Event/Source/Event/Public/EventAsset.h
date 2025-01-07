#pragma once
#include "Node/EventNode_Base.h"
#include "Node/EventNode_EventRoot.h"

#include "EventAsset.generated.h"

// 编辑器信息通知
DECLARE_DELEGATE_OneParam(FOnGraphEditorNotification, FString&);

UCLASS(BlueprintType)
class EVENT_API UEventAsset : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UEdGraph* GetGraph() const { return EventGraph; }
	UEventNode_Base* CreateNode(const UClass* NodeClass, UEdGraphNode* EdGraphNode);

public:
	UPROPERTY()
	UEdGraph* EventGraph;

	UPROPERTY()
	UEventNode_EventRoot* Root;

	FOnGraphEditorNotification OnGraphEditorNotification;
};
