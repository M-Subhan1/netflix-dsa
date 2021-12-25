run:
	g++ ./src/*.cpp -lpthread -o ./bin/output && ./bin/output

build:
	g++ ./src/*.cpp -lpthread -o ./bin/output

execute:
	./bin/output

clean:
	rm ./bin/*.o ./bin/output
