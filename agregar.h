#ifndef AGREGAR_H
#define	AGREGAR_H
// importacion de librerias en el archivo cabecera
#include <gtk/gtk.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>


    // declaracion de funciones que seran parte del programa
    int Interfaz(int argc, char** argv);
    void Agregar (GtkWidget *boton, GdkEventKey *event);
    int chat(int argc,char* argv[],char* usr,char* str);
    GtkWidget* chatFrame();
    void enviado(GtkWidget *boton, GdkEventKey *event,GtkWidget *entry);
    void error(const char *msg);
    int cliente (int argc, char *argv[]);
    void errorServ(const char *msg);
    int servidor(int argc, int puerto);
    void dostuff (int sock);
    int recibido(int argc, char** argv, char* mensaje, char* ipcliente);



#endif	/* AGREGAR_H */
