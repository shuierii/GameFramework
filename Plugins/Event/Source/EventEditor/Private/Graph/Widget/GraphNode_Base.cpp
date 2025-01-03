#include "Graph/Widget/GraphNode_Base.h"

#include "EventEditorStyle.h"
#include "GraphEditorSettings.h"
#include "SCommentBubble.h"
#include "SLevelOfDetailBranchNode.h"
#include "Graph/Widget/GraphPin_Event.h"

void SGraphNode_Base::Construct(const FArguments& InArgs, UEdGraphNode_Base* InNode)
{
	this->GraphNode = InNode;
	this->EventGraphNode = InNode;

	this->SetCursor(EMouseCursor::CardinalCross);
	this->UpdateGraphNode();
}

void SGraphNode_Base::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();
	LeftNodeBox.Reset();
	RightNodeBox.Reset();

	// 上方布局
	TSharedRef<SCommentBubble> CommentBubble = StaticCastSharedRef<SCommentBubble>(CreateCommentBubble());
	GetOrAddSlot(ENodeZone::TopCenter)
		.SlotOffset(TAttribute<FVector2D>(CommentBubble, &SCommentBubble::GetOffset))
		.SlotSize(TAttribute<FVector2D>(CommentBubble, &SCommentBubble::GetSize))
		.AllowScaling(TAttribute<bool>(CommentBubble, &SCommentBubble::IsScalingAllowed))
		.VAlign(VAlign_Top)
		[
			CommentBubble
		];

	// 中间布局
	const TSharedPtr<SVerticalBox> InnerVerticalBox = SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		  .AutoHeight()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Top)
		  .Padding(Settings->GetNonPinNodeBodyPadding())
		[
			CreateNodeTitle()
		]
		+ SVerticalBox::Slot()
		  .AutoHeight()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Top)
		[
			CreateNodeBody()
		];

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
	    .HAlign(HAlign_Center)
	    .VAlign(VAlign_Center)
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.Padding(Settings->GetNonPinNodeBodyPadding())
			[
				SNew(SImage)
				.Image(FEventEditorStyle::GetBrush("Event.Node.Body"))
				.ColorAndOpacity(this, &SGraphNode::GetNodeBodyColor)
			]
			+ SOverlay::Slot()
			[
				InnerVerticalBox.ToSharedRef()
			]
		]
	];

	// 引脚
	CreatePinWidgets();

	// 输入
	CreateInputAddButton();

	// 输出
	CreateOutputAddButton();
}

void SGraphNode_Base::CreateStandardPinWidget(UEdGraphPin* Pin)
{
	const TSharedPtr<SGraphPin> NewPin = SNew(SGraphPin_Event, Pin);

	AddPin(NewPin.ToSharedRef());
}

TSharedRef<SWidget> SGraphNode_Base::CreateCommentBubble()
{
	const FSlateColor CommentColor = GetDefault<UGraphEditorSettings>()->DefaultCommentNodeTitleColor;

	return SNew(SCommentBubble)
	.GraphNode(GraphNode)
	.Text(this, &SGraphNode::GetNodeComment)
	.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
	.OnToggled(this, &SGraphNode::OnCommentBubbleToggled)
	.ColorAndOpacity(CommentColor)
	.AllowPinning(true)
	.EnableTitleBarBubble(true)
	.EnableBubbleCtrls(true)
	.GraphLOD(this, &SGraphNode::GetCurrentLOD)
	.IsGraphNodeHovered(this, &SGraphNode::IsHovered);
}

TSharedRef<SWidget> SGraphNode_Base::CreateNodeTitle()
{
	IconColor = FLinearColor::White;
	const FSlateBrush* IconBrush = nullptr;
	if (GraphNode && GraphNode->ShowPaletteIconOnNode())
	{
		IconBrush = GraphNode->GetIconAndTint(IconColor).GetOptionalIcon();
	}

	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	const TSharedRef<SOverlay> DefaultTitleAreaWidget =
		SNew(SOverlay)
		+ SOverlay::Slot()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Center)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Fill)
			[
				SNew(SBorder)
				.BorderImage(FEventEditorStyle::GetBrush("Event.Node.Title"))
				.Padding(FMargin(10, 5, 30, 3))
				.BorderBackgroundColor(this, &SGraphNode::GetNodeTitleColor)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					  .VAlign(VAlign_Top)
					  .Padding(FMargin(0.f, 0.f, 4.f, 0.f))
					  .AutoWidth()
					[
						SNew(SImage)
						.Image(IconBrush)
						.ColorAndOpacity(this, &SGraphNode::GetNodeTitleIconColor)
					]
					+ SHorizontalBox::Slot()
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SGraphNode::CreateTitleWidget(NodeTitle)
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							NodeTitle.ToSharedRef()
						]
					]
				]
			]
		];

	SetDefaultTitleAreaWidget(DefaultTitleAreaWidget);

	return SNew(SLevelOfDetailBranchNode)
	.UseLowDetailSlot(this, &SGraphNode_Base::UseLowDetailNodeTitles)
	.LowDetail()
		[
			SNew(SBorder)
				.BorderImage(FEventEditorStyle::GetBrush("Event.Node.Title"))
				.Padding(FMargin(75.0f, 22.0f))
				.BorderBackgroundColor(this, &SGraphNode::GetNodeTitleColor)
		]
		.HighDetail()
		[
			DefaultTitleAreaWidget
		];
}

TSharedRef<SWidget> SGraphNode_Base::CreateNodeBody()
{
	return SNew(SBorder)
	.BorderImage(FEditorStyle::GetBrush("NoBorder"))
   .HAlign(HAlign_Fill)
   .VAlign(VAlign_Fill)
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBorder)
			.BorderImage(FEventEditorStyle::GetBrush("Event.Node.Desc"))
			.BorderBackgroundColor(FLinearColor(0.04, 0.04, 0.04, 1))
			// Visibility_Lambda TODO
			[
				SNew(STextBlock)
				//  Text_Lambda TODO
				// Visibility_Lambda TODO
			]
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			// left
			+ SHorizontalBox::Slot()
			  .HAlign(HAlign_Left)
			  .FillWidth(1.0f)
			[
				SAssignNew(LeftNodeBox, SVerticalBox)
			]
			// Right
			+ SHorizontalBox::Slot()
			  .HAlign(HAlign_Right)
			  .AutoWidth()
			[
				SAssignNew(RightNodeBox, SVerticalBox)
			]
		]
	];
}
