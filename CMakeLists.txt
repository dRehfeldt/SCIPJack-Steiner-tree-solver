cmake_minimum_required(VERSION 3.0.0)

project(SCIPJACK VERSION 1.2.1)

# make 'Release' the default build type
#if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE Release)
#endif()

set(SOPLEX_DIR ${CMAKE_BINARY_DIR})
set(SCIP_DIR ${CMAKE_BINARY_DIR})

# path to e.g. findGMP module
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/scip/cmake/Modules)

add_subdirectory(soplex)
add_subdirectory(scip)

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${SCIPOptSuite_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${SCIPOptSuite_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${SCIPOptSuite_VERSION_PATCH}")
set(CPACK_PACKAGE_VENDOR "Zuse Institute Berlin")
set(CPACK_NSIS_MODIFY_PATH on)
set(CPACK_PACKAGE_EXECUTABLES scip;SCIP soplex;SoPlex)
set(CPACK_PACKAGE_CONTACT "SCIPJACK <rehfeldt@zib.de>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SCIP-Jack, SCIP and Soplex")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "http://scip.zib.de")
# autogenerate dependency information
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS on)
include(CPack)

find_package(SCIP REQUIRED)

include_directories(${SCIP_INCLUDE_DIRS})

add_executable(st-exact
    src/cmain.c
    src/branch_stp.c
    src/cons_stp.c
    src/dialog_stp.c
    src/event_bestsol.c
    src/grphbase.c
    src/grphload.c
    src/grphmcut.c
    src/grphpath.c
    src/grphsave.c
    src/heur_ascendprune.c
    src/heur_local.c
    src/heur_prune.c
    src/heur_rec.c
    src/heur_slackprune.c
    src/heur_tm.c
    src/misc_stp.c
    src/pricer_stp.c
    src/probdata_stp.c
    src/prop_stp.c
    src/reader_stp.c
    src/reader_gr.c
    src/reduce_alt.c
    src/reduce_bnd.c
    src/reduce.c
    src/reduce_simple.c
    src/validate.c
)

# link to math library if it is available
find_library(LIBM m)
if(NOT LIBM)
  set(LIBM "")
endif()

target_link_libraries(st-exact ${SCIP_LIBRARIES} ${LIBM})

set_property(TARGET st-exact PROPERTY C_STANDARD 99)


enable_testing()
