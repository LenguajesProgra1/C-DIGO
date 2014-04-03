main: agregar.c agregar.h chat.c cliente.c main.c servidor.c

	gcc -w -o exe agregar.h agregar.c chat.c cliente.c main.c servidor.c `pkg-config --libs --cflags gtk+-3.0`
