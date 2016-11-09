cliente: mainc.o  cliente.o 
	gcc -o cliente mainc.o  cliente.o
mainc.o: mainc.c  cliente.h
	gcc -c mainc.c
cliente.o: cliente.c cliente.h
	gcc -c cliente.c

clean:
	rm mainc.o  cliente.o
