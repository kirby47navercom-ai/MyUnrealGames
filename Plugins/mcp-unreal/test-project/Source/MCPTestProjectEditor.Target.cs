using UnrealBuildTool;

public class MCPTestProjectEditorTarget : TargetRules
{
	public MCPTestProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V7;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
		ExtraModuleNames.Add("MCPTestProject");
	}
}
