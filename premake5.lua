workspace "Hazel"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/glfw/include"

include "Hazel/vendor/glfw"

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
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}"
	}

	links {
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"HAZEL_PLATFORM_WINDOWS",
			"HAZEL_BUILD_DLL",
			"HAZEL_ENABLE_ASSERTS"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
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
		"Hazel/vendor/spdlog/include",
		"Hazel/src"
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
		symbols "On"

	filter "configurations:Release"
		defines "HAZEL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HAZEL_DIST"
		optimize "On"
