// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class NewProject : ModuleRules
{
	public NewProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "AITestSuite"});

		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"Engine",
			"CoreUObject",
			"InputCore",
			"EnhancedInput",
			"PoseSearch",
			"MotionWarping",
			"MotionTrajectory",
			"IKRig", "WindowsDualsense_ds5w",
		});

		// PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}