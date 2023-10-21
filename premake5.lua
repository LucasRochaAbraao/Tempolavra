workspace "LearningWorkspace"
    configurations { "Debug", "Release" }

project "wordclock"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin/obj/%{cfg.buildcfg}"
    warnings "Extra"
    files { "src/**.cpp" }
    includedirs { "include" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
