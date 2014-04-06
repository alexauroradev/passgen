all:
	g++ -g main.cpp sha256.cpp passgen.cpp -o passgen
clean:
	rm -rf passgen
