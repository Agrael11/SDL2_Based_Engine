cmake_minimum_required(VERSION 3.13)
set(PROJECT_AND_EXECATUBLE_NAME SDL_Engine_Base)
project(${PROJECT_AND_EXECATUBLE_NAME})
set (CMAKE_CXX_STANDARD 17)

set (ENGINE_SOURCE_FILES "./src/Engine/Helper/Logger.cpp"
"./src/Engine/Rendering/Sprite.cpp" "./src/Engine/Rendering/RenderTexture.cpp" "./src/Engine/Rendering/Renderer.cpp"
"./src/Engine/Audio/Audio.cpp" "./src/Engine/Audio/Music.cpp" "./src/Engine/Audio/Sound.cpp"
"./src/Engine/BaseGame.cpp" "./src/Engine/Support.cpp")
set (SOURCE_FILES "./src/Game.cpp" "./src/Main.cpp")

if (UNIX)
  if(CMAKE_CXX_COMPILER MATCHES "/em\\+\\+(-[a-zA-Z0-9.])?$")
    message("Emscripten")
    set(CMAKE_CXX_COMPILER_ID "Emscripten")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -sUSE_SDL_MIXER=2 -s SDL2_IMAGE_FORMATS=[\"png\"] --preload-file Assets")

  else()
    message("UNIX")

    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/linux/")

    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
  endif()
endif (UNIX)

if (WIN32)
  message("WINDOWS")
  find_package(SDL2 CONFIG REQUIRED)
  find_package(SDL2-image CONFIG REQUIRED)
  find_package(SDL2_mixer CONFIG REQUIRED)
endif (WIN32)


include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

add_executable(${PROJECT_AND_EXECATUBLE_NAME} ${ENGINE_SOURCE_FILES} ${SOURCE_FILES})

if (UNIX)
  target_link_libraries(${PROJECT_AND_EXECATUBLE_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
endif (UNIX)

if (WIN32)
  target_link_libraries(${PROJECT_AND_EXECATUBLE_NAME} PRIVATE ${SDL2_LIBRARIES} SDL2::SDL2_image SDL2_mixer::SDL2_mixer)
endif (WIN32)