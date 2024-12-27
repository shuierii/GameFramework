#pragma once
#include "EventAsset.h"

#include "Eventgraph.generated.h"

// 图标面板

UCLASS()
class EVENTEDITOR_API UEventGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	static UEdGraph* CreateGraph(UEventAsset* InEventAsset);

	UEventAsset* GetEventAsset() const;	// 获取当前表绑定的事件资产
};
