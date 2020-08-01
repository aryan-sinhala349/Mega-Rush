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
		"%{prj.name}/src/**.cpp"
	}

	defines
	{

	}

	includedirs
	{
		"%{prj.name}/src"
	}

	links
	{
	
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
		"MegaRush/src"
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