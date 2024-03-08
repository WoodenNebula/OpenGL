project "OpenGL"
    language "C++"
    cppdialect "C++20"
    kind "ConsoleApp"

    filter "system:linux"
    targetname ("OpenGL.out")

    targetdir ("%{wks.location}/build/bin/" .. "%{wks.outputdir}" .. "/%{prj.name}")
    objdir ("%{wks.location}/build/obj/" .. "%{wks.outputdir}" .. "/%{prj.name}")

    includedirs {
        "dependencies",
        "dependencies/GL",
        "dependencies/glad",
        "dependencies/glfw",
        "src/vendor/"
    }

    libdirs {
        "dependencies/lib/GL",
        "dependencies/lib/GLFW",
    }

    files {
        "src/**.hpp", "src/**.h",
        "src/**.cpp", "src/**.c"
    }

    filter "system:linux"
        links {
            "Glad",
            "libglfw.so.3.3",
        }
    filter{}

    filter {"system:windows"}
        links {
            "Glad",
            "glew32s.lib",
            "GLFW3.lib",
            "opengl32.lib",
        }
    filter{}