project "OpenGL"
    language "C++"
    cppdialect "C++20"
    kind "ConsoleApp"

    filter "system:linux"
    targetname ("OpenGL.out")

    targetdir ("%{wks.location}/build/bin/" .. "%{wks.outputdir}" .. "/%{prj.name}")
    objdir ("%{wks.location}/build/obj/" .. "%{wks.outputdir}" .. "/%{prj.name}")

    includedirs {
        "src",
        "src/vendor",
        "dependencies/glad/include",
        "dependencies/GLFW/include",

    }

    libdirs {
        "dependencies/GL/lib",
        "dependencies/GLFW/lib",
    }

    links {
        "glad",
    }


    files {
        "src/**.hpp", "src/**.h",
        "src/**.cpp", "src/**.c"
    }

    filter "system:linux"
        links {
            "GL",
            "glfw"
        }
    filter{}

    filter {"system:windows"}
        links {
            "opengl32.lib",
        }
    filter{}