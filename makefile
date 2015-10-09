main: main.o triagem.o func.o ficheiros.o atender.o consulta.o
	gcc -o main main.o triagem.o func.o ficheiros.o atender.o consulta.o

main.o: main.c func.h
	gcc -c main.c 

triagem.o: triagem.c
	gcc -c triagem.c 

func.o: func.c 
	gcc -c func.c

ficheiros.o: ficheiros.c
	gcc -c ficheiros.c

atender.o: atender.c
	gcc -c atender.c

consulta.o: consulta.c
	gcc -c consulta.c
