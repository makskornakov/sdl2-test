# C++ SDL2 template
## Including SDL2
SDL2 can be included in several ways, including building it from [Source code](https://github.com/libsdl-org/SDL/releases). The source code includes Config file so that the build is optimized for your machine, however I changed a couple of things for the build to work on various (MacOS in my case) machines. In the CMakeLists.txt I have added this line:
```
if(APPLE)
  set(CMAKE_OSX_DEPLOYMENT_TARGET "10.7" CACHE STRING "Minimum OS X deployment version")
endif()
```
*10.7 is the minimum version supported by current SDL2 framework*

I then navigated into downloaded source code folder, and run:
```
mkdir build
cd build
cmake -DCMAKE_OSX_ARCHITECTURES=x86_64;arm64 ..
```
*The falg is there for the build to be suitable for both arm and intel architectures*
```
make
```
Now there are 2 ways:
1. Just copy the executable and the include folder in your project and refer to it accordingly (explained below)
2. install SDL2 that you just built into your system (a reusable way)

#### Installing SDL2
```
sudo make install
```
and to see where was it installed:
```
sdl2-config --cflags --libs
```
#### Configuring CMake
There are 2 things left to do:
1. Include the library and its headers
2. (optional) If you want your user to be able to run the executable without installing SDL you can include it in the build:

I am building a MacOS app, so my build structure will be like this:
```
YourApp.app/
├── Contents/
│ ├── MacOS/
│ │ └── YourExecutable
│ ├── Resources/ (optional)
│ └── Info.plist
└── 
```
I will copy SDL2 to ../Frameworks folder, considering the app structure
```
set (FRAMEWORKS_PATH $<TARGET_FILE_DIR:sdl2-test>/../Frameworks)

add_custom_command(TARGET sdl2-test POST_BUILD
	COMMAND  ${CMAKE_COMMAND} -E copy
	
	# Depending where your frameworks are:
	# ${CMAKE_SOURCE_DIR}/Frameworks
	/usr/local/lib/libSDL2-2.0.0.dylib

	${FRAMEWORKS_PATH}/libSDL2-2.0.0.dylib
)
```
*CMakeLists.txt*
</br>
I also want to make sure our executable is searching for the library in the right place
```
# Depending where you decided to copy it
set(RPATH @executable_path/../Frameworks)
set(CMAKE_BUILD_RPATH ${RPATH})
```
### Check the rest of the file if needed

#### ! Command to delete quarantine files from an app:
```
xattr -rc /yourApp.app
```
