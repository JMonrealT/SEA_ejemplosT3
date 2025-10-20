/*
 * Ejemplo 3: Botón Simple
 * 
 * Introducimos nuestro primer widget: un botón.
 * El botón no hace nada aún, pero es clickeable.
 * 
 * Compilar con:
 * gcc `pkg-config --cflags gtk+-3.0` ejemplo3_boton_simple.c -o ejemplo3 `pkg-config --libs gtk+-3.0`
 */

#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear ventana principal
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Ejemplo con Botón");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 150);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Crear un botón con texto
    button = gtk_button_new_with_label("¡Haz click aquí!");

    // Añadir el botón a la ventana
    gtk_container_add(GTK_CONTAINER(window), button);

    // Conectar señal de cierre de ventana
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar todos los widgets
    gtk_widget_show_all(window);

    // Iniciar bucle principal
    gtk_main();

    return 0;
}