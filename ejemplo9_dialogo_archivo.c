/*
 * Ejemplo 9: Diálogo de Archivo
 * 
 * Introducimos diálogos para seleccionar archivos.
 * Mostramos cómo abrir diálogos modales y obtener rutas de archivos.
 * 
 * Compilar con:
 * gcc `pkg-config --cflags gtk+-3.0` ejemplo9_dialogo_archivo.c -o ejemplo9 `pkg-config --libs gtk+-3.0`
 */

#include <gtk/gtk.h>
#include <stdio.h>

GtkWidget *label_archivo;
GtkWidget *text_view;

// Callback para abrir archivo
static void on_abrir_archivo(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog;
    GtkWidget *parent_window = GTK_WIDGET(data);
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Abrir Archivo",
                                        GTK_WINDOW(parent_window),
                                        action,
                                        "Cancelar",
                                        GTK_RESPONSE_CANCEL,
                                        "Abrir",
                                        GTK_RESPONSE_ACCEPT,
                                        NULL);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        
        // Actualizar la etiqueta con el nombre del archivo
        char mensaje[500];
        g_snprintf(mensaje, sizeof(mensaje), "Archivo seleccionado: %s", filename);
        gtk_label_set_text(GTK_LABEL(label_archivo), mensaje);
        
        // Intentar leer y mostrar el contenido (solo para archivos de texto pequeños)
        FILE *file = fopen(filename, "r");
        if (file != NULL) {
            char contenido[1000] = {0};
            size_t bytes_leidos = fread(contenido, 1, sizeof(contenido)-1, file);
            fclose(file);
            
            if (bytes_leidos > 0) {
                GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
                gtk_text_buffer_set_text(buffer, contenido, -1);
            }
        }
        
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

// Callback para guardar archivo
static void on_guardar_archivo(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog;
    GtkWidget *parent_window = GTK_WIDGET(data);
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Guardar Archivo",
                                        GTK_WINDOW(parent_window),
                                        action,
                                        "Cancelar",
                                        GTK_RESPONSE_CANCEL,
                                        "Guardar",
                                        GTK_RESPONSE_ACCEPT,
                                        NULL);

    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);

        // Obtener texto del text_view
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
        GtkTextIter start, end;
        gtk_text_buffer_get_bounds(buffer, &start, &end);
        char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

        // Guardar archivo
        FILE *file = fopen(filename, "w");
        if (file != NULL) {
            fprintf(file, "%s", text);
            fclose(file);
            
            char mensaje[500];
            g_snprintf(mensaje, sizeof(mensaje), "Archivo guardado: %s", filename);
            gtk_label_set_text(GTK_LABEL(label_archivo), mensaje);
        }

        g_free(text);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *button_abrir, *button_guardar;
    GtkWidget *scrolled_window;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear ventana principal
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Editor de Texto Simple");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Crear contenedor vertical principal
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);

    // Crear contenedor horizontal para botones
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    // Crear botones
    button_abrir = gtk_button_new_with_label("Abrir Archivo");
    button_guardar = gtk_button_new_with_label("Guardar Archivo");
    
    gtk_box_pack_start(GTK_BOX(hbox), button_abrir, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button_guardar, FALSE, FALSE, 0);

    // Etiqueta para mostrar archivo actual
    label_archivo = gtk_label_new("Ningún archivo seleccionado");
    gtk_label_set_xalign(GTK_LABEL(label_archivo), 0.0);
    gtk_box_pack_start(GTK_BOX(vbox), label_archivo, FALSE, FALSE, 0);

    // Crear área de texto con scroll
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                  GTK_POLICY_AUTOMATIC,
                                  GTK_POLICY_AUTOMATIC);
    
    text_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    // Texto inicial
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, "Escribe aquí tu texto o abre un archivo...", -1);

    // Conectar callbacks
    g_signal_connect(button_abrir, "clicked", G_CALLBACK(on_abrir_archivo), window);
    g_signal_connect(button_guardar, "clicked", G_CALLBACK(on_guardar_archivo), window);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar todos los widgets
    gtk_widget_show_all(window);

    // Bucle principal
    gtk_main();

    return 0;
}