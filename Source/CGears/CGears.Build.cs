// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CGears : ModuleRules
{
	public CGears(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AImodule", "GameplayTasks","ApexDestruction" });
	}
}
