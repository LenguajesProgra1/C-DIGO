#include "agregar.h"
// creacion de variables globales
char* basedatos;
char* iplocal;
char* contacto[8];
void dostuff(int);

void errorServ(const char *msg)
{
    perror(msg);
    exit(1);
}

int servidor(int argc, int portno) // funcion para el socket servidor
{
    int sockfd, newsockfd, pid;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    if (argc < 2)
    {
        g_print("ERROR, no hay ningún puerto\n"); // validar que recibio la cantidad de datos necesarios
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0)
        g_print("ERROR de apertura de socket"); //validar la apertura del socket
    
    bzero((char *) &serv_addr, sizeof(serv_addr));  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        g_print("ERROR en la conexión"); //validar la conexion
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    while (1) // while donde ira el fork para dejar al servidor escuchando
        {
        newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen); 
        iplocal = inet_ntoa(cli_addr.sin_addr); // guarda en una variable global el ip de la persona que manda el mensaje
        if (newsockfd < 0)
            g_print("ERROR en aceptar"); //errorServ
        pid = fork(); // creacion del fork
        if (pid < 0)
            g_print("ERROR en fork"); //errorServ
        if (pid == 0)
        {
            close(sockfd); 
            dostuff(newsockfd); // manipulacion de recibimiento de datos
            exit(0);
        }
        else
            close(newsockfd);
        }
    close(sockfd);
    return 0;
}
//Gestiona todas las comunicaciones una vez que la conexión ha sido establecida
void dostuff (int sock)
{
    int n;
    char buffer[256];
    bzero(buffer,256);
    n = read(sock,buffer,255);
    
    if (n < 0)
        g_print("ERROR al leer del socket"); //valida la lectura del socket
    
    n = write(sock," ",2); // envia respuesta al servidor
    recibido(0,0,buffer,iplocal);// llama al frame para mostrar el mensaje que entro
    if (n < 0)
        g_print("ERROR al escribir en el socket"); // validar la escritura del socket
    
}

int recibido(int argc, char** argv, char* mensaje, char* ipcliente)
{
    GtkWidget* fixed;
    GtkWidget* window;
    GtkWidget* label;
    
    gtk_init(&argc, &argv);
    
    //Frame
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mensaje");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 100);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    //Layout
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    
    //Label
    const gchar* txt_lbl = g_strconcat(iplocal,mensaje,NULL);
    label = gtk_label_new(txt_lbl);
    gtk_fixed_put(GTK_FIXED(fixed), label, 0, 0);
    gtk_widget_set_size_request(label, 300, 100);
    
    g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
 
    gtk_widget_show_all(window);
    
    gtk_main();
    return 0;
}
