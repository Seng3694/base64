cmake_minimum_required(VERSION 2.4)

project(base64)

set(SOURCES
	src/base64.c 
)

set(HEADERS
	include/base64.h
)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC include)

if(BUILD_BASE64_TEST)
	add_executable(${PROJECT_NAME}_test src/test.c)
	target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
endif()
