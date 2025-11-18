main: src/main.c src/ArquivoSaida.c src/Arquivo.c
	gcc -o main src/Arquivo.c src/ArquivoSaida.c src/main.c  -I include

run: main
	./main
