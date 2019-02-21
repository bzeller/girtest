cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(FindPkgConfig)

pkg_check_modules ( GLIBMM2 glibmm-2.58 REQUIRED )

INCLUDE_DIRECTORIES ( ${GLIBMM2_INCLUDE_DIRS} )
LINK_DIRECTORIES ( ${GLIBMM2_LIBRARY_DIRS} )

project(glibmm)
add_library( ${PROJECT_NAME} SHARED "main.cpp" "testclass.cpp" "testclass.h" "zypp/zypptestclass.cpp" "zypp/zypptestclass.h" "zypp/zypp.h" "zypp/zypp.cpp" )


target_link_libraries( ${PROJECT_NAME} ${GLIBMM2_LIBRARIES} )

include (GIR)

if (GIR_FOUND)
    list (APPEND MODULES "Zypp" )
    foreach (MOD ${MODULES})
        string(TOLOWER ${MOD} LOWER_MOD)
        if (EXISTS "${CMAKE_SOURCE_DIR}/${LOWER_MOD}")
            gir (${LOWER_MOD} ${MOD})
        endif ()
    endforeach ()
else ()
    message (FATAL_ERROR "g-ir-scanner not found")
endif ()
