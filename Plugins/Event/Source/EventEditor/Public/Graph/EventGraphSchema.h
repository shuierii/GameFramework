#pragma once
#include "EventAsset.h"

#include "EventGraphSchema.generated.h"

// 委托
DECLARE_DELEGATE_TwoParams(FOnPinConnection, UEdGraphPin*, UEdGraphPin*) // PinA，PinB
DECLARE_MULTICAST_DELEGATE(FEventGraphSchemaRefresh);

// 图标面板编辑规则

UCLASS()
class EVENTEDITOR_API UEventGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public:
	// UEdGraphSchema
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;
	// END

public:
	static void BindAssetChangeActions();
	static UClass* GetAssignedEdGraphNodeClass(const UClass* EventNodeClass);

	static TArray<TSharedPtr<FString>> GetEventNodeCategories();
	static void GetPaletteActions(FGraphActionMenuBuilder& ActionMenuBuilder);

private:
	static void BindEventNodeActions(FGraphActionMenuBuilder& ActionMenuBuilder);

	static void GatherEventNodes();
	static void OnAssetAdded(const FAssetData& AssetData);
	static void OnAssetRemoved(const FAssetData& AssetData);

public:
	static FOnPinConnection OnPinConnection;
	static FEventGraphSchemaRefresh OnNodeListChanged;

private:
	static TArray<UClass*> NativeEventNodes; // 已创建的蓝图节点
	static TMap<UClass*, UClass*> AssignedEdGraphNodeClasses; // <EventNode,EdGraphNode>
	static TMap<FName, FAssetData> BlueprintEventNodes; // <资产名，蓝图资产>
};
