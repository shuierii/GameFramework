#include "NodeAsset/NodeAssetFactory_Input.h"

#include "Blueprint/Blueprint_EventNode_Input.h"
#include "Node/EventNode_Input.h"
#include "Kismet2/KismetEditorUtilities.h"

#define LOCTEXT_NAMESPACE "UNodeAssetFactory_Input"

UNodeAssetFactory_Input::UNodeAssetFactory_Input(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	SupportedClass = UBlueprint_EventNode_Input::StaticClass();
	ParentClass = UEventNode_Input::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UNodeAssetFactory_Input::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(InClass->IsChildOf(UBlueprint_EventNode_Input::StaticClass()))

	if (ParentClass == nullptr || !FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass) || !ParentClass->IsChildOf(UEventNode_Input::StaticClass()))
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("ClassName"), ParentClass ? FText::FromString(ParentClass->GetName()) : LOCTEXT("Null", "(null)"));
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("打开错误！")));

		return nullptr;
	}

	UBlueprint_EventNode_Input* NewBP = CastChecked<UBlueprint_EventNode_Input>(FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, InName, BPTYPE_Normal, UBlueprint_EventNode_Input::StaticClass(), UBlueprintGeneratedClass::StaticClass()));

	UE_LOG(LogTemp, Log, TEXT("创建资产：输入"));

	return NewBP;
}

#undef LOCTEXT_NAMESPACE
