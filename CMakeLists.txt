include(config.cmake)
cmake_minimum_required(VERSION 3.20)

# set min mac os version for 10.7
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.7" CACHE STRING "Minimum OS X deployment version")

project(sdl2-test VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set source files
# file(GLOB SOURCES "src/*.cpp")
# file(GLOB HEADERS "src/*.h")
# set the path depending on if it is an app bundle or not
if (IS_APP_BUNDLE)
    set (FRAMEWORKS_PATH $<TARGET_FILE_DIR:sdl2-test>/../Frameworks)
    set (RESOURCES_PATH $<TARGET_FILE_DIR:sdl2-test>/../Resources)
    set (RPATH @executable_path/../Frameworks)
else ()
    set (FRAMEWORKS_PATH $<TARGET_FILE_DIR:sdl2-test>/Frameworks)
    set (RESOURCES_PATH $<TARGET_FILE_DIR:sdl2-test>/Resources)
    set (RPATH @executable_path/Frameworks)
endif ()
# same but also includes subdirectories like src/ECS (recursive)
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# set @rpath to be @executable_path/../Frameworks
set(CMAKE_BUILD_RPATH ${RPATH})

add_executable(sdl2-test ${SOURCES} ${HEADERS})

if (IS_APP_BUNDLE)
    # Set the executable to be a MACOSX_BUNDLE
    set_target_properties(sdl2-test PROPERTIES MACOSX_BUNDLE TRUE)
    # configure the Info.plist file
    set_target_properties(sdl2-test PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist.in)
else ()
    set_target_properties(sdl2-test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bundle)
endif ()

# set the include directory
# target_include_directories(
#   sdl2-test PRIVATE src/ECS
# )

target_include_directories(
  sdl2-test PRIVATE /usr/local/include/SDL2
)

target_link_libraries(
  # sdl2-test PRIVATE ${CMAKE_SOURCE_DIR}/Frameworks/libSDL2-2.0.0.dylib
  sdl2-test PRIVATE /usr/local/lib/libSDL2-2.0.0.dylib /usr/local/lib/libSDL2_image-2.0.801.0.0.dylib
)

# target_link_libraries(
#   sdl2-test PRIVATE /usr/local/lib/libSDL2_image-2.0.0.dylib
# )



# copy one dylib to app bundle into ../Frameworks 
add_custom_command(TARGET sdl2-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        # ${CMAKE_SOURCE_DIR}/Frameworks
        /usr/local/lib/libSDL2-2.0.0.dylib
        ${FRAMEWORKS_PATH}/libSDL2-2.0.0.dylib
)

# copy one dylib to app bundle into ../Frameworks
add_custom_command(TARGET sdl2-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        # ${CMAKE_SOURCE_DIR}/Frameworks
        /usr/local/lib/libSDL2_image-2.0.801.0.0.dylib
        ${FRAMEWORKS_PATH}/libSDL2_image-2.0.801.0.0.dylib
)

add_custom_command(TARGET sdl2-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources
        ${RESOURCES_PATH}
)



