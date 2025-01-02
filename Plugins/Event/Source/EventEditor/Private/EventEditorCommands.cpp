#include "EventEditorCommands.h"

#define LOCTEXT_NAMESPACE "FEventToolbarCommands"

FEventGraphCommands::FEventGraphCommands(): TCommands("EventGraph",LOCTEXT("EventGraph", "Event Graph"), NAME_None, FEditorStyle::GetStyleSetName())
{
}

void FEventGraphCommands::RegisterCommands()
{
	UI_COMMAND(RemovePin, "Remove Pin", "Remove a pin from the node", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(JumpToNodeDefinition, "Jump to Node Definition", "Jump to the node definition", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
