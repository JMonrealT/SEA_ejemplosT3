/*
 * Ejemplo 2: Ventana con Título y Tamaño
 * 
 * En este ejemplo añadimos un título a la ventana
 * y definimos su tamaño inicial.
 * 
 * Compilar con:
 * gcc `pkg-config --cflags gtk+-3.0` ejemplo2_ventana_con_titulo.c -o ejemplo2 `pkg-config --libs gtk+-3.0`
 */

#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    GtkWidget *window;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear una nueva ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Establecer el título de la ventana
    gtk_window_set_title(GTK_WINDOW(window), "Mi Primera Ventana GTK");

    // Establecer el tamaño de la ventana (ancho, alto)
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Centrar la ventana en la pantalla
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Conectar la señal de cierre
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar la ventana
    gtk_widget_show(window);

    // Iniciar el bucle principal
    gtk_main();

    return 0;
}