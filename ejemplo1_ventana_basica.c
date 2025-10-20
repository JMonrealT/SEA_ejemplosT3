/*
 * Ejemplo 1: Ventana Básica
 * 
 * Este es el ejemplo más simple posible de GTK.
 * Crea una ventana vacía que se puede cerrar.
 * 
 * Compilar con:
 * gcc `pkg-config --cflags gtk+-3.0` ejemplo1_ventana_basica.c -o ejemplo1 `pkg-config --libs gtk+-3.0`
 */

#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    GtkWidget *window;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear una nueva ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Conectar la señal de cierre de ventana
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar la ventana
    gtk_widget_show(window);

    // Iniciar el bucle principal de GTK
    gtk_main();

    return 0;
}