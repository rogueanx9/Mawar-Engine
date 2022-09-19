workspace "MawarEngine"
    architecture "x64"
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

-- Include Dirs array
IncludeDir = {}
IncludeDir["spdlog"] = "MawarEngine/vendor/spdlog/include"
IncludeDir["GLFW"] = "MawarEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "MawarEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "MawarEngine/vendor/imgui"
IncludeDir["glm"] = "MawarEngine/vendor/glm"
IncludeDir["stb"] = "MawarEngine/vendor/stb"

include "MawarEngine/vendor/GLFW"
include "MawarEngine/vendor/Glad"
include "MawarEngine/vendor/imgui"

project "MawarEngine"
	location "MawarEngine"
	kind "StaticLib"
	language "C++"
	staticruntime "on"
	cppdialect "C++17"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mpch.hpp"
	pchsource "MawarEngine/src/mpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/vendor/stb/**.cpp",
		"%{prj.name}/vendor/stb/**.h",
		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}"
	}
	
	links
	{
		"GLFW",
		"GLad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		defines "M_DEBUG"
		symbols "on"
		
	filter "configurations:Release"
		runtime "Release"
		defines "M_RELEASE"
		optimize "on"
		
	filter "configurations:Dist"
		runtime "Release"
		defines "M_DIST"
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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
	}
	
	includedirs
	{
		"%{IncludeDir.spdlog}",
		"MawarEngine/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}"
	}
	
	links
	{
		"MawarEngine"
	}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "M_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "M_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "M_DIST"
		runtime "Release"
		optimize "on"