cmake_minimum_required(VERSION 3.0)

project (nedit CXX)

option(ENABLE_ASAN   "Enable address santiziers")
option(ENABLE_USAN   "Enable undefined santiziers")
option(ENABLE_MSAN   "Enable memory santiziers")
option(ENABLE_TSAN   "Enable thread santiziers")
option(ENABLE_LTO    "Enable Link Time Optimization")
option(PURIFY        "Fill Unused TextBuffer space")

set(VISUAL_CTRL_CHARS ON CACHE BOOL "Visualize ASCII Control Characters")

if(ENABLE_ASAN)
	set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS}        -fsanitize=address") # -fsanitize-address-use-after-scope
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()

if(ENABLE_ASAN)
	set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS}        -fsanitize=undefined")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")
endif()

if(ENABLE_TSAN)
	set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS}        -fsanitize=thread")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")
endif()

if(ENABLE_MSAN)
	set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS}        -fsanitize=memory")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=memory")
endif()

if(ENABLE_LTO)
	set(CMAKE_CXX_FLAGS        "${CMAKE_CXX_FLAGS}        -flto")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto")
	set(CMAKE_AR               "gcc-ar")
	set(CMAKE_RANLIB           "gcc-ranlib")
endif()

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

if(PURIFY)
	add_definitions(-DPURIFY)
endif()

if(VISUAL_CTRL_CHARS)
	add_definitions(-DVISUAL_CTRL_CHARS)
endif()

add_definitions(-DQT_NO_CAST_FROM_ASCII)
add_definitions(-DQT_NO_CAST_TO_ASCII)

if(MSVC)

else()
	add_compile_options(-W -Wall -pedantic -Wunused -Wno-unused-macros -Wno-shadow -Wno-switch-enum -Wno-unknown-pragmas)
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		add_compile_options(-Wshorten-64-to-32 -Wconditional-uninitialized -Wsign-conversion) # -Weverything -Wno-documentation -Wno-missing-prototypes -Wno-date-time -Wno-padded -Wno-documentation-unknown-command -Wno-exit-time-destructors -Wno-c++98-compat-pedantic -Wno-c++98-compat -Wno-global-constructors -Wno-weak-vtables -Wno-implicit-fallthrough)
	else()
#		add_compile_options(-Wuseless-cast)
	endif()
endif()

# 
# -Wno-gnu-zero-variadic-macro-arguments
# 

add_subdirectory (Util)
add_subdirectory (source)
add_subdirectory (client)
add_subdirectory (Regex)
add_subdirectory (Settings)
add_subdirectory (Interpreter)
add_subdirectory (GSL EXCLUDE_FROM_ALL)

if (UNIX)
    find_package(X11)
    if(${X11_FOUND})
        add_subdirectory (import)
    endif()
endif()
