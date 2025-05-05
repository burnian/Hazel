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
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on" -- "on" represents buildoptions "/MTd", "Off" represents buildoptions "/MDd"

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
		"%{IncludeDir.glm}",
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"HAZEL_PLATFORM_WINDOWS",
			"HAZEL_BUILD_DLL",
			"HAZEL_ENABLE_ASSERTS",
			"GLFW_INCLUDE_NONE"
		}

		-- postbuildcommands {
		-- 	-- fix the bug that error emerged the first time compile Hazel
		-- 	("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		-- }

	filter "configurations:Debug"
		defines "HAZEL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HAZEL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HAZEL_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Hazel/vendor",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
	}

	links {
		"Hazel"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"HAZEL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HAZEL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HAZEL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HAZEL_DIST"
		runtime "Release"
		optimize "on"
