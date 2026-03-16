
FIND_PACKAGE(VTK QUIET)
if(VTK_FOUND)
    INCLUDE(${VTK_USE_FILE})
    ADD_DEFINITIONS(-DVTKINCLUDED)
    message(STATUS "VTK found - VTK export enabled")
else()
    message(STATUS "VTK not found - VTK export disabled")
endif()

INCLUDE_DIRECTORIES(lib)
INCLUDE_DIRECTORIES(nlohmann)
INCLUDE_DIRECTORIES(lib/liblzma)
INCLUDE_DIRECTORIES(mesh/rply)
INCLUDE_DIRECTORIES(mesh/tinyxml)

AUX_SOURCE_DIRECTORY(lib ctm)
AUX_SOURCE_DIRECTORY(lib/liblzma lzma)
AUX_SOURCE_DIRECTORY(mesh/rply rply)
AUX_SOURCE_DIRECTORY(mesh/tinyxml tinyxml)

set(LIBRARIES evpp_static ${DEPENDENT_LIBRARIES})

add_executable(mfc
        mesh/systimer.cpp
        mesh/options.cpp
        mesh/mesh.cpp
        mesh/meshio.cpp
        mesh/format/ctm.cpp
        mesh/format/ply.cpp
        mesh/format/stl.cpp
        mesh/format/3ds.cpp
        mesh/format/dae.cpp
        mesh/format/lwo.cpp
        mesh/format/obj.cpp
        mesh/format/off.cpp
        mesh/format/wrl.cpp
        mesh/common.cpp
        network/NetworkProvider.cpp
        network/HttpServer.cpp
        ${ctm} ${lzma} ${rply} ${tinyxml}
        mfc.cpp
        controllers/MeshController.cpp
        time/Timer.cpp
        mesh/MeshProcessor.cpp
        mesh/MeshConverter.cpp
        mesh/OptionsProcessor.cpp
        mesh/OptionParser.cpp
        mesh/format/Format.cpp)

if(VTK_FOUND)
    TARGET_LINK_LIBRARIES(mfc ${VTK_LIBRARIES} ${LIBRARIES})
else()
    TARGET_LINK_LIBRARIES(mfc ${LIBRARIES})
endif()
