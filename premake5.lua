workspace "OpenGL"
    configurations { "Debug", "Release" }
    architecture "x64"
    location "./OpenGL/"

    filter "configurations:Debug"
    defines { "DEBUG", "_DEBUG" }
    symbols "On"
    filter{}

    filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
    filter{}

    filter "system:windows"
        defines { "WINDOWS" }
    filter{}

    filter "system:linux"
        defines { "LINUX" }
    filter{}


    outputdir = "%{cfg.architecture}-%{cfg.system}-%{cfg.buildcfg}"


    include "OpenGL/Project.lua"





newaction {
    trigger = "clean",
    description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        print("Cleaning Up:")
        os.chdir("OpenGL")

        os.rmdir("build")
        os.rmdir("./.vs")

        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.**")
        os.remove("**Makefile")
        os.remove("**.make")
        print("Success")
    end
}