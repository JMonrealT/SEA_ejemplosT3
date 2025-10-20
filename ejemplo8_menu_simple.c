/*
 * Ejemplo 8: Menú Simple
 * 
 * Introducimos menús y barras de menú.
 * Creamos una ventana con menú Archivo que incluye opciones básicas.
 * 
 * Compilar con:
 * gcc `pkg-config --cflags gtk+-3.0` ejemplo8_menu_simple.c -o ejemplo8 `pkg-config --libs gtk+-3.0`
 */

#include <gtk/gtk.h>

GtkWidget *label_estado;

// Callbacks para elementos del menú
static void on_nuevo_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    gtk_label_set_text(GTK_LABEL(label_estado), "Nuevo archivo seleccionado");
}

static void on_abrir_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    gtk_label_set_text(GTK_LABEL(label_estado), "Abrir archivo seleccionado");
}

static void on_guardar_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    gtk_label_set_text(GTK_LABEL(label_estado), "Guardar archivo seleccionado");
}

static void on_acerca_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    GtkWidget *dialog;
    GtkWidget *parent_window = GTK_WIDGET(user_data);
    
    dialog = gtk_message_dialog_new(GTK_WINDOW(parent_window),
                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                   GTK_MESSAGE_INFO,
                                   GTK_BUTTONS_OK,
                                   "Ejemplo de Menú GTK\nVersión 1.0");
    
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void on_salir_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    gtk_main_quit();
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *menubar;
    GtkWidget *menu_archivo, *menu_ayuda;
    GtkWidget *menuitem_archivo, *menuitem_ayuda;
    GtkWidget *menuitem_nuevo, *menuitem_abrir, *menuitem_guardar;
    GtkWidget *menuitem_separador, *menuitem_salir;
    GtkWidget *menuitem_acerca;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear ventana principal
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Ejemplo con Menú");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Crear contenedor vertical principal
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Crear barra de menú
    menubar = gtk_menu_bar_new();

    // Crear menú "Archivo"
    menu_archivo = gtk_menu_new();
    menuitem_archivo = gtk_menu_item_new_with_label("Archivo");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem_archivo), menu_archivo);

    // Elementos del menú Archivo
    menuitem_nuevo = gtk_menu_item_new_with_label("Nuevo");
    menuitem_abrir = gtk_menu_item_new_with_label("Abrir");
    menuitem_guardar = gtk_menu_item_new_with_label("Guardar");
    menuitem_separador = gtk_separator_menu_item_new();
    menuitem_salir = gtk_menu_item_new_with_label("Salir");

    // Añadir elementos al menú Archivo
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), menuitem_nuevo);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), menuitem_abrir);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), menuitem_guardar);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), menuitem_separador);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_archivo), menuitem_salir);

    // Crear menú "Ayuda"
    menu_ayuda = gtk_menu_new();
    menuitem_ayuda = gtk_menu_item_new_with_label("Ayuda");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem_ayuda), menu_ayuda);

    menuitem_acerca = gtk_menu_item_new_with_label("Acerca de...");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_ayuda), menuitem_acerca);

    // Añadir menús principales a la barra
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menuitem_archivo);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menuitem_ayuda);

    // Añadir barra de menú al contenedor
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    // Crear etiqueta de estado
    label_estado = gtk_label_new("Bienvenido. Selecciona una opción del menú.");
    gtk_box_pack_start(GTK_BOX(vbox), label_estado, TRUE, TRUE, 10);

    // Conectar callbacks de los menús
    g_signal_connect(menuitem_nuevo, "activate", G_CALLBACK(on_nuevo_activate), NULL);
    g_signal_connect(menuitem_abrir, "activate", G_CALLBACK(on_abrir_activate), NULL);
    g_signal_connect(menuitem_guardar, "activate", G_CALLBACK(on_guardar_activate), NULL);
    g_signal_connect(menuitem_salir, "activate", G_CALLBACK(on_salir_activate), NULL);
    g_signal_connect(menuitem_acerca, "activate", G_CALLBACK(on_acerca_activate), window);

    // Conectar señal de cierre de ventana
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar todos los widgets
    gtk_widget_show_all(window);

    // Bucle principal
    gtk_main();

    return 0;
}