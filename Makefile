CFLAGS= -g -Wall -Wextra

output: ./bin/main.o
	g++ ./bin/main.o -o ./bin/output -lpthread

./bin/main.o: ./bin/utils.o ./src/main.cpp
	g++ -c ./src/main.cpp -o ./bin/main.o -lpthread

./bin/utils.o: ./src/utils.cpp
	g++ -c ./src/utils.cpp -o ./bin/utils.o -lpthread

execute: output
	./bin/output

debug: output
	g++ -g ./bin/output

clean:
	rm ./bin/*.o ./bin/output
