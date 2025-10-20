/*
 * Ejemplo 6: Entrada de Texto
 * 
 * Introducimos el widget GtkEntry para entrada de texto.
 * El botón mostrará el texto introducido en la etiqueta.
 * 
 * Compilar con:
 * gcc `pkg-config --cflags gtk+-3.0` ejemplo6_entrada_de_texto.c -o ejemplo6 `pkg-config --libs gtk+-3.0`
 */

#include <gtk/gtk.h>

// Widgets globales
GtkWidget *entry;
GtkWidget *label;

// Callback que lee el texto del entry y lo muestra en el label
static void on_button_clicked(GtkWidget *widget, gpointer data)
{
    const char *texto_entrada;
    char mensaje[200];
    
    // Obtener el texto del entry
    texto_entrada = gtk_entry_get_text(GTK_ENTRY(entry));
    
    // Verificar si hay texto
    if (strlen(texto_entrada) > 0) {
        g_snprintf(mensaje, sizeof(mensaje), "Has escrito: '%s'", texto_entrada);
    } else {
        g_snprintf(mensaje, sizeof(mensaje), "No has escrito nada.");
    }
    
    // Actualizar la etiqueta
    gtk_label_set_text(GTK_LABEL(label), mensaje);
}

// Callback para limpiar el texto
static void on_clear_clicked(GtkWidget *widget, gpointer data)
{
    gtk_entry_set_text(GTK_ENTRY(entry), "");
    gtk_label_set_text(GTK_LABEL(label), "Campo limpiado.");
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *button_mostrar, *button_limpiar;
    GtkWidget *box;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Entrada de Texto");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Crear contenedor vertical
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), box);
    
    // Añadir márgenes al contenedor
    gtk_container_set_border_width(GTK_CONTAINER(box), 10);

    // Crear entry (campo de entrada)
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Escribe algo aquí...");
    gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 0);

    // Crear botón para mostrar texto
    button_mostrar = gtk_button_new_with_label("Mostrar Texto");
    gtk_box_pack_start(GTK_BOX(box), button_mostrar, FALSE, FALSE, 0);

    // Crear botón para limpiar
    button_limpiar = gtk_button_new_with_label("Limpiar");
    gtk_box_pack_start(GTK_BOX(box), button_limpiar, FALSE, FALSE, 0);

    // Crear etiqueta para mostrar resultados
    label = gtk_label_new("Escribe algo y presiona 'Mostrar Texto'");
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);

    // Conectar callbacks
    g_signal_connect(button_mostrar, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(button_limpiar, "clicked", G_CALLBACK(on_clear_clicked), NULL);
    
    // También podemos conectar Enter en el entry
    g_signal_connect(entry, "activate", G_CALLBACK(on_button_clicked), NULL);

    // Conectar señal de cierre
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar todo
    gtk_widget_show_all(window);

    // Bucle principal
    gtk_main();

    return 0;
}