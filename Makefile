execute:
	g++ -O3 ./src/*.cpp -lpthread -o ./bin/output && ./bin/output

clean:
	rm ./bin/*.o ./bin/output
