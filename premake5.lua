workspace "MegaRush"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include Directories
IncludeDir = {}
IncludeDir["spdlog"] = "MegaRush/vendor/spdlog/include"
IncludeDir["Glad"] = "MegaRush/vendor/Glad/include"
IncludeDir["glm"] = "MegaRush/vendor/glm"

group "Dependencies"
	include "MegaRush/vendor/Glad"
group ""

project "MegaRush"
	location "MegaRush"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		
		}

	filter "configurations:Debug"
		defines "MR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MR_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"MegaRush/src",
		"MegaRush/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}"
	}

	links
	{
		"MegaRush"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		
		}
		
	filter "configurations:Debug"
		defines "MR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MR_DIST"
		runtime "Release"
		optimize "on"