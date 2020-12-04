# PlayerLink Overlay System - Beta
As PlayerLink is developed as a native cross-platform system, accomodations have had to be made for platform-specific code. As a result we have developed the overlay system.

## How it works
An overlay is a static library created to be linked onto a PlayerLink library if conditions are met during runtime

## Example of Overlay
One of the overlays we have created is the `winsockinit` overlay which holds code that needs to be included on top of `PLAYERLINK_CORE_NET` library for Windows devices (`winsockinit.h` holds code required by Windows to initialise the `Winsock2.dll` library).

The overlay was created as follows:

1. Create a mirroring path within `src/platfrom/microsoft/win32/overlays` mirroring the `src` directory, In this case we had to add the following subfolders `core/net`. 

2. In this folder, add your source code. In the case of this example it was `winsockinit.h` and `winsockinit.c`.

3. Create a `CMakeLists.txt` in the folder and add the following:
```
add_library(
        PLAYERLINK_CORE_NET_WIN32
        winsockinit.h
        winsockinit.c
)
```
This creates the static library which will be linked into `PLAYERLINK_CORE_NET`

4. Now you need to add some code in `core/net/CMakeLists.txt` to ensure that this library is compiled:
```
IF(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/src/platform/microsoft/win32/overlays/core/net/)
    target_link_libraries(PLAYERLINK_CORE_NET PRIVATE PLAYERLINK_CORE_NET_WIN32)
ENDIF()
```
This chunk of code will link the overlay library if the compiler detects that it is compiling on a `Win32` system.

5. Now in your code, you will have to use macros to include the `winsockinit.h` file. For example:
```
#ifdef WIN32
#include 'winsockinit.h'
#endif
``` 
This will ensure that the defined functions are included in the class that is using them.

### Nested Method Calls
We are currently working on a solution to have efficient nested method calls using the overlay system but at the moment you may use pre-processor directives as a workaround
### Exclusive Classes and Methods
At the moment we havent yet created a solution to allow for exclusive methods to existing PlayerLink classes but you can include classes using pre-processor directives