

using UnrealBuildTool;
using System.Collections.Generic;

public class FortTimeEditorTarget : TargetRules
{
	public FortTimeEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "FortTime" } );
	}
}
