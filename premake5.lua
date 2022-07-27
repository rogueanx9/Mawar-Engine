workspace "MawarEngine"
    architecture "x64"
	startproject "Sandbox"

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
IncludeDir["ImGui"] = "MawarEngine/vendor/imgui"
IncludeDir["glm"] = "MawarEngine/vendor/glm"

include "MawarEngine/vendor/GLFW"
include "MawarEngine/vendor/Glad"
include "MawarEngine/vendor/imgui"

project "MawarEngine"
	location "MawarEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mpch.hpp"
	pchsource "MawarEngine/src/mpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/glm/**.inl"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"GLFW",
		"GLad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"M_PLATFORM_W10",
			"M_BUILD_DLL",
			"M_ENABLE_ASSERT"
		}
		
		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\""
		}

	filter "configurations:Debug"
		runtime "Debug"
		defines "M_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		runtime "Release"
		defines "M_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		runtime "Release"
		defines "M_DIST"
		optimize "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"
	
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
		"MawarEngine/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}"
	}
	
	links
	{
		"MawarEngine"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"M_PLATFORM_W10",
		}

	filter "configurations:Debug"
		defines "M_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "M_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "M_DIST"
		runtime "Release"
		optimize "On"