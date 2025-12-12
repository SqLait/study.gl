if(NOT EXISTS "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
    file(DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/CPM.cmake
        ${CMAKE_BINARY_DIR}/cmake/CPM.cmake
        TLS_VERIFY ON
    )
endif()
include(${CMAKE_BINARY_DIR}/cmake/CPM.cmake)

CPMAddPackage(
    NAME SDL3
    GITHUB_REPOSITORY libsdl-org/SDL
    GIT_TAG release-3.2.28
)

CPMAddPackage(
    NAME glm
	GITHUB_REPOSITORY g-truc/glm
	GIT_TAG 1.0.2
)
