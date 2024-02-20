
local rootPath = path.getabsolute(".")
require "cmake"
require "clion"

workspace "D7048E"
    architecture "x64"
    startproject "App"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["GLFW"] = "App/vendor/GLFW/include"
    IncludeDir["Glad"] = "App/vendor/Glad/include"
    IncludeDir["ImGui"] = "App/vendor/imgui"
    IncludeDir["glm"] = "App/vendor/glm"
    IncludeDir["LeapSDK"] = "App/vendor/LeapSDK/include"

group "Dependencies"
    include "App/vendor/GLFW"
    include "App/vendor/Glad"
    include "App/vendor/imgui"
group ""

project "App"
    location "App"
    kind "ConsoleApp"
    staticruntime "off"
    language "C++"
    cppdialect "C++17"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    removefiles
    {
        "%{prj.name}/src/Platform/**"
    }

    libdirs
    {
        "%{prj.name}/vendor/GLFW/lib-vc2022",
        "%{prj.name}/vendor/LeapSDK/lib/x64"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "LeapC"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "ROOT_PATH=\"" .. rootPath .. "/" .. "%{prj.name}\""
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.LeapSDK}",
        "%{prj.name}/src",
    }

    filter "system:windows"
        systemversion "latest"
        defines
        {
            "PLATFORM_WINDOWS",
            "BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }
        
        links 
        {
            "opengl32.lib"
        }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "DIST"
        runtime "Release"
        optimize "on"
