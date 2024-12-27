#include "NodeAsset/NodeAssetFactory_Trigger.h"

#include "Blueprint/Blueprint_EventNode_Trigger.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Node/EventNode_Trigger.h"

#define LOCTEXT_NAMESPACE "UEventNodeFactory_Trigger"

UNodeAssetFactory_Trigger::UNodeAssetFactory_Trigger(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	SupportedClass = UBlueprint_EventNode_Trigger::StaticClass();	// 资产右上角的类
	ParentClass = UEventNode_Trigger::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UNodeAssetFactory_Trigger::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(InClass->IsChildOf(UBlueprint_EventNode_Trigger::StaticClass()))

	if (ParentClass == nullptr || !FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass) || !ParentClass->IsChildOf(UEventNode_Trigger::StaticClass()))
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("ClassName"), ParentClass ? FText::FromString(ParentClass->GetName()) : LOCTEXT("Null", "(null)"));
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("打开错误！")));

		return nullptr;
	}

	UBlueprint_EventNode_Trigger* NewBP = CastChecked<UBlueprint_EventNode_Trigger>(FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, InName, BPTYPE_Normal, UBlueprint_EventNode_Trigger::StaticClass(), UBlueprintGeneratedClass::StaticClass()));

	return NewBP;
}

#undef LOCTEXT_NAMESPACE
