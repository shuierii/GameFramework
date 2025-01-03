#include "NodeAsset/NodeAssetFactory_Output.h"

#include "Blueprint/Blueprint_EventNode_Output.h"
#include "Node/EventNode_Output.h"
#include "Kismet2/KismetEditorUtilities.h"

#define LOCTEXT_NAMESPACE "UNodeAssetFactory_Output"

UNodeAssetFactory_Output::UNodeAssetFactory_Output(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	SupportedClass = UBlueprint_EventNode_Output::StaticClass();
	ParentClass = UEventNode_Output::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UNodeAssetFactory_Output::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(InClass->IsChildOf(UBlueprint_EventNode_Output::StaticClass()))

	if (ParentClass == nullptr || !FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass) || !ParentClass->IsChildOf(UEventNode_Output::StaticClass()))
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("ClassName"), ParentClass ? FText::FromString(ParentClass->GetName()) : LOCTEXT("Null", "(null)"));
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("打开错误！")));

		return nullptr;
	}

	UBlueprint_EventNode_Output* NewBP = CastChecked<UBlueprint_EventNode_Output>(FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, InName, BPTYPE_Normal, UBlueprint_EventNode_Output::StaticClass(), UBlueprintGeneratedClass::StaticClass()));

	UE_LOG(LogTemp, Log, TEXT("创建资产：输出"));
	
	return NewBP;
}

#undef LOCTEXT_NAMESPACE
