solution "2d-game-engine"
  configurations { "Debug", "Release" }

  project "2d-game-engine"
    kind "ConsoleApp"
    language "C++"
    files { "**.h", "**.cpp" }
    files { "helper/rendering/**.h", "helper/rendering/**.cpp" }
    files { "systems/**.h", "systems/**.cpp" }
    files { "components/**.h", "components/**.cpp" }
    includedirs { "/" }

    configuration "windows"
      links { "glu32", "opengl32", "gdi32", "winmm", "user32", "GLEW" }

    configuration "linux"
      links { "GL", "glfw", "GLEW", "IL" }
      buildoptions { "-std=c++11" }

    configuration "Debug"
      defines { "DEBUG" }
      flags { "Symbols", "ExtraWarnings", "FatalWarnings" }
    configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize" }
