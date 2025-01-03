#include "NodeAsset/NodeAssetFactory_Action.h"

#include "Blueprint/Blueprint_EventNode_Action.h"
#include "Node/EventNode_Action.h"
#include "Kismet2/KismetEditorUtilities.h"

#define LOCTEXT_NAMESPACE "UNodeAssetFactory_Action"

UNodeAssetFactory_Action::UNodeAssetFactory_Action(const FObjectInitializer& ObjectInitializer)
{
	SupportedClass = UBlueprint_EventNode_Action::StaticClass();
	ParentClass = UEventNode_Action::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UNodeAssetFactory_Action::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(InClass->IsChildOf(UBlueprint_EventNode_Action::StaticClass()))

	if (ParentClass == nullptr || !FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass) || !ParentClass->IsChildOf(UEventNode_Action::StaticClass()))
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("ClassName"), ParentClass ? FText::FromString(ParentClass->GetName()) : LOCTEXT("Null", "(null)"));
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("打开错误！")));

		return nullptr;
	}

	UBlueprint_EventNode_Action* NewBP = CastChecked<UBlueprint_EventNode_Action>(FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, InName, BPTYPE_Normal, UBlueprint_EventNode_Action::StaticClass(), UBlueprintGeneratedClass::StaticClass()));

	UE_LOG(LogTemp, Log, TEXT("创建资产：行动"));

	return NewBP;
}

#undef LOCTEXT_NAMESPACE
