solution "2d-game-engine"
  configurations { "Debug", "Release" }

  project "2d-game-engine"
    kind "ConsoleApp"
    language "C++"
    files { "**.h", "**.cpp" }
    includedirs { "/" }

    configuration "windows"
      links {  "opengl32", "glew32", "DevIL", "GLFW"}

    configuration "linux"
      links { "GL", "glfw", "GLEW", "IL" }
      buildoptions { "-std=c++11" }

    configuration { "Debug", "vs*" }
      buildoptions { "/Za" }
    configuration { "Debug", "not vs*" }
      flags { "FatalWarnings" }

    configuration "Debug"
      defines { "DEBUG" }
      flags { "Symbols", "ExtraWarnings" }
    configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize" }
