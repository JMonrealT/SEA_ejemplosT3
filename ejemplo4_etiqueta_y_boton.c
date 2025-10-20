/*
 * Ejemplo 5: Etiqueta y Botón
 * 
 * Combinamos una etiqueta (label) con un botón que cambia el texto.
 * Introducimos contenedores para organizar múltiples widgets.
 * 
 * Compilar con:
 * gcc `pkg-config --cflags gtk+-3.0` ejemplo5_etiqueta_y_boton.c -o ejemplo5 `pkg-config --libs gtk+-3.0`
 */

#include <gtk/gtk.h>

// Variable global para la etiqueta
GtkWidget *label;
int contador = 0;

// Callback que actualiza la etiqueta
static void on_button_clicked(GtkWidget *widget, gpointer data)
{
    char texto[100];
    contador++;
    
    // Formatear el nuevo texto
    g_snprintf(texto, sizeof(texto), "¡Botón presionado %d veces!", contador);
    
    // Actualizar la etiqueta
    gtk_label_set_text(GTK_LABEL(label), texto);
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Etiqueta y Botón");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 150);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Crear un contenedor vertical (VBox)
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Crear etiqueta
    label = gtk_label_new("¡Hola! Presiona el botón.");
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);

    // Crear botón
    button = gtk_button_new_with_label("Presionar");
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);

    // Conectar callback del botón
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    // Conectar señal de cierre
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar todo
    gtk_widget_show_all(window);

    // Bucle principal
    gtk_main();

    return 0;
}