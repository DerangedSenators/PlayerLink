# The PlayerLink Repository

The PlayerLink repository contains the source code for both server and client base implementation of PlayerLink. PlayerLink is built using CMake, a cross-platform C/C++ build system.

## Repository Layout

The Repository is layed out as follows:

```
📦 PlayerLink
┃
┣ 📂 include
┃    ┣ *.cmake //These files will host cmake functions to import additional libraries such as boost
┃    ┣ 📂 Libraries
┃       ┣ 📂 dynlibs
┃       ┃   ┣ 📂 win //Windows DLLs
┃       ┃   ┣ 📂 linux //Linux .so files
┃       ┃   ┣ 📂 mac // dynlibs for MacOS
┃       ┣ 📂 static
┃           ┣ 📂 win //Windows Static libs
┃           ┣ 📂 linux //Linux Static libs
┃           ┣ 📂 mac // dynlibs Static libs
┣ 📂  src
 ┣ 📂client // PlayerLink Client system
 ┃ ┣ 📂net // Client Network Code
 ┣ 📂core // PlayerLink Core Library
 ┃ ┣ 📂crypto // Cryptography Functions
 ┃ ┣ 📂net // Networking code
 ┃ ┣ 📂utils // PlayerLink Utility Code
 ┃ ┃ ┣ 📂exceptions //PlayerLink Exceptions Library
 ┃ ┃ ┣ 📂logger // PlayerLink Logger
 ┣ 📂platform
 ┃ ┣ 📂ieee
 ┃ ┃ ┗ 📂posix // Posix Specific code
 ┃ ┣ 📂microsoft
 ┃ ┃ ┗ 📂win32 //Win32 specific code
 ┃ ┃ ┃ ┣ 📂overlays
 ┃ ┃ ┃ ┃ ┗ 📂core
 ┃ ┃ ┃ ┃ ┃ ┣ 📂net
 ┃ ┗ 📂unix // Unix specific code
 ┗ 📂server // PlayerLink Server
 ┃ ┣ 📂net // Network sources
 ┃ ┣ 📂room //GameRoom sources
 
  ```      
