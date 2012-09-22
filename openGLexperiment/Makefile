all: app

LIBS= \
  -lGL \
  -lGLU \
  -lglut \
  -lpthread

main.o: main.cpp
	g++ -c main.cpp

app: main.o
	g++ main.o $(LIBS) -o output.out

run: app
	./output.out

clean:
	rm -rf *.o output.out
