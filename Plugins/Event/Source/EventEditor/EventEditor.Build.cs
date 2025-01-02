using UnrealBuildTool;

public class EventEditor : ModuleRules
{
	public EventEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"AssetTools",
				"UnrealEd",
				"Event",
				"GraphEditor",
				"PropertyEditor",
				"EditorStyle",
				"ToolMenus",
				"KismetWidgets",
				"Projects",
				"DeveloperSettings",
				"ApplicationCore"
			}
		);
	}
}