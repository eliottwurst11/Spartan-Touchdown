cmake_minimum_required(VERSION 3.19)

project(Spartan_Touchdown)
set(CMAKE_CXX_STANDARD 17)
set(APPLICATION_LIBRARY GameLib)

# Request the required wxWidgets libs
# Turn off wxWidgets own precompiled header system
set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

# Include the wxWidgets use file; initializes settings
include(${wxWidgets_USE_FILE})

# ===================================================================
# HAD TO ADD THIS HERE DUE TO NOT BUILDING ON MY MACHINE. DELETE THIS
# IF THE APP DOES NOT BUILD ANYMORE AFTER THIS CHANGE.
# ===================================================================
find_library(wxWidgets_WEBP_LIBRARY
        NAMES wxwebpd
        HINTS ${wxWidgets_LIB_DIR}
)

if(wxWidgets_WEBP_LIBRARY)
    message(STATUS "Found wxWidgets WebP library: ${wxWidgets_WEBP_LIBRARY}")
    list(APPEND wxWidgets_LIBRARIES ${wxWidgets_WEBP_LIBRARY})
else()
    message(WARNING "Could not find the wxWidgets WebP library (wxwebpd).")
endif()
# ===================================================================

add_subdirectory(${APPLICATION_LIBRARY})

#add_subdirectory(Tests)

include_directories(${APPLICATION_LIBRARY})

set(SOURCE_FILES
        main.cpp
        GameApp.cpp
        GameApp.h
        pch.h
)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCE_FILES})

# Link wxWidgets libraries
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${APPLICATION_LIBRARY})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/levels/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/levels/)
