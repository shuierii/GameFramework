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

class EVENTEDITOR_API FEventToolbarCommands final : public TCommands<FEventToolbarCommands>
{
public:
	FEventToolbarCommands();
	
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> ExportData;
};
