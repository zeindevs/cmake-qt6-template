cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

cmake_policy(SET CMP0091 NEW)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_PREFIX "install")
set(CMAKE_PREFIX_PATH "D:/Qt/6.7.1/msvc2019_64_static")

project(QtApp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_VERSION 0.1.0)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

find_package(Qt6 REQUIRED COMPONENTS
	Core 
	Widgets
	Gui
)

set(HEADERS
  src/mainwindow.h
)

set(SOURCES 
	src/main.cpp
	src/mainwindow.cpp
)

set(UIS
	src/resources/ui/mainwindow.ui
)

set(RESOURCES 
	src/resources/app.rc
	src/resources/resource.qrc
)

# add_subdirectory(3rdparty/SomeLibrary)
add_subdirectory(mylibrary)

qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION
	${SOURCES}
 	${HEADERS}
	${UIS} 
	${RESOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
	Qt6::Core
	Qt6::Widgets
	Qt6::Gui
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
	mylibrary
)

if(MSVC)
	target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
	${BUNDLE_ID_OPTION}
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	set(INSTALL_PATH "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_PREFIX}")
	file(MAKE_DIRECTORY ${INSTALL_PATH})

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	    COMMAND ${CMAKE_COMMAND} -E make_directory "${INSTALL_PATH}"
	    COMMAND windeployqt6 --no-translations --no-opengl-sw --no-translations --no-compiler-runtime --dir ${INSTALL_PATH} $<TARGET_FILE:${PROJECT_NAME}>
	    COMMENT "Deploying Qt application..."
 	)

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${INSTALL_PATH}
	    COMMENT "Copying executable to deployment directory"
 	)
endif()

install(TARGETS ${PROJECT_NAME}
	DESTINATION bin
	COMPONENT ${PROJECT_NAME}
)

qt_finalize_executable(${PROJECT_NAME})