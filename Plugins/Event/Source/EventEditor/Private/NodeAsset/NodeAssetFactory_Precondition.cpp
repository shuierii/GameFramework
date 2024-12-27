#include "NodeAsset/NodeAssetFactory_Precondition.h"

#include "Blueprint/Blueprint_EventNode_Precondition.h"
#include "Node/EventNode_Precondition.h"
#include "Kismet2/KismetEditorUtilities.h"

#define LOCTEXT_NAMESPACE "UNodeAssetFactory_Precondition"

UNodeAssetFactory_Precondition::UNodeAssetFactory_Precondition(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	SupportedClass = UBlueprint_EventNode_Precondition::StaticClass(); // 资产右上角的类
	ParentClass = UEventNode_Precondition::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UNodeAssetFactory_Precondition::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(InClass->IsChildOf(UBlueprint_EventNode_Precondition::StaticClass()))

	if (ParentClass == nullptr || !FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass) || !ParentClass->IsChildOf(UEventNode_Precondition::StaticClass()))
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("ClassName"), ParentClass ? FText::FromString(ParentClass->GetName()) : LOCTEXT("Null", "(null)"));
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("打开错误！")));

		return nullptr;
	}

	UBlueprint_EventNode_Precondition* NewBP = CastChecked<UBlueprint_EventNode_Precondition>(FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, InName, BPTYPE_Normal, UBlueprint_EventNode_Precondition::StaticClass(), UBlueprintGeneratedClass::StaticClass()));

	UE_LOG(LogTemp, Log, TEXT("创建资产：前置条件"));
	
	return NewBP;
}

#undef LOCTEXT_NAMESPACE
