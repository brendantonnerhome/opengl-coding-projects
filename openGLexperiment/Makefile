

CXX = g++

LIBS= \
  -lGL \
  -lGLU \
  -lglut \
  -lpthread

SRC_DIR = ./source
INC_DIR = ./include
THIS_DIR = ./

TARGET := GLBIN

all: ${TARGET}

CXXFLAGS := -I $(INC_DIR)

SRCS_CPP := \
  $(SRC_DIR)/socketHelper.cpp \
  $(SRC_DIR)/definitions.cpp \
  $(SRC_DIR)/imageLoader.cpp \
  $(SRC_DIR)/main.cpp \
  $(SRC_DIR)/objParser.cpp
  
SRCS := 
  
OBJS_CPP := ${SRCS_CPP:.cpp=.o}
OBJS	:= ${SRCS:.c=.o}

#OBJECTS=$(SOURCES:%.cpp=%.o)

#OBJS_CPP := ${SOURCES:.cpp=.o}

${TARGET}: ${OBJS} ${OBJS_CPP}
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS}

${OBJS}: %.o: %.c %.dep
	${CXX} -I $(INC_DIR) ${CFLAGS} -o $@ -c $<

${OBJS_CPP}: %.o: %.cpp
	${CXX} ${CXXFLAGS} -o $@ -c $<

${DEPS}: %.dep: %.c Makefile
	${CXX} ${CFLAGS} -MM $< > $@

clean::
	-rm -f ${OBJS} ${OBJS_CPP} ${TARGET} ${XDEPS}
	
tags::
	@rm -f $@
	ctags -R
