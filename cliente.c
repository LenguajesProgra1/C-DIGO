#include "agregar.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int cliente (int argc, char *argv[]) // socket cliente
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    char buffer[256];
    if (argc < 3)
    {
        g_print("El puerto host %s está en uso\n", argv[0]); 
        exit(0);
    }
   
    portno = atoi(argv[2]); // asigna el puerto
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    
    if (sockfd < 0)
        g_print("ERROR de apertura de socket"); //error
    
    server = gethostbyname(argv[1]);
    
    if (server == NULL)
    {
        g_print("ERROR, no hay host \n"); 
        exit(0);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    
    bcopy((char *)server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);
    
    serv_addr.sin_port = htons(portno);
    
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        g_print("ERROR de conexión"); //error
    
    bzero(buffer,256);
    sprintf(buffer,"%s",argv[3]);// guarda el mensaje por enviar en la variable buffer
    
    n = write(sockfd,buffer,strlen(buffer)); // envia el mensaje 
    
    if (n < 0)
        g_print("ERROR al escribir en socket"); //error
    
    bzero(buffer,256);
    n = read(sockfd,buffer,255); // recibe respuesta del servidor
    
    if (n < 0)
        g_print("ERROR al leer del socket"); //error
    
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}
