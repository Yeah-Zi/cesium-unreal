// Copyright 2020-2024 CesiumGS, Inc. and Contributors

using UnrealBuildTool;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

public class CesiumRuntime : ModuleRules
{
    public CesiumRuntime(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        ShadowVariableWarningLevel = WarningLevel.Off;

        PublicIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "../ThirdParty/include")
            }
        );

        PrivateIncludePaths.AddRange(
            new string[] {
              // ... add other private include paths required here ...
#if UE_5_1_OR_LATER
              // In UE5.1, we need to explicit add the renderer's private directory to the include
              // paths in order to be able to include ScenePrivate.h. GetModuleDirectory makes this
              // easy, but it isn't available in UE5.0 and earlier.
              Path.Combine(GetModuleDirectory("Renderer"), "Private")
#endif
            }
        );

        string libPrefix;
        string libPostfix;
        string platform;
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            platform = "Windows-x64";
            libPostfix = ".lib";
            libPrefix = "";
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            platform = "Darwin-x64";
            libPostfix = ".a";
            libPrefix = "lib";
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            platform = "Android-xaarch64";
            libPostfix = ".a";
            libPrefix = "lib";
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            platform = "Linux-x64";
            libPostfix = ".a";
            libPrefix = "lib";
        }
        else if(Target.Platform == UnrealTargetPlatform.IOS)
        {
            platform = "iOS-xarm64";
            libPostfix = ".a";
            libPrefix = "lib";
        }
        else {
            platform = "Unknown";
            libPostfix = ".Unknown";
            libPrefix = "Unknown";
        }

        string libPath = Path.Combine(ModuleDirectory, "../ThirdParty/lib/" + platform);

        string releasePostfix = "";
        string debugPostfix = "d";

        bool preferDebug = (Target.Configuration == UnrealTargetConfiguration.Debug || Target.Configuration == UnrealTargetConfiguration.DebugGame);
        string postfix = preferDebug ? debugPostfix : releasePostfix;

        string[] libs = new string[]
        {
            //Mirror
            "ScriptX",
            "v8.dll",
            "v8_libbase.dll",
            "v8_libplatform.dll",
            //Mirror,
            "async++",
            "Cesium3DTiles",
            "Cesium3DTilesContent",
            "Cesium3DTilesReader",
            "Cesium3DTilesSelection",
            "CesiumAsync",
            "CesiumIonClient",
            "CesiumGeometry",
            "CesiumGeospatial",
            "CesiumGltfReader",
            "CesiumGltfContent",
            "CesiumGltf",
            "CesiumJsonReader",
            "CesiumRasterOverlays",
            "CesiumQuantizedMeshTerrain",
            "CesiumUtility",
            "csprng",
            "draco",
            "ktx",
            //"MikkTSpace",
            "meshoptimizer",
            "modp_b64",
            "s2geometry",
            "spdlog",
            "sqlite3",
            "tinyxml2",
            "turbojpeg",
            "uriparser",
            "webpdecoder"

        };

        // Use our own copy of MikkTSpace on Android.
        if (Target.Platform == UnrealTargetPlatform.Android || Target.Platform == UnrealTargetPlatform.IOS)
        {
            libs = libs.Concat(new string[] { "MikkTSpace" }).ToArray();
            PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "../ThirdParty/include/mikktspace"));
        }

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            libs = libs.Concat(new string[] { "tidy_static", "zlibstatic" }).ToArray();
        }
        else
        {
            libs = libs.Concat(new string[] { "tidy", "z" }).ToArray();
        }

        if (preferDebug)
        {
            // We prefer Debug, but might still use Release if that's all that's available.
            foreach (string lib in libs)
            {
                string debugPath = Path.Combine(libPath, libPrefix + lib + debugPostfix + libPostfix);
                if (!File.Exists(debugPath))
                {
                    Console.WriteLine("Using release build of cesium-native because a debug build is not available.");
                    preferDebug = false;
                    postfix = releasePostfix;
                    break;
                }
            }
        }

        PublicAdditionalLibraries.AddRange(libs.Select(lib => Path.Combine(libPath, libPrefix + lib + postfix + libPostfix)));

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "RHI",
                "CoreUObject",
                "Engine",
                "MeshDescription",
                "StaticMeshDescription",
                "HTTP",
                "LevelSequence",
                "Projects",
                "RenderCore",
                "SunPosition",
                "DeveloperSettings",
                "UMG",
                "Renderer",
		            "InputCore",
                "JsonUtilities" ,
                "Json" ,
            }
        );

        // Use UE's MikkTSpace on non-Android
        if (Target.Platform != UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.Add("MikkTSpace");
        }


        PublicDefinitions.AddRange(
            new string[]
            {
                "SPDLOG_COMPILED_LIB",
                "LIBASYNC_STATIC",
                "GLM_FORCE_XYZW_ONLY",
                "GLM_FORCE_EXPLICIT_CTOR",
                "GLM_FORCE_SIZE_T_LENGTH",
                "TIDY_STATIC",
                "URI_STATIC_BUILD"
            }
        );

        PrivateDependencyModuleNames.Add("Chaos");

        if (Target.bBuildEditor == true)
        {
            PublicDependencyModuleNames.AddRange(
                new string[] {
                    "UnrealEd",
                    "Slate",
                    "SlateCore",
                    "WorldBrowser",
                    "ContentBrowser",
                    "MaterialEditor"
                }
            );
        }

        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // ... add any modules that your module loads dynamically here ...
            }
        );

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Private/PCH.h";

#if UE_5_4_OR_LATER
        CppStandard = CppStandardVersion.Cpp20;
#else
        CppStandard = CppStandardVersion.Cpp17;
#endif
        bEnableExceptions = true;



    {
      //临时解决cmake中定义的SCRIPTX_BACKEND_TRAIT_PREFIX宏未被识别的未知问题
      PrivateDefinitions.Add("SCRIPTX_BACKEND_TRAIT_PREFIX = ../backend/V8/trait/Trait");
      PublicDefinitions.Add("SCRIPTX_BACKEND_TRAIT_PREFIX = ../backend/V8/trait/Trait");
      //临时解决editor模式下bEnableUndefinedIdentifierWarnings = false;未生效，无法以0替换未定义宏的未知问题
      PublicDefinitions.AddRange(
            new string[]
            {
              "V8_HAS_ATTRIBUTE_ALWAYS_INLINE = 0",
              "V8_HAS_ATTRIBUTE_NOINLINE = 0",
              "V8_HAS_BUILTIN_EXPECT = 0",
              "V8_HAS_ATTRIBUTE_WARN_UNUSED_RESULT = 0",
              "USING_V8_SHARED = 0",
              "V8_OS_POSIX = 0"
            }
        );
      // bin
      string DllPath = Path.Combine(ModuleDirectory, "../ThirdParty/bin");
      string TargetOutputDir = Path.Combine(ModuleDirectory, "..", "..", "Binaries", Target.Platform.ToString());

      foreach (string DllFile in Directory.EnumerateFiles(DllPath, "*.*", SearchOption.AllDirectories))
      {
        RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)", Path.GetFileName(DllFile)), Path.Combine(DllPath, DllFile));
      }
      // 设置需要打包的目录路径
      string DirectoryToPackage = Path.Combine(ModuleDirectory, "../../Content/Javascript");
      System.Console.WriteLine("YOYYY: " + DirectoryToPackage);

      // 检查目录是否存在
      if (Directory.Exists(DirectoryToPackage))
      {
        // 获取该目录下的所有文件，并添加到 RuntimeDependencies
        foreach (string File in Directory.GetFiles(DirectoryToPackage, "*.*", SearchOption.AllDirectories))
        {
          RuntimeDependencies.Add(Path.Combine(Path.Combine(DirectoryToPackage,"/") , File));
          System.Console.WriteLine("YOYYY: " + Path.Combine(Path.Combine(DirectoryToPackage, "/"), File));
        }
      }
      else
      {
        System.Console.WriteLine("Directory does not exist: " + DirectoryToPackage);
      }


      PublicIncludePaths.AddRange(
          new string[] {
                      Path.Combine(ModuleDirectory, "../ThirdParty/include"),
                      Path.Combine(ModuleDirectory, "../ThirdParty/include/v8")
          }
      );


    }

  }
}
