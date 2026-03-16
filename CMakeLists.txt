cmake_minimum_required(VERSION 2.8)

project(mfc C CXX)

if (UNIX)
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release")
    endif ()

    set(CXX_FLAGS
            -g
            -fPIC
            -Wall
            -Wno-unused-parameter
            -Wno-unused-function
            -Wunused-variable
            -Wunused-value
            -Wshadow
            -Wcast-qual
            -Wcast-align
            -Wwrite-strings
            -Wsign-compare
            -Winvalid-pch
            -fms-extensions
            -Wfloat-equal
            -Wextra
            -std=c++14
            )
    set(CMAKE_CXX14_EXTENSION_COMPILE_OPTION -std=c++14)
    set(CMAKE_CXX_STANDARD 14)

    include_directories(${PROJECT_SOURCE_DIR}
            ${PROJECT_SOURCE_DIR}/3rdparty)
else (UNIX)
    set(CXX_FLAGS -DWIN32 -D_WIN32 -EHsc)
    set(VcpkgRoot ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET})
    include_directories(${VcpkgRoot}/include
            ${PROJECT_SOURCE_DIR}
            ${PROJECT_SOURCE_DIR}/3rdparty/wininclude)

    # On windows, Debug mode
    link_directories(${VcpkgRoot}/debug/lib ${VcpkgRoot}/debug/lib/manual-link)

    # On Windows, Release mode
    # link_directories(${VcpkgRoot}/lib ${VcpkgRoot}/lib/manual-link)
endif (UNIX)

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

if (UNIX)
    SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb -D_DEBUG -DGOOGLE_STRIP_LOG=0")
    SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -g -ggdb -DNDEBUG -DGOOGLE_STRIP_LOG=1")
    SET(DEPENDENT_LIBRARIES event glog pthread)
else (UNIX)
    SET(DEPENDENT_LIBRARIES event glog)
endif (UNIX)

# Set to true if https support is needed.
# Note that this needs openssl
# SET(HTTPS True)
if (HTTPS)
    list(APPEND DEPENDENT_LIBRARIES ssl crypto event_openssl)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEVPP_HTTP_CLIENT_SUPPORTS_SSL")
endif (HTTPS)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_MACOSX_RPATH 0)

add_subdirectory(evpp)
add_subdirectory(mfc)
