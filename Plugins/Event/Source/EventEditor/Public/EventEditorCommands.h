#pragma once

class EVENTEDITOR_API FEventGraphCommands final : public TCommands<FEventGraphCommands>
{
public:
	FEventGraphCommands();

	virtual void RegisterCommands() override;

public:
	/** Pins */
	TSharedPtr<FUICommandInfo> RemovePin;

	/** Jumps */
	TSharedPtr<FUICommandInfo> JumpToNodeDefinition;
};
