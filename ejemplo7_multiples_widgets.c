/*
 * Ejemplo 7: Múltiples Widgets
 * 
 * Combinamos varios widgets: etiqueta, entrada de texto, botones y una barra de progreso.
 * Introducimos diferentes tipos de contenedores para organizar la interfaz.
 * 
 * Compilar con:
 * gcc `pkg-config --cflags gtk+-3.0` ejemplo7_multiples_widgets.c -o ejemplo7 `pkg-config --libs gtk+-3.0`
 */

#include <gtk/gtk.h>

// Widgets globales
GtkWidget *entry_nombre, *entry_edad;
GtkWidget *label_resultado;
GtkWidget *progress_bar;
GtkWidget *checkbutton;

// Callback para procesar datos
static void on_procesar_clicked(GtkWidget *widget, gpointer data)
{
    const char *nombre = gtk_entry_get_text(GTK_ENTRY(entry_nombre));
    const char *edad_str = gtk_entry_get_text(GTK_ENTRY(entry_edad));
    gboolean es_estudiante = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton));
    
    char mensaje[300];
    
    if (strlen(nombre) > 0 && strlen(edad_str) > 0) {
        int edad = atoi(edad_str);
        g_snprintf(mensaje, sizeof(mensaje), 
                  "Nombre: %s\nEdad: %d años\n%s", 
                  nombre, edad, 
                  es_estudiante ? "Es estudiante" : "No es estudiante");
        
        // Actualizar barra de progreso
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), 1.0);
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress_bar), "¡Completado!");
    } else {
        g_snprintf(mensaje, sizeof(mensaje), "Por favor, completa todos los campos.");
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), 0.0);
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress_bar), "Incompleto");
    }
    
    gtk_label_set_text(GTK_LABEL(label_resultado), mensaje);
}

// Callback para limpiar formulario
static void on_limpiar_clicked(GtkWidget *widget, gpointer data)
{
    gtk_entry_set_text(GTK_ENTRY(entry_nombre), "");
    gtk_entry_set_text(GTK_ENTRY(entry_edad), "");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton), FALSE);
    gtk_label_set_text(GTK_LABEL(label_resultado), "Formulario limpiado.");
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), 0.0);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress_bar), "Esperando...");
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *main_box, *form_box, *button_box;
    GtkWidget *label_nombre, *label_edad;
    GtkWidget *button_procesar, *button_limpiar;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear ventana principal
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Formulario Completo");
    gtk_window_set_default_size(GTK_WINDOW(window), 450, 350);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Crear contenedor principal vertical
    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), main_box);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 15);

    // Crear sección del formulario
    form_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(main_box), form_box, FALSE, FALSE, 0);

    // Campo nombre
    label_nombre = gtk_label_new("Nombre:");
    gtk_label_set_xalign(GTK_LABEL(label_nombre), 0.0);
    gtk_box_pack_start(GTK_BOX(form_box), label_nombre, FALSE, FALSE, 0);
    
    entry_nombre = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_nombre), "Introduce tu nombre");
    gtk_box_pack_start(GTK_BOX(form_box), entry_nombre, FALSE, FALSE, 0);

    // Campo edad
    label_edad = gtk_label_new("Edad:");
    gtk_label_set_xalign(GTK_LABEL(label_edad), 0.0);
    gtk_box_pack_start(GTK_BOX(form_box), label_edad, FALSE, FALSE, 0);
    
    entry_edad = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_edad), "Introduce tu edad");
    gtk_box_pack_start(GTK_BOX(form_box), entry_edad, FALSE, FALSE, 0);

    // Checkbox
    checkbutton = gtk_check_button_new_with_label("Soy estudiante");
    gtk_box_pack_start(GTK_BOX(form_box), checkbutton, FALSE, FALSE, 5);

    // Barra de progreso
    progress_bar = gtk_progress_bar_new();
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress_bar), "Esperando...");
    gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progress_bar), TRUE);
    gtk_box_pack_start(GTK_BOX(main_box), progress_bar, FALSE, FALSE, 0);

    // Contenedor horizontal para botones
    button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(main_box), button_box, FALSE, FALSE, 0);

    // Botones
    button_procesar = gtk_button_new_with_label("Procesar");
    button_limpiar = gtk_button_new_with_label("Limpiar");
    
    gtk_box_pack_start(GTK_BOX(button_box), button_procesar, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_box), button_limpiar, TRUE, TRUE, 0);

    // Etiqueta de resultado
    label_resultado = gtk_label_new("Completa el formulario y presiona 'Procesar'");
    gtk_label_set_line_wrap(GTK_LABEL(label_resultado), TRUE);
    gtk_box_pack_start(GTK_BOX(main_box), label_resultado, TRUE, TRUE, 0);

    // Conectar callbacks
    g_signal_connect(button_procesar, "clicked", G_CALLBACK(on_procesar_clicked), NULL);
    g_signal_connect(button_limpiar, "clicked", G_CALLBACK(on_limpiar_clicked), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar todos los widgets
    gtk_widget_show_all(window);

    // Bucle principal
    gtk_main();

    return 0;
}