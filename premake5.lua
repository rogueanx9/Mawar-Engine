workspace "MawarEngine"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include Dirs array
IncludeDir = {}
IncludeDir["GLFW"] = "MawarEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "MawarEngine/vendor/Glad/include"

include "MawarEngine/vendor/GLFW"
include "MawarEngine/vendor/Glad"

project "MawarEngine"
	location "MawarEngine"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mpch.hpp"
	pchsource "MawarEngine/src/mpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}
	
	links
	{
		"GLFW",
		"GLad",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"M_PLATFORM_W10",
			"M_BUILD_DLL",
			"M_ENABLE_ASSERT"
		}
		
		postbuildcommands
		{
			"{MKDIR} ../bin/" .. outputdir .. "/Sandbox/",
			"{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/"
		}

	filter "configurations:Debug"
		staticruntime "Off"
		runtime "Debug"
		buildoptions "/MDd"
		defines "M_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		staticruntime "Off"
		runtime "Release"
		buildoptions "/MD"
		defines "M_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		buildoptions "/MD"
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
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "M_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist"
		defines "M_DIST"
		buildoptions "/MD"
		optimize "On"