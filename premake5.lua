workspace "Hazel"
	architecture "x64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["spdlog"] = "Hazel/vendor/spdlog/include"
IncludeDir["GLFW"] = "Hazel/vendor/glfw/include"
IncludeDir["Glad"] = "Hazel/vendor/glad/include"
IncludeDir["ImGui"] = "Hazel/vendor/imgui"
IncludeDir["glm"] = "Hazel/vendor/glm"

include "Hazel/vendor/glfw"
include "Hazel/vendor/glad"
include "Hazel/vendor/imgui"

project "Hazel"
	location "Hazel"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin_int/" .. outputdir .. "/%{prj.name}")

	pchheader"hazel_pch.h"
	pchsource"Hazel/src/hazel_pch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cc",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs {
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off" -- "On" represents buildoptions "/MTd", "Off" represents buildoptions "/MDd"
		systemversion "latest"

		defines {
			"HAZEL_PLATFORM_WINDOWS",
			"HAZEL_BUILD_DLL",
			"HAZEL_ENABLE_ASSERTS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			-- fix the bug that error emerged the first time compile Hazel
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "HAZEL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HAZEL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HAZEL_DIST"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin_int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cc",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Hazel/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}"
	}

	links {
		"Hazel"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"HAZEL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HAZEL_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "HAZEL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "HAZEL_DIST"
		buildoptions "/MD"
		optimize "On"
