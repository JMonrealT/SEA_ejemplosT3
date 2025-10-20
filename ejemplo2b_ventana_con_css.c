/*
 * Ejemplo 2b: Ventana con CSS básico
 * 
 * Este ejemplo muestra cómo añadir estilo CSS sencillo a una ventana GTK.
 * Aprenderás los conceptos básicos de personalización visual.
 * 
 * Compilar con:
 * gcc `pkg-config --cflags gtk+-3.0` ejemplo2b_ventana_con_css.c -o ejemplo2b `pkg-config --libs gtk+-3.0`
 */

#include <gtk/gtk.h>

// Función para aplicar CSS básico
static void aplicar_css_basico(void)
{
    GtkCssProvider *css_provider;
    GdkDisplay *display;
    GdkScreen *screen;

    // CSS básico - solo colores y fuente
    const gchar *css_data = 
        "window {"
        "    background-color: #006ccb;"  /* Azul */
        "    font-family: 'Sans';"
        "    font-size: 14px;"
        "}";

    css_provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    // Cargar el CSS
    gtk_css_provider_load_from_data(css_provider, css_data, -1, NULL);

    // Aplicar el CSS a toda la aplicación
    gtk_style_context_add_provider_for_screen(screen,
                                               GTK_STYLE_PROVIDER(css_provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_object_unref(css_provider);
}

int main(int argc, char *argv[])
{
    GtkWidget *window;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Aplicar CSS básico antes de crear widgets
    aplicar_css_basico();

    // Crear ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Ventana con CSS Básico");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Conectar señal de cierre
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar ventana
    gtk_widget_show(window);

    // Bucle principal
    gtk_main();

    return 0;
}