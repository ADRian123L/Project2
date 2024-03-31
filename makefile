run: project.cpp
	g++ -std=c++11 project.cpp -o align -Wall
	./align
clean:
	rm -fv align
