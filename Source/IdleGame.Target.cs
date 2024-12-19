// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class IdleGameTarget : TargetRules
{
    public IdleGameTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;

        // Use the latest build settings and include order
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        // Ensure a unique build environment to avoid conflicts
        BuildEnvironment = TargetBuildEnvironment.Shared;

        bOverrideBuildEnvironment = true;

        ExtraModuleNames.AddRange(new string[] { "IdleGame" });
    }
}
