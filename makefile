run: project.cpp
	g++ -std=c++11 project.cpp -o align -Wall
test: run
	./align
clean:
	rm -fv align
