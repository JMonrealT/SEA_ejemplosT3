/*
 * EJEMPLO 4: Botón con callback
 * 
 * Este ejemplo muestra la diferencia entre printf() y g_print():
 * - printf() aparece en el terminal original
 * - g_print() aparece en un terminal separado
 * 
 * NOTA: Los mensajes de error sobre D-Bus al inicio son normales en algunos sistemas
 * y no afectan el funcionamiento del programa.
 * 
 * Compilación: gcc -o ejemplo4 ejemplo4_boton_con_callback.c `pkg-config --cflags --libs gtk+-3.0`
 */

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

// Contador de clicks
static int click_count = 0;
static FILE *g_print_file = NULL;

// Handler personalizado para redirigir g_print al terminal separado
static void redirect_g_print(const gchar *message)
{
    if (g_print_file) {
        fprintf(g_print_file, "%s", message);
        fflush(g_print_file);  // Forzar que se escriba inmediatamente
    }
}

// Función callback que se ejecuta cuando se hace click en el botón
static void on_button_clicked(GtkWidget *widget, gpointer data)
{
    click_count++;
    
    // printf() se muestra en el terminal original
    printf("printf(): Click %d - terminal original\n", click_count);
    
    // g_print() se redirige al terminal separado
    g_print("g_print(): Click %d - terminal separado\n", click_count);
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Crear un named pipe para comunicarse con el terminal
    system("rm -f /tmp/gtk_log");  // Limpiar pipe anterior
    system("mkfifo /tmp/gtk_log");
    
    // Abrir terminal separado (puede depender del SO y versión)
    system("x-terminal-emulator -T 'Salida de g_print()' "
           "-e bash -c 'echo \"=== Terminal para g_print() ===\"; "
           "echo \"Los mensajes de g_print aparecerán aquí:\"; echo; "
           "while IFS= read -r line; do echo \"$line\"; done < /tmp/gtk_log' &");
    
    // Dar tiempo para que se abra el terminal
    sleep(1);
    
    // Abrir el pipe para escritura
    g_print_file = fopen("/tmp/gtk_log", "w");
    
    // Configurar el handler personalizado para g_print
    g_set_print_handler(redirect_g_print);
    
    // Mensaje inicial
    printf("printf(): Aplicación iniciada - terminal original\n");
    g_print("g_print(): Aplicación iniciada - terminal separado\n");

    // Crear ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "printf vs g_print");
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Crear botón
    button = gtk_button_new_with_label("¡Presiona y mira ambos terminales!");

    // Conectar el callback del botón
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    // Añadir botón a la ventana
    gtk_container_add(GTK_CONTAINER(window), button);

    // Conectar señal de cierre
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar widgets
    gtk_widget_show_all(window);

    // Bucle principal
    gtk_main();

    // Limpiar al cerrar
    if (g_print_file) {
        fclose(g_print_file);
        unlink("/tmp/gtk_log");
    }

    return 0;
}