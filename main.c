#include "agregar.h"
// creacion de variables globales
GtkWidget* help;
char bd[1000];
char nombres[100];
enum
{
  COLUMN = 0,
  NUM_COLS
} ;

void cargarContactos() // carga lista de los contactos agregados
{
    int i,b,c;b=0;c=0;
    char str[100];
    FILE* file;
    file = fopen("amigos.txt" , "a+"); // abre y/o crea el archivo amigos.txt
    while (fscanf(file, "%s", str)!=EOF)
    {
        int largo = strlen(str);
        for(i=0;i<largo;i++)
        {
            if(str[i]!=';')
            {
                bd[b] = str[i];
                nombres[c] = str[i];
                b++;c++;                     
            }
            else
            {
                bd[b] = ';';
                i++;b++;
                for(;i<largo;i++)
                {
                    bd[b]= str[i];
                    b++;
                }                  
            }
        }        
        nombres[c]=',';c++;
    }
    fclose(file); // cierra el archivo 
}

void  abreChat(GtkWidget *widget, gpointer statusbar) //despliegue de amigos agregados
{
  GtkTreeIter iter;
  GtkTreeModel *model;
  GtkWidget *frame;
  char *value;

  if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter)) 
  {
    gtk_tree_model_get(model, &iter, COLUMN, &value,-1);
    if(strcmp(value,"Amigos")!=0){
        frame = chat(0,0,value,bd);}
    g_free(value);
  }
}

//GENERA LA ESTRUCTURA DEL ARBOL YA CON LOS CONTACTOS
static GtkTreeModel *crearDespliegue (void)
{
  int i,b,c;
  GtkTreeStore *treestore;
  GtkTreeIter toplevel, child;

  treestore = gtk_tree_store_new(NUM_COLS,G_TYPE_STRING);
  gtk_tree_store_append(treestore, &toplevel, NULL);
  gtk_tree_store_set(treestore, &toplevel, COLUMN, "Amigos",-1);
  b=0;i=0;c=0;  
  int largo = strlen(nombres);
  while(i<largo){
      char temp[20];
      for(;nombres[i]!=',';i++)
      {
          temp[c] = nombres[i];
          c++;
      }
      gtk_tree_store_append(treestore, &child, &toplevel);
      gtk_tree_store_set(treestore, &child,COLUMN, temp,-1);   
      i++;c=0; memset(temp, 0, sizeof(temp));
  }
  
  return GTK_TREE_MODEL(treestore);
}


//HACE VISIBLE LA ESTRUCTURA DEL ARBOL
static GtkWidget * mostrarDespliegue (void)
{
  GtkTreeViewColumn *col;
  GtkCellRenderer *renderer;
  GtkWidget *view;
  GtkTreeModel *model;

  view = gtk_tree_view_new();

  col = gtk_tree_view_column_new();
  gtk_tree_view_column_set_title(col, "Bienvenido!");
  gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_column_pack_start(col, renderer, TRUE);
  gtk_tree_view_column_add_attribute(col, renderer, "text", COLUMN);

  model = crearDespliegue();
  gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
  g_object_unref(model); //Como el modelo ya esta en el arbol, borramos el modelo

  //retornamos el puntero donde esta el arbol
  return view;
}

void PopUp (GtkWidget *boton, GdkEventKey *event,GtkWidget *entry)// abre el frame Añadir amigos
{
    entry = Interfaz(0,0);
    gtk_widget_destroy(help);
    entry = main(0,0);    
}

int main (int argc, char **argv)
{
    int pid,bandera; bandera=0;
    pid = fork();
    while(1)
    {
        if (pid < 0)
            g_print("ERROR en fork"); //errorServ
        if (pid == 0)
        {
            if (bandera==0)
            {
                bandera=1;
                servidor(3,15557);
            }
        }
        else
        {
            cargarContactos();// llama a la funcion cargar contactos
// se crean los punteros para crear la interfaz principal
            GtkWidget *window;
            GtkWidget *view1;
            GtkTreeSelection *selection;
            GtkWidget *vbox;
            GtkWidget *bAgregar;

            gtk_init(&argc, &argv); // manejo de interfaz

            window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
            gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
            gtk_window_set_title(GTK_WINDOW(window), "Chat@");
            gtk_widget_set_size_request (window, 200, 300);

            vbox = gtk_vbox_new(FALSE, 2);
            gtk_container_add(GTK_CONTAINER(window), vbox);

            view1 = mostrarDespliegue();
            selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view1));
            gtk_box_pack_start(GTK_BOX(vbox), view1, TRUE, TRUE, 1);

            bAgregar = gtk_button_new_with_label("Agregar amigo");
            gtk_box_pack_start(GTK_BOX(vbox), bAgregar, FALSE, FALSE, 1);

            g_signal_connect(selection, "changed", G_CALLBACK(abreChat), NULL);

            g_signal_connect(G_OBJECT(bAgregar), "clicked", G_CALLBACK(PopUp),NULL);

            g_signal_connect(G_OBJECT (window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

            gtk_widget_show_all(window);

            help=window;

            gtk_main();

            return 0;
        }
    }
}
