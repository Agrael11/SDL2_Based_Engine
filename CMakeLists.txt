cmake_minimum_required(VERSION 3.13)
set(PROJECT_AND_EXECATUBLE_NAME SDL_Engine_Base)
project(${PROJECT_AND_EXECATUBLE_NAME})
set (CMAKE_CXX_STANDARD 17)

set (USE_SDL2D false)

if (USE_SDL2D)
  message("Use SDL2D")
  add_compile_definitions(USE_SDL2D)
  set (RENDERER_SOURCE_FILES "./src/Engine/Rendering/2D/Sprite.cpp" "./src/Engine/Rendering/2D/RenderTexture.cpp" "./src/Engine/Rendering/2D/Renderer.cpp")
else ()
  if ((UNIX) AND (CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$"))
    message ("Use OpenGL ES")
    add_compile_definitions(USE_OPENGL_ES)
    set (RENDERER_SOURCE_FILES 
    "./src/Engine/Rendering/OpenGL_ES/Texture.cpp" "./src/Engine/Rendering/OpenGL_ES/ImageTexture.cpp" "./src/Engine/Rendering/OpenGL_ES/Sprite.cpp" "./src/Engine/Rendering/OpenGL_ES/RenderTexture.cpp" 
    "./src/Engine/Rendering/OpenGL_ES/Renderer.cpp" "./src/Engine/Rendering/OpenGL_ES/Shader.cpp"
    "./src/Engine/Rendering/OpenGL_ES/glad.c")
  else ()  
    message ("Use OpenGL")
    add_compile_definitions(USE_OPENGL)
    set (RENDERER_SOURCE_FILES
    "./src/Engine/Rendering/OpenGL/Texture.cpp" "./src/Engine/Rendering/OpenGL/ImageTexture.cpp" "./src/Engine/Rendering/OpenGL/RenderTexture.cpp" "./src/Engine/Rendering/OpenGL/Sprite.cpp"
    "./src/Engine/Rendering/OpenGL/Renderer.cpp" "./src/Engine/Rendering/OpenGL/Shader.cpp" 
    "./src/Engine/Rendering/OpenGL/glad.c")
  endif()
endif()


set (ENGINE_SOURCE_FILES "./src/Engine/Helper/Logger.cpp"
${RENDERER_SOURCE_FILES}
"./src/Engine/Audio/Audio.cpp" "./src/Engine/Audio/Music.cpp" "./src/Engine/Audio/Sound.cpp"
"./src/Engine/Math/Vector2f.cpp" "./src/Engine/Math/Vector2.cpp" "./src/Engine/Math/Vector3f.cpp" "./src/Engine/Math/Vector3.cpp" "./src/Engine/Math/Rectanglef.cpp" "./src/Engine/Math/Rectangle.cpp" "./src/Engine/Math/Color.cpp" "./src/Engine/Math/Colorf.cpp" "./src/Engine/Math/MathHelper.cpp"
"./src/Engine/BaseGame.cpp" "./src/Engine/Support.cpp")
set (GAME_SOURCE_FILES "./src/Game.cpp")
set (SOURCE_FILES ${ENGINE_SOURCE_FILES} ${GAME_SOURCE_FILES} "./src/Main.cpp")

if (UNIX)
  if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$")
    message("Emscripten")
    set(CMAKE_CXX_COMPILER_ID "Emscripten")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sFULL_ES2 -sMIN_WEBGL_VERSION=1 -sMAX_WEBGL_VERSION=2 --preload-file Assets")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -sUSE_SDL_MIXER=2 -s SDL2_IMAGE_FORMATS=[\"png\"]")

  else()
    message("UNIX")

    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/linux/")
    find_library(DL_LIBRARY libdl.so  )
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_net REQUIRED)
    find_package(OpenGL REQUIRED)
  endif()
endif (UNIX)

if (WIN32)
  message("WINDOWS")
  find_package(SDL2 CONFIG REQUIRED)
  find_package(SDL2-image CONFIG REQUIRED)
  find_package(SDL2_mixer CONFIG REQUIRED)
  find_package(SDL2_ttf CONFIG REQUIRED)
  find_package(sdl2-net CONFIG REQUIRED)
  find_package(glm CONFIG REQUIRED)
endif (WIN32)


if (UNIX)
  include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_net_INCLUDE_DIRS})

  add_executable(${PROJECT_AND_EXECATUBLE_NAME} ${SOURCE_FILES})

  target_link_libraries(${PROJECT_AND_EXECATUBLE_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${DL_LIBRARY})
endif (UNIX)

if (WIN32)
  include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_net_INCLUDE_DIRS})

  add_executable(${PROJECT_AND_EXECATUBLE_NAME} ${SOURCE_FILES})

  target_link_libraries(${PROJECT_AND_EXECATUBLE_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_image SDL2_mixer::SDL2_mixer SDL2::SDL2_net SDL2_ttf::SDL2_ttf glm::glm)
endif (WIN32)