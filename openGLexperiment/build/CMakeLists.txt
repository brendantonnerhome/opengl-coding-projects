cmake_minimum_required(VERSION 2.8.4)
#cmake_minimum_required(VERSION 2.8)

project (openGLTest C CXX)

#-Werror
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -lGL -lGLU -lglut -lpthread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lGL -lGLU -lglut -lpthread")
add_executable(
	openGLTest 
	../source/main.cpp 
	../source/definitions.cpp 
	../source/imageLoader.cpp 
	../source/objParser.cpp 
	../source/socketHelper.cpp
)
###################################
# opengl magic
###################################
find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(openGLTest ${OPENGL_LIBRARIES} ) 

###################################
# glut magic
###################################
#find_package(GLUT REQUIRED)
#link_directories(${GLUT_LIBRARY_DIRS})
#target_link_libraries( openGLTest ${GLUT_LIBRARY})
target_link_libraries( openGLTest ${CMAKE_THREAD_LIBS_INIT})
###################################
# pthread magic
###################################
find_package( Threads REQUIRED)
target_link_libraries( openGLTest ${CMAKE_THREAD_LIBS_INIT})
#${GLUT_LIBRARY}
#add_definitions(CMAKE_EXE_LINKER_FLAGS)


