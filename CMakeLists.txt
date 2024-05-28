cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

cmake_policy(SET CMP0091 NEW)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "In-tree builds are not supported. Run CMake from a separate directory: cmake -B build")
endif()

project(QtApp VERSION 0.1.0 LANGUAGES CXX)

if(MSVC)
	set(Qt6_DIR "D:/Lib/qt6_670_static_64")
	set(Qt6_CMAKE_DIR "D:/Lib/Qt6_static/lib/cmake/Qt6")
	
	list(APPEND CMAKE_PREFIX_PATH ${Qt6_CMAKE_DIR})
endif()

set(QT_VERSION 6)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS
	Core 
	Widgets
	Gui)

set(HEADERS
    src/mainwindow.h)

set(SOURCES 
	src/main.cpp
	src/mainwindow.cpp)

set(UIS
	src/resources/ui/mainwindow.ui)

set(RESOURCES 
	src/resources/app.rc
	src/resources/resource.qrc)

qt_standard_project_setup()

# add_subdirectory(3rdparty/SomeLibrary)
add_subdirectory(mylibrary)

add_executable(QtApp ${SOURCES} ${HEADERS} ${UIS} ${RESOURCES})

target_link_libraries(QtApp PRIVATE 
	mylibrary
	Qt6::Core
	Qt6::Widgets
	Qt6::Gui)

if(MSVC)
	set_target_properties(QtApp PROPERTIES
	    WIN32_EXECUTABLE ON
	    MACOSX_BUNDLE ON)
endif()

if(NOT MSVC)
	if (CMAKE_BUILD_TYPE STREQUAL "Release")
		set(CMAKE_POSITION_INDEPENDENT_CODE ON)

		set_target_properties(QtApp PROPERTIES
	    WIN32_EXECUTABLE ON
	    MACOSX_BUNDLE ON)
	endif()
endif()


if(NOT MSVC AND CMAKE_BUILD_TYPE STREQUAL "Release")
	set(DEPLOY_PATH "${CMAKE_CURRENT_BINARY_DIR}/deploy")
	file(MAKE_DIRECTORY ${DEPLOY_PATH})

	add_custom_command(
	    TARGET QtApp POST_BUILD
	    COMMAND ${CMAKE_COMMAND} -E make_directory "${DEPLOY_PATH}"
	    COMMAND windeployqt6 --no-translations --no-opengl-sw --no-translations --no-compiler-runtime --dir ${DEPLOY_PATH} $<TARGET_FILE:QtApp>
	    COMMENT "Deploying Qt application...")

	add_custom_command(
	    TARGET QtApp POST_BUILD
	    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:QtApp> ${DEPLOY_PATH}
	    COMMENT "Copying executable to deployment directory")

	install(
	    DIRECTORY ${DEPLOY_PATH}/
	    DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()

if(MSVC)
	install(
		TARGETS QtApp
		DESTINATION bin
		COMPONENT QtApp)
endif()