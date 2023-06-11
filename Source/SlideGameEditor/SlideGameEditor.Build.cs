// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class SlideGameEditor : ModuleRules
{
	public SlideGameEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                Path.Combine(ModuleDirectory, "Public"),
                Path.Combine(ModuleDirectory, "."),
            });
        PrivateIncludePaths.AddRange(
            new string[]
            {
                Path.Combine(ModuleDirectory, "Private"),
                Path.Combine(ModuleDirectory, "."),
            });

        PublicDependencyModuleNames.AddRange(
            new string[] { 
			    "SlideGame",
                "Core",
                "CoreUObject",
                "Engine",
            });

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "UnrealEd",
            });
    }
}
