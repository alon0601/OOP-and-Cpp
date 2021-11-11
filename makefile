makall: studio

studio: bin/main.o bin/Studio.o
	@echo 'Building target: studio'
	g++ -o bin/studio bin/main.o bin/Studio.o
	@echo 'Finished building target: studio'
	@echo ' '

bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

bin/Studio.o: src/Studio.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Studio.o src/Studio.cpp

clean:
	rm -f bin/*
