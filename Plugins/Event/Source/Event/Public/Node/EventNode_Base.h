#pragma once
#include "EventTypes.h"

#include "EventNode_Base.generated.h"

class UEventNode_Input;
class UEventNode_Precondition;
class UEventNode_Output;

UCLASS(Abstract)
class EVENT_API UEventNode_Base : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	void SetEdGraphNode(UEdGraphNode* NewGraphNode);
	UEdGraphNode* GetEdGraphNode();

	virtual FString GetNodeCategory() const;
	virtual FText GetNodeTitle() const;
	virtual FText GetNodeToolTip() const;

	EEventNodeStyle GetNodeStyle() const { return NodeStyle; }

	virtual FString GetNodeType();
	UFUNCTION(BlueprintImplementableEvent)
	FString GetNodeType_Blueprint();

	virtual void ResetConnectData()
	{
		InputList.Empty();
		Precondition = nullptr;
		OutputList.Empty();
	}

public:
	UPROPERTY(Transient) // Transient 修饰，标识此属性不会被序列化即不会被保存到磁盘上
	UEventNode_Base* Parent;

	UPROPERTY()
	TArray<UEventNode_Input*> InputList;

	UPROPERTY()
	UEventNode_Precondition* Precondition;

	UPROPERTY()
	TArray<UEventNode_Output*> OutputList;

protected:
	UPROPERTY()
	FString Category;

	UPROPERTY(VisibleDefaultsOnly, Category = "EventNode")
	EEventNodeStyle NodeStyle;

private:
	UPROPERTY()
	UEdGraphNode* EventEdGraphNode;
};
