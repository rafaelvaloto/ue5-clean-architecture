// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class NewProjectTarget : TargetRules
{
	public NewProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		// DefaultBuildSettings = BuildSettingsVersion.V5;
		
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		Platform = UnrealTargetPlatform.Win64;

		ExtraModuleNames.AddRange( new string[] { "NewProject" } );
	}
}
