/*
 * Ejemplo 10: Calculadora Simple
 * 
 * Calculadora básica que integra todos los conceptos vistos:
 * botones, etiquetas, contenedores, callbacks y manejo de estados.
 * 
 * Compilar con:
 * gcc `pkg-config --cflags gtk+-3.0` ejemplo10_calculadora_simple.c -o ejemplo10 `pkg-config --libs gtk+-3.0`
 */

#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Variables globales
GtkWidget *display;
double numero_actual = 0.0;
double numero_anterior = 0.0;
char operacion = '\0';
gboolean nuevo_numero = TRUE;

// Función para convertir string a double ignorando locale
static double string_to_double(const char *str)
{
    // Crear una copia del string y reemplazar comas por puntos si las hay
    char temp[50];
    strcpy(temp, str);
    
    char *coma = strchr(temp, ',');
    if (coma != NULL) {
        *coma = '.';
    }
    
    return strtod(temp, NULL);
}

// Función para actualizar el display
static void actualizar_display(double valor)
{
    char texto[50];
    
    // Asegurar formato con punto decimal (no coma)
    // Formatear el número usando formato específico con punto
    if (valor == (int)valor) {
        sprintf(texto, "%.0f", valor);
    } else {
        sprintf(texto, "%.8g", valor);
    }
    
    // Reemplazar cualquier coma por punto (por si acaso)
    char *coma = strchr(texto, ',');
    if (coma != NULL) {
        *coma = '.';
    }
    
    gtk_label_set_text(GTK_LABEL(display), texto);
}

// Callback para números
static void on_numero_clicked(GtkWidget *widget, gpointer data)
{
    int numero = GPOINTER_TO_INT(data);
    const char *texto_actual = gtk_label_get_text(GTK_LABEL(display));
    char nuevo_texto[50];
    
    if (nuevo_numero) {
        sprintf(nuevo_texto, "%d", numero);
        nuevo_numero = FALSE;
    } else {
        sprintf(nuevo_texto, "%s%d", texto_actual, numero);
    }
    
    // Actualizar tanto el display como la variable interna
    gtk_label_set_text(GTK_LABEL(display), nuevo_texto);
    numero_actual = string_to_double(nuevo_texto);
}

// Callback para operaciones
static void on_operacion_clicked(GtkWidget *widget, gpointer data)
{
    char nueva_operacion = *(char*)data;
    const char *texto_actual = gtk_label_get_text(GTK_LABEL(display));
    
    // Asegurar que numero_actual refleja lo que está en pantalla
    if (!nuevo_numero) {
        numero_actual = string_to_double(texto_actual);
    }
    
    // DEBUG: Mostrar valores
    // printf("DEBUG - Operación '%c': numero_anterior=%.3f, numero_actual=%.3f, texto='%s'\n", 
    //        nueva_operacion, numero_anterior, numero_actual, texto_actual);
    
    if (!nuevo_numero && operacion != '\0') {
        // Realizar operación pendiente
        double resultado = numero_anterior;
        
        // printf("DEBUG - Calculando: %.3f %c %.3f\n", numero_anterior, operacion, numero_actual);
        
        switch (operacion) {
            case '+':
                resultado = numero_anterior + numero_actual;
                break;
            case '-':
                resultado = numero_anterior - numero_actual;
                break;
            case '*':
                resultado = numero_anterior * numero_actual;
                break;
            case '/':
                if (numero_actual != 0) {
                    resultado = numero_anterior / numero_actual;
                } else {
                    gtk_label_set_text(GTK_LABEL(display), "Error: División por cero");
                    return;
                }
                break;
        }
        
        // printf("DEBUG - Resultado: %.3f\n", resultado);
        numero_actual = resultado;
        actualizar_display(resultado);
    }
    
    numero_anterior = numero_actual;
    operacion = nueva_operacion;
    nuevo_numero = TRUE;
}

// Callback para igual
static void on_igual_clicked(GtkWidget *widget, gpointer data)
{
    if (operacion != '\0') {
        // Asegurar que numero_actual refleja lo que está en pantalla
        const char *texto_actual = gtk_label_get_text(GTK_LABEL(display));
        if (!nuevo_numero) {
            numero_actual = string_to_double(texto_actual);
        }
        
        on_operacion_clicked(widget, &operacion);
        operacion = '\0';
    }
}

// Callback para limpiar
static void on_clear_clicked(GtkWidget *widget, gpointer data)
{
    numero_actual = 0.0;
    numero_anterior = 0.0;
    operacion = '\0';
    nuevo_numero = TRUE;
    actualizar_display(0.0);
}

// Callback para punto decimal
static void on_punto_clicked(GtkWidget *widget, gpointer data)
{
    const char *texto_actual = gtk_label_get_text(GTK_LABEL(display));
    
    // Verificar si ya hay un punto decimal
    if (strchr(texto_actual, '.') == NULL) {
        char nuevo_texto[50];
        if (nuevo_numero) {
            sprintf(nuevo_texto, "0.");
            nuevo_numero = FALSE;
        } else {
            sprintf(nuevo_texto, "%s.", texto_actual);
        }
        gtk_label_set_text(GTK_LABEL(display), nuevo_texto);
        numero_actual = string_to_double(nuevo_texto);
        nuevo_numero = FALSE;
    }
}

// Función para crear un botón
static GtkWidget* crear_boton(const char *etiqueta, GCallback callback, gpointer data)
{
    GtkWidget *boton = gtk_button_new_with_label(etiqueta);
    gtk_widget_set_size_request(boton, 60, 50);
    g_signal_connect(boton, "clicked", callback, data);
    return boton;
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *vbox, *grid;
    
    // Datos para callbacks
    static char operaciones[] = {'+', '-', '*', '/'};

    // Inicializar GTK PRIMERO
    gtk_init(&argc, &argv);
    
    // Configurar locale para usar punto decimal DESPUÉS de gtk_init
    setlocale(LC_NUMERIC, "C");

    // Crear ventana principal
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculadora GTK");
    gtk_window_set_default_size(GTK_WINDOW(window), 280, 350);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    // Crear contenedor principal
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);

    // Crear display
    display = gtk_label_new("0");
    gtk_label_set_xalign(GTK_LABEL(display), 1.0); // Alinear a la derecha
    gtk_widget_set_size_request(display, -1, 50);
    
    // Estilo del display
    GtkStyleContext *context = gtk_widget_get_style_context(display);
    gtk_style_context_add_class(context, "display");
    
    // Marco para el display
    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(frame), display);
    gtk_box_pack_start(GTK_BOX(vbox), frame, FALSE, FALSE, 0);

    // Crear grid para botones
    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    // Crear botones de números y operaciones
    // Fila 1: C, /, *, -
    gtk_grid_attach(GTK_GRID(grid), crear_boton("C", G_CALLBACK(on_clear_clicked), NULL), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), crear_boton("/", G_CALLBACK(on_operacion_clicked), &operaciones[3]), 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), crear_boton("*", G_CALLBACK(on_operacion_clicked), &operaciones[2]), 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), crear_boton("-", G_CALLBACK(on_operacion_clicked), &operaciones[1]), 3, 0, 1, 1);

    // Fila 2: 7, 8, 9, +
    gtk_grid_attach(GTK_GRID(grid), crear_boton("7", G_CALLBACK(on_numero_clicked), GINT_TO_POINTER(7)), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), crear_boton("8", G_CALLBACK(on_numero_clicked), GINT_TO_POINTER(8)), 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), crear_boton("9", G_CALLBACK(on_numero_clicked), GINT_TO_POINTER(9)), 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), crear_boton("+", G_CALLBACK(on_operacion_clicked), &operaciones[0]), 3, 1, 1, 2);

    // Fila 3: 4, 5, 6
    gtk_grid_attach(GTK_GRID(grid), crear_boton("4", G_CALLBACK(on_numero_clicked), GINT_TO_POINTER(4)), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), crear_boton("5", G_CALLBACK(on_numero_clicked), GINT_TO_POINTER(5)), 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), crear_boton("6", G_CALLBACK(on_numero_clicked), GINT_TO_POINTER(6)), 2, 2, 1, 1);

    // Fila 4: 1, 2, 3, =
    gtk_grid_attach(GTK_GRID(grid), crear_boton("1", G_CALLBACK(on_numero_clicked), GINT_TO_POINTER(1)), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), crear_boton("2", G_CALLBACK(on_numero_clicked), GINT_TO_POINTER(2)), 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), crear_boton("3", G_CALLBACK(on_numero_clicked), GINT_TO_POINTER(3)), 2, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), crear_boton("=", G_CALLBACK(on_igual_clicked), NULL), 3, 3, 1, 2);

    // Fila 5: 0, .
    gtk_grid_attach(GTK_GRID(grid), crear_boton("0", G_CALLBACK(on_numero_clicked), GINT_TO_POINTER(0)), 0, 4, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), crear_boton(".", G_CALLBACK(on_punto_clicked), NULL), 2, 4, 1, 1);

    // Conectar señal de cierre
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar todos los widgets
    gtk_widget_show_all(window);

    // Bucle principal
    gtk_main();

    return 0;
}