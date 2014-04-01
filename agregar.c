#include "agregar.h"

GtkWidget *eNombre, *eIp, *ePuerto, *window;

void Agregar (GtkWidget *boton, GdkEventKey *event)// funcion para agregar amigos
{
    int i;
    FILE *fp;
    fp = fopen ( "amigos.txt", "a+" ); // crea y/o escribe en el archivo
    //validacion del nombre ingresado
    int largo = (int) g_utf8_strlen(gtk_entry_get_text(GTK_ENTRY(eNombre)), -1);
    if ( largo != 0)
    {
       gchar *str = NULL;
       str = g_strconcat(gtk_entry_get_text(GTK_ENTRY(eNombre)), NULL);
       fprintf(fp,"%s;",str);
    }
    int ip[10] = {0};
    largo = (int) g_utf8_strlen(gtk_entry_get_text(GTK_ENTRY(eIp)), -1); // validacion de la ip ingresada
    if ( largo != 0)
    {
       gchar *str = NULL;
       str = g_strconcat(gtk_entry_get_text(GTK_ENTRY(eIp)), NULL);
       for(i=0;i<largo;i++)
       {
           if(i==(largo-1) && ((str[i])=='.'))
           {
             g_print("Ip incorrecto\n");
             return;
           }
           if(isdigit(str[i])||(str[i])=='.')
           {
               ip[i] = str[i]-48;
           }
           else
           {
             g_print("Ip incorrecto\n");
             return;
           }       
       }
       fprintf(fp,"%s;",str);
    }
    int puerto[10] = {0};
    largo = (int) g_utf8_strlen(gtk_entry_get_text(GTK_ENTRY(ePuerto)), -1); // validacion del puerto ingresado
    if ( largo != 0)
    {
       gchar *str = NULL;
       str = g_strconcat(gtk_entry_get_text(GTK_ENTRY(ePuerto)), NULL);
       for(i=0;i<largo;i++)
       {
           if(isdigit(str[i]))
           {
               puerto[i] = str[i]-48;               
           }
           else
           {
             g_print("Puerto incorrecto\n");
             return;
           }       
       }
       fprintf(fp,"%s;\n",str);
    }
    fclose(fp); // se cierra el archivo
    gtk_widget_destroy(window);
    
}


int Interfaz(int argc, char** argv) {

    // Declaracion de los punteros 
    GtkWidget *fixed;
    GtkWidget *bAgregar;
    GtkWidget *lTitulo;
    GtkWidget *lNombre;
    GtkWidget *lIp;
    GtkWidget *lPuerto;
    
    gtk_init(&argc, &argv);
    
    //Asignar los atributos a los punteros
    
    //Frame
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkFixed");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    //Layout
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    
    //Botones
    bAgregar = gtk_button_new_with_label("Agregar");
    gtk_fixed_put(GTK_FIXED(fixed), bAgregar, 135, 150);
    gtk_widget_set_size_request(bAgregar, 80, 35);
    
    //Labels
    lTitulo = gtk_label_new("Agregar Amigo");
    gtk_fixed_put(GTK_FIXED(fixed), lTitulo, 100, 0);
    gtk_widget_set_size_request(lTitulo, 150, 35);
    
    lNombre = gtk_label_new("Usuario :");
    gtk_fixed_put(GTK_FIXED(fixed), lNombre, 10, 35);
    gtk_widget_set_size_request(lNombre, 55, 35);
    
    lIp = gtk_label_new("IP :");
    gtk_fixed_put(GTK_FIXED(fixed), lIp, 0, 70);
    gtk_widget_set_size_request(lIp, 40, 35);
    
    lPuerto = gtk_label_new("Puerto :");
    gtk_fixed_put(GTK_FIXED(fixed), lPuerto, 0, 105);
    gtk_widget_set_size_request(lPuerto, 70, 35);
    
    //Entry
    
    eNombre = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), eNombre, 100, 40);
    gtk_widget_set_size_request(eNombre, 80, 20);
    
    eIp =gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), eIp, 100, 75);
    gtk_widget_set_size_request(eIp, 80, 20);
    
    ePuerto =gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), ePuerto, 100, 110);
    gtk_widget_set_size_request(ePuerto, 80, 20);
    
    //Declaracion de señales
    
    g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(bAgregar), "clicked", G_CALLBACK(Agregar), NULL);
 
    gtk_widget_show_all(window);
    
    gtk_main();
    return 0;
}
