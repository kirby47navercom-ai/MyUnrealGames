using UnrealBuildTool;

public class MCPTestProjectTarget : TargetRules
{
	public MCPTestProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V7;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
		ExtraModuleNames.Add("MCPTestProject");
	}
}
