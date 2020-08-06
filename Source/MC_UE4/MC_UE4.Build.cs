// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class MC_UE4 : ModuleRules
{
	public MC_UE4(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"Sockets"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { 
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
		if(Target.Type == TargetType.Editor)
        {
			PrivateIncludePaths.Add(Path.Combine(GetPathToJDK(), "include"));

			if (
				Environment.OSVersion.Platform == PlatformID.Unix ||
				Environment.OSVersion.Platform == PlatformID.MacOSX
			)
			{
				// TODO set up linux libraries
			}
			else
			{
				PrivateIncludePaths.Add(Path.Combine(GetPathToJDK(), "include", "win32"));
				PublicAdditionalLibraries.Add(Path.Combine(GetPathToJDK(), "lib", "jvm.lib"));
				PublicDelayLoadDLLs.Add("jvm.dll");
			}
		}
	}

	public string GetPathToJDK()
    {
		string path = Environment.GetEnvironmentVariable("JAVA_HOME");
		if (path == null)
			throw new Exception("JAVA_HOME environment variable must be set.");

		return path;
    }
}
