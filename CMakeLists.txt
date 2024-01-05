include(config.cmake)
cmake_minimum_required(VERSION 3.20)

# set min mac os version for 10.7
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.7" CACHE STRING "Minimum OS X deployment version")

project(sdl2-test VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set source files
set(SOURCES src/main.cpp)

set (HEADERS src/include/Window.h src/include/Layer.h src/include/EventReceiver.h src/include/Button.h src/include/Application.h)

# Add your executable
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
target_include_directories(
  sdl2-test PRIVATE src/include
)

target_include_directories(
  sdl2-test PRIVATE /usr/local/include/SDL2
)

target_link_libraries(
  sdl2-test PRIVATE /usr/local/lib/libSDL2.dylib
)

# set the path depending on if it is an app bundle or not
if (IS_APP_BUNDLE)
    set (FRAMEWORKS_PATH $<TARGET_FILE_DIR:sdl2-test>/../Frameworks)
    set (RESOURCES_PATH $<TARGET_FILE_DIR:sdl2-test>/../Resources)
    set (RPATH @executable_path/../Frameworks)
else ()
    set (FRAMEWORKS_PATH $<TARGET_FILE_DIR:sdl2-test>)
    set (RESOURCES_PATH $<TARGET_FILE_DIR:sdl2-test>)
    set (RPATH @executable_path)
endif ()

# copy one dylib to app bundle into ../Frameworks 
add_custom_command(TARGET sdl2-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Frameworks
        ${FRAMEWORKS_PATH}
)

# copy one dylib to app bundle into ../Resources
add_custom_command(TARGET sdl2-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources
        ${RESOURCES_PATH}
)

# change path of the dylib in the executable to @executable_path/../Frameworks
add_custom_command(TARGET sdl2-test POST_BUILD
    COMMAND install_name_tool -change
    @rpath/libSDL2-2.0.0.dylib
    ${RPATH}/libSDL2-2.0.0.dylib
        $<TARGET_FILE:sdl2-test>
)
