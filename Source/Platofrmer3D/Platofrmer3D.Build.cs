// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Platofrmer3D : ModuleRules
{
	public Platofrmer3D(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
	}
}
