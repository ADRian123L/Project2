run: project.cpp
	g++ -std=c++11 project.cpp -o align
test: ./align
	./align
clean:
	rm -fv align
