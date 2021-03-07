cmake_minimum_required (VERSION 3.8)

project ("Snake")
link_directories(${CMAKE_SOURCE_DIR}/lib)
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)
find_package(OpenGL REQUIRED)
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw3)
target_link_libraries(${PROJECT_NAME} PUBLIC glew32s)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
FILE(COPY "${CMAKE_SOURCE_DIR}/res" DESTINATION "${CMAKE_BINARY_DIR}")
