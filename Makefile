main: src/main.c src/ArquivoSaida.c src/Arquivo.c
	gcc -o main src/Arquivo.c src/ArquivoSaida.c src/main.c src/Cripto.c src/Frequencia.c src/Casamento.c -I include -Wall

run: main
	./main
