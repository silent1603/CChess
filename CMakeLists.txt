cmake_minimum_required(VERSION 3.25)
project(TinySB)

# The configurations we support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/Vendors/glm/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()


list(APPEND VENDORS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendors/glad/src/glad.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendors/imgui/imgui.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendors/imgui/imgui_tables.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendors/imgui/imgui_widgets.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendors/imgui/imgui_draw.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendors/imgui/backends/imgui_impl_opengl3.cpp 
)
if( WIN32)
    list(APPEND VENDORS_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Vendors/glad/src/glad_wgl.c 
        ${CMAKE_CURRENT_SOURCE_DIR}/Vendors/imgui/backends/imgui_impl_win32.cpp
    )

else()
    list(APPEND VENDORS_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Vendors/glad/src/glad_glx.c 
    )
    set(GLAD_LIBRARIES dl)

endif()


file(GLOB_RECURSE PROJECT_HEADERS Sources/*.hpp Sources/*.h)
file(GLOB_RECURSE PROJECT_SOURCES Sources/*.cpp)
file(GLOB_RECURSE PROJECT_SHADERS Shaders/*.comp
                          Shaders/*.frag
                          Shaders/*.geom
                          Shaders/*.vert 
                          )

file(GLOB_RECURSE PROJECT_RES Res/*.*)

file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Resources" FILES ${PROJECT_RES})

add_definitions(-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

if(WIN32)
add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCES} ${PROJECT_HEADERS}
    ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
    ${VENDORS_SOURCES} ${PROJECT_RES})
else()
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES} ${PROJECT_RES})
endif()

target_include_directories(TinySB PUBLIC "${PROJECT_SOURCE_DIR}/Sources/" 
                               PUBLIC "${PROJECT_SOURCE_DIR}/Vendors/glad/include/" 
                               PUBLIC "${PROJECT_SOURCE_DIR}/Vendors/glm/" 
                               PUBLIC "${PROJECT_SOURCE_DIR}/Vendors/stb/" 
                               PUBLIC "${PROJECT_SOURCE_DIR}/Vendors/imgui/" 
                               PUBLIC "${PROJECT_SOURCE_DIR}/Vendors/imgui/backends/")

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    target_link_libraries(${PROJECT_NAME} opengl32.lib)
endif()
    


add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_SHADERS} )

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Res $<TARGET_FILE_DIR:${PROJECT_NAME}>
        DEPENDS ${PROJECT_RES} )
