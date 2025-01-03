#include "Graph/Widget/GraphNode_DialogEvent.h"

#include "GraphEditorSettings.h"

#define LOCTEXT_NAMESPACE "SGraphNode_DialogEvent"

void SGraphNode_DialogEvent::CreateInputAddButton()
{
	TSharedPtr<SWidget> AddPinWidget;
	SAssignNew(AddPinWidget, SHorizontalBox) // SAssignNew 是虚幻引擎（Unreal Engine）中 Slate UI 编程的一个宏，它用于创建 Slate 组件（Widget）的实例，并将这个实例赋值给一个指定的变量
		+ SHorizontalBox::Slot()
		  .AutoWidth()
		  .VAlign(VAlign_Center)
		  .Padding(0, 0, 7, 0)
		[
			SNew(SImage)
			.Image(FEditorStyle::GetBrush(TEXT("PropertyWindow.Button_AddToArray")))
		]
		+ SHorizontalBox::Slot()
		  .AutoWidth()
		  .HAlign(HAlign_Left)
		[
			SNew(STextBlock)
		.Text(LOCTEXT("SGraphNode_DialogEvent_AddTrigger", "添加触发器"))
		.ColorAndOpacity(FLinearColor::White)
		];

	auto OnAddBtnClick = [this]()-> FReply
	{
		EventGraphNode->CreateInputPin(TEXT("触发器"), FEventNodeTypes::NODE_TYPE_TRIGGER, true);

		return FReply::Handled();
	};

	const TSharedRef<SButton> AddPinButton =
		SNew(SButton)
	.ContentPadding(0.0f)
	.ButtonStyle(FEditorStyle::Get(), "NoBorder")
	.OnClicked_Lambda(OnAddBtnClick)
		[
			AddPinWidget.ToSharedRef()
		];

	AddPinButton->SetCursor(EMouseCursor::Hand); // 设置鼠标悬停为 手 的样式

	FMargin AddPinPadding = Settings->GetInputPinPadding();
	AddPinPadding.Top += 6.0f;

	// Add AddBtn
	LeftNodeBox->AddSlot()
	           .AutoHeight()
	           .VAlign(VAlign_Center)
	           .Padding(AddPinPadding)
	[
		AddPinButton
	];
}

void SGraphNode_DialogEvent::CreateOutputAddButton()
{
	// AddBtn
	TSharedPtr<SWidget> AddPinWidget;
	SAssignNew(AddPinWidget, SHorizontalBox)
		+ SHorizontalBox::Slot()
		  .AutoWidth()
		  .HAlign(HAlign_Left)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("SGraphNode_DialogEvent_AddScript", "添加剧本"))
			.ColorAndOpacity(FLinearColor::White)
		]
		+ SHorizontalBox::Slot()
		  .AutoWidth()
		  .VAlign(VAlign_Center)
		  .Padding(7, 0, 0, 0)
		[
			SNew(SImage)
			.Image(FEditorStyle::GetBrush(TEXT("PropertyWindow.Button_AddToArray")))
		];

	auto OnAddBtnClick = [this]()-> FReply
	{
		EventGraphNode->CreateOutputPin(TEXT("剧本"), FEventNodeTypes::NODE_TYPE_SCRIPT, FEventNodeTypes::NODE_TYPE_SCRIPT, true);

		return FReply::Handled();
	};

	const TSharedRef<SButton> AddPinButton =
		SNew(SButton)
		.ContentPadding(0.0f)
		.ButtonStyle(FEditorStyle::Get(), "NoBorder")
		.OnClicked_Lambda(OnAddBtnClick)
		[
			AddPinWidget.ToSharedRef()
		];

	AddPinButton->SetCursor(EMouseCursor::Hand);

	FMargin AddPinPadding = Settings->GetOutputPinPadding();
	AddPinPadding.Top += 6.0f;

	// Add AddBtn
	RightNodeBox->AddSlot()
	            .AutoHeight()
	            .VAlign(VAlign_Center)
	            .HAlign(HAlign_Right)
	            .Padding(AddPinPadding)
	[
		AddPinButton
	];
}

#undef LOCTEXT_NAMESPACE
