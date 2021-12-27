valgrind:
	valgrind --leak-check=yes ./bin/output

debug:
	g++ -g ./src/*.cpp -lpthread -o ./bin/output

run:
	g++ -O3 ./src/*.cpp -lpthread -o ./bin/output && ./bin/output

build:
	g++ -O3 ./src/*.cpp -lpthread -o ./bin/output

execute:
	./bin/output

clean:
	rm ./bin/*.o ./bin/output
