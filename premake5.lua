workspace "MawarEngine"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "MawarEngine"
	location "MawarEngine"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
	}
	
	includedirs
	{
		"src",
		"%{prj.name}/vendor/spdlog/include"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"M_PLATFORM_W10",
			"M_BUILD_DLL"
		}
		
		postbuildcommands
		{
			"{MKDIR} ../bin/" .. outputdir .. "/Sandbox/",
			"{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/"
		}

	filter "configurations:Debug"
		defines "M_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "M_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "M_DIST"
		optimize "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
	}
	
	includedirs
	{
		"MawarEngine/vendor/spdlog/include",
		"MawarEngine/src"
	}
	
	links
	{
		"MawarEngine"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"M_PLATFORM_W10",
		}

	filter "configurations:Debug"
		defines "M_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "M_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "M_DIST"
		optimize "On"