valgrind:
	g++ -g ./src/*.cpp -lpthread -o ./bin/output && valgrind --leak-check=yes -s --main-stacksize=4000000 ./bin/output

debug:
	g++ -g ./src/*.cpp -lpthread -o ./bin/output

run:
	g++ ./src/*.cpp -lpthread -o ./bin/output && ./bin/output

build:
	g++ -O3 ./src/*.cpp -lpthread -o ./bin/output

execute:
	./bin/output

clean:
	rm ./bin/*.o ./bin/output
