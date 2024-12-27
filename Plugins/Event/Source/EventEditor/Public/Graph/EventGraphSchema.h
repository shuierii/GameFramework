#pragma once
#include "EventAsset.h"

#include "EventGraphSchema.generated.h"

// 图标面板编辑规则

UCLASS()
class EVENTEDITOR_API UEventGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public:
	// UEdGraphSchema
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	// END

public:
	static void BindAssetChangeActions();
	static UClass* GetAssignedEdGraphNodeClass(const UClass* EventNodeClass);

private:
	static void BindEventNodeActions(FGraphActionMenuBuilder& ActionMenuBuilder);

	static void GatherEventNodes();
	static void OnAssetAdded(const FAssetData& AssetData);
	static void OnAssetRemoved(const FAssetData& AssetData);

private:
	static TArray<UClass*> NativeEventNodes;	// 已创建的蓝图节点
	static TMap<UClass*, UClass*> AssignedEdGraphNodeClasses; // <EventNode,EdGraphNode>
	static TMap<FName, FAssetData> BlueprintEventNodes; // <资产名，蓝图资产>
};
