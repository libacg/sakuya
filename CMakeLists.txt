cmake_minimum_required(VERSION 3.22)
project(sakuya)

set(CMAKE_CXX_STANDARD 20)

add_executable(sakuya main.cpp lib/NkEndian.h lib/Nkstdint.h lib/NkTypes.h lib/Maid3.h lib/Maid3d1.h Callback.cpp Callback.h)
add_library(sakuya2 SHARED SakuyaLibrary.cpp lib/NkEndian.h lib/Nkstdint.h lib/NkTypes.h lib/Maid3.h lib/Maid3d1.h Callback.cpp Callback.h)
