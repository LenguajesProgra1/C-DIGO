#ifndef AGREGAR_AMIGO_H
#include <gtk/gtk.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define	AGREGAR_AMIGO_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    int Interfaz(int argc, char** argv);
    void Agregar (GtkWidget *boton, GdkEventKey *event);



#ifdef	__cplusplus
}
#endif

#endif	/* AGREGAR_AMIGO_H */

