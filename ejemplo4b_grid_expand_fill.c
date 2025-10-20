/*
 * Ejemplo 4b: Comparativa visual de Expand y Fill con Grid Diagonal
 * 
 * Este ejemplo muestra las 4 combinaciones de expand/fill en un grid diagonal 4×4
 * con bordes visibles para facilitar la comprensión de la estructura.
 * 
 * - expand: ¿El widget puede crecer para tomar espacio extra de su celda?
 * - fill: ¿El widget llena todo el espacio asignado o se centra en él?
 * 
 * Compilar con:
 * gcc `pkg-config --cflags gtk+-3.0` ejemplo4b_grid_expand_fill.c -o ejemplo4b `pkg-config --libs gtk+-3.0`
 */

#include <gtk/gtk.h>

// Función para aplicar CSS que muestra los bordes del grid
static void aplicar_estilos_grid(void)
{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    
    const gchar *css_data = 
        "grid { "
        "  background-color: #e0e0e0; "  // Fondo gris claro para ver el grid
        "}"
        "button { "
        "  border: 2px solid #333; "      // Borde oscuro para los botones
        "  margin: 2px; "                 // Pequeño margen para ver separación
        "  font-size: 11px; "
        "  padding: 10px; "
        "}";
    
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    
    gtk_style_context_add_provider_for_screen(screen,
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    gtk_css_provider_load_from_data(provider, css_data, -1, NULL);
    g_object_unref(provider);
}

// Callback que muestra información sobre el botón clickeado
static void on_boton_clicked(GtkWidget *widget, gpointer data)
{
    const char *mensaje = (const char*)data;
    g_print("\n%s\n", mensaje);
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *main_box, *grid;
    GtkWidget *label_titulo;
    GtkWidget *boton_expand_fill, *boton_expand_nofill;
    GtkWidget *boton_noexpand_fill, *boton_noexpand_nofill;

    // Inicializar GTK
    gtk_init(&argc, &argv);
    
    // Aplicar estilos CSS para visualizar el grid
    aplicar_estilos_grid();

    // Crear ventana principal
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Expand vs Fill - Comparación Lado a Lado");
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 500);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    
    // Crear contenedor principal vertical
    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), main_box);
    gtk_container_set_border_width(GTK_CONTAINER(main_box), 15);
    
    // Título explicativo
    label_titulo = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label_titulo), 
        "<b>Comparativa visual de Expand y Fill</b>\n"
        "Observa cómo cada botón se comporta diferente al redimensionar la ventana");
    gtk_label_set_justify(GTK_LABEL(label_titulo), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(main_box), label_titulo, FALSE, FALSE, 0);

    // Crear grid 4x4 para los 4 botones en diagonal
    // Máxima independencia y claridad visual
    grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(main_box), grid, TRUE, TRUE, 0);
    
    // Configurar espaciado del grid (muy generoso para separación clara)
    gtk_grid_set_row_spacing(GTK_GRID(grid), 40);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 40);
    
    // El grid se expande para llenar la ventana
    gtk_widget_set_hexpand(grid, TRUE);
    gtk_widget_set_vexpand(grid, TRUE);
    
    // NO configurar como homogéneo para que expand tenga efecto visual
    // Esto permite que cada fila/columna tenga su propio tamaño según sus widgets
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), FALSE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), FALSE);

    /*
     * ==========================================
     * CREAR LOS 4 BOTONES EN GRID 4×2 (2 filas, 4 columnas)
     * ==========================================
     * 
     * NUEVA DISTRIBUCIÓN para MÁXIMA claridad visual:
     * 
     * Fila 0: AMBOS con expand=TRUE (compiten por espacio)
     *   - Col 0: fill=TRUE  (llena toda su celda grande)
     *   - Col 3: fill=FALSE (se centra en su celda grande)
     * 
     * Fila 1: AMBOS con expand=FALSE (tamaño mínimo)
     *   - Col 0: fill=TRUE  (llena su celda pequeña)
     *   - Col 3: fill=FALSE (se centra en su celda pequeña)
     * 
     * Columnas 1 y 2 quedan VACÍAS como separadores visuales
     * 
     * Grid visual:
     *     Col 0       Col 1    Col 2    Col 3
     *   ┌─────────┬─────────┬─────────┬─────────┐
     * 0 │ Botón1  │ (vacío) │ (vacío) │ Botón2  │  expand=TRUE
     *   ├─────────┼─────────┼─────────┼─────────┤
     * 1 │ Botón3  │ (vacío) │ (vacío) │ Botón4  │  expand=FALSE
     *   └─────────┴─────────┴─────────┴─────────┘
     *   fill=TRUE                      fill=FALSE
     * 
     * VENTAJA: Comparación directa en cada fila
     */

    // BOTÓN 1: expand=TRUE, fill=TRUE - Posición [0,0]
    boton_expand_fill = gtk_button_new_with_label(
        "[Fila 0, Col 0]\n\n"
        "expand=TRUE\n"
        "fill=TRUE\n\n"
        "Tomo espacio extra\n"
        "Y LO LLENO TODO"
    );
    gtk_grid_attach(GTK_GRID(grid), boton_expand_fill, 0, 0, 1, 1);
    gtk_widget_set_hexpand(boton_expand_fill, TRUE);   // SÍ se expande
    gtk_widget_set_vexpand(boton_expand_fill, TRUE);
    gtk_widget_set_halign(boton_expand_fill, GTK_ALIGN_FILL);  // Llena todo
    gtk_widget_set_valign(boton_expand_fill, GTK_ALIGN_FILL);
    g_signal_connect(boton_expand_fill, "clicked", G_CALLBACK(on_boton_clicked),
        "EXPAND=TRUE, FILL=TRUE: Tomo espacio Y lo lleno completamente");

    // BOTÓN 2: expand=TRUE, fill=FALSE - Posición [3,0]
    boton_expand_nofill = gtk_button_new_with_label(
        "[Fila 0, Col 3]\n\n"
        "expand=TRUE\n"
        "fill=FALSE\n\n"
        "Tomo espacio extra\n"
        "pero me CENTRO"
    );
    gtk_grid_attach(GTK_GRID(grid), boton_expand_nofill, 3, 0, 1, 1);
    gtk_widget_set_hexpand(boton_expand_nofill, TRUE);   // SÍ se expande
    gtk_widget_set_vexpand(boton_expand_nofill, TRUE);
    gtk_widget_set_halign(boton_expand_nofill, GTK_ALIGN_CENTER);  // Pero se centra
    gtk_widget_set_valign(boton_expand_nofill, GTK_ALIGN_CENTER);
    g_signal_connect(boton_expand_nofill, "clicked", G_CALLBACK(on_boton_clicked),
        "EXPAND=TRUE, FILL=FALSE: Tomo espacio pero mantengo tamaño natural centrado");

    // BOTÓN 3: expand=FALSE, fill=TRUE - Posición [0,1]
    boton_noexpand_fill = gtk_button_new_with_label(
        "[Fila 1, Col 0]\n\n"
        "expand=FALSE\n"
        "fill=TRUE\n\n"
        "Tamaño mínimo\n"
        "pero LO LLENO"
    );
    gtk_grid_attach(GTK_GRID(grid), boton_noexpand_fill, 0, 1, 1, 1);
    gtk_widget_set_hexpand(boton_noexpand_fill, FALSE);  // NO se expande
    gtk_widget_set_vexpand(boton_noexpand_fill, FALSE);
    gtk_widget_set_halign(boton_noexpand_fill, GTK_ALIGN_FILL);  // Pero llena
    gtk_widget_set_valign(boton_noexpand_fill, GTK_ALIGN_FILL);
    g_signal_connect(boton_noexpand_fill, "clicked", G_CALLBACK(on_boton_clicked),
        "EXPAND=FALSE, FILL=TRUE: NO tomo espacio pero lleno mi celda pequeña");

    // BOTÓN 4: expand=FALSE, fill=FALSE - Posición [3,1]
    boton_noexpand_nofill = gtk_button_new_with_label(
        "[Fila 1, Col 3]\n\n"
        "expand=FALSE\n"
        "fill=FALSE\n\n"
        "Tamaño mínimo\n"
        "y me CENTRO"
    );
    gtk_grid_attach(GTK_GRID(grid), boton_noexpand_nofill, 3, 1, 1, 1);
    gtk_widget_set_hexpand(boton_noexpand_nofill, FALSE);  // NO se expande
    gtk_widget_set_vexpand(boton_noexpand_nofill, FALSE);
    gtk_widget_set_halign(boton_noexpand_nofill, GTK_ALIGN_CENTER);  // Y se centra
    gtk_widget_set_valign(boton_noexpand_nofill, GTK_ALIGN_CENTER);
    g_signal_connect(boton_noexpand_nofill, "clicked", G_CALLBACK(on_boton_clicked),
        "EXPAND=FALSE, FILL=FALSE: Tamaño mínimo centrado en mi celda pequeña");

        // BOTÓN 1: expand=TRUE, fill=TRUE - Diagonal [0,0]
    boton_expand_fill = gtk_button_new_with_label(
        "[Fila 0, Col 0]\n\n"
        "expand=TRUE\nfill=TRUE\n\n"
        "Tomo espacio extra\nY lo lleno TODO"
    );
    gtk_grid_attach(GTK_GRID(grid), boton_expand_fill, 0, 0, 1, 1);
    gtk_widget_set_hexpand(boton_expand_fill, TRUE);   // SÍ se expande
    gtk_widget_set_vexpand(boton_expand_fill, TRUE);
    gtk_widget_set_halign(boton_expand_fill, GTK_ALIGN_FILL);  // Llena todo
    gtk_widget_set_valign(boton_expand_fill, GTK_ALIGN_FILL);
    g_signal_connect(boton_expand_fill, "clicked", G_CALLBACK(on_boton_clicked),
        "EXPAND=TRUE, FILL=TRUE: Compito por espacio extra y lo lleno completamente");

    // BOTÓN 2: expand=TRUE, fill=FALSE - Diagonal [1,1]
    boton_expand_nofill = gtk_button_new_with_label(
        "[Fila 1, Col 1]\n\n"
        "expand=TRUE\nfill=FALSE\n\n"
        "Tomo espacio extra\npero me CENTRO"
    );
    gtk_grid_attach(GTK_GRID(grid), boton_expand_nofill, 1, 1, 1, 1);
    gtk_widget_set_hexpand(boton_expand_nofill, TRUE);   // SÍ se expande
    gtk_widget_set_vexpand(boton_expand_nofill, TRUE);
    gtk_widget_set_halign(boton_expand_nofill, GTK_ALIGN_CENTER);  // Pero se centra
    gtk_widget_set_valign(boton_expand_nofill, GTK_ALIGN_CENTER);
    g_signal_connect(boton_expand_nofill, "clicked", G_CALLBACK(on_boton_clicked),
        "EXPAND=TRUE, FILL=FALSE: Compito por espacio pero mantengo mi tamaño y me centro");

    // BOTÓN 3: expand=FALSE, fill=TRUE - Diagonal [2,2]
    boton_noexpand_fill = gtk_button_new_with_label(
        "[Fila 2, Col 2]\n\n"
        "expand=FALSE\nfill=TRUE\n\n"
        "Tamaño mínimo\npero lo LLENO"
    );
    gtk_grid_attach(GTK_GRID(grid), boton_noexpand_fill, 2, 2, 1, 1);
    gtk_widget_set_hexpand(boton_noexpand_fill, FALSE);  // NO se expande
    gtk_widget_set_vexpand(boton_noexpand_fill, FALSE);
    gtk_widget_set_halign(boton_noexpand_fill, GTK_ALIGN_FILL);  // Pero llena
    gtk_widget_set_valign(boton_noexpand_fill, GTK_ALIGN_FILL);
    g_signal_connect(boton_noexpand_fill, "clicked", G_CALLBACK(on_boton_clicked),
        "EXPAND=FALSE, FILL=TRUE: NO compito por espacio pero lleno lo que me toca");

    // BOTÓN 4: expand=FALSE, fill=FALSE - Diagonal [3,3]
    boton_noexpand_nofill = gtk_button_new_with_label(
        "[Fila 3, Col 3]\n\n"
        "expand=FALSE\nfill=FALSE\n\n"
        "Tamaño mínimo\ny me CENTRO"
    );
    gtk_grid_attach(GTK_GRID(grid), boton_noexpand_nofill, 3, 3, 1, 1);
    gtk_widget_set_hexpand(boton_noexpand_nofill, FALSE);  // NO se expande
    gtk_widget_set_vexpand(boton_noexpand_nofill, FALSE);
    gtk_widget_set_halign(boton_noexpand_nofill, GTK_ALIGN_CENTER);  // Y se centra
    gtk_widget_set_valign(boton_noexpand_nofill, GTK_ALIGN_CENTER);
    g_signal_connect(boton_noexpand_nofill, "clicked", G_CALLBACK(on_boton_clicked),
        "EXPAND=FALSE, FILL=FALSE: NO compito por espacio y mantengo mi tamaño centrado");
    
    // Aplicar estilos CSS para visualizar el grid con bordes
    aplicar_estilos_grid();

    // Mostrar información en consola
    g_print("\n╔════════════════════════════════════════════════════════════╗\n");
    boton_expand_nofill = gtk_button_new_with_label(
        "[Fila 1, Col 1]\n\n"
        "expand=TRUE\nfill=FALSE\n\n"
        "Tomo espacio extra\npero me CENTRO"
    );
    gtk_grid_attach(GTK_GRID(grid), boton_expand_nofill, 1, 1, 1, 1);
    gtk_widget_set_hexpand(boton_expand_nofill, TRUE);   // SÍ se expande
    gtk_widget_set_vexpand(boton_expand_nofill, TRUE);
    gtk_widget_set_halign(boton_expand_nofill, GTK_ALIGN_CENTER);  // Pero se centra
    gtk_widget_set_valign(boton_expand_nofill, GTK_ALIGN_CENTER);
    g_signal_connect(boton_expand_nofill, "clicked", G_CALLBACK(on_boton_clicked),
        "BOTÓN [1,1]: EXPAND=TRUE, FILL=FALSE → Compito por espacio pero me centro");

    // BOTÓN 3: expand=FALSE, fill=TRUE - Diagonal [2,2]
    boton_noexpand_fill = gtk_button_new_with_label(
        "[Fila 2, Col 2]\n\n"
        "expand=FALSE\nfill=TRUE\n\n"
        "Tamaño mínimo\npero lo LLENO"
    );
    gtk_grid_attach(GTK_GRID(grid), boton_noexpand_fill, 2, 2, 1, 1);
    gtk_widget_set_hexpand(boton_noexpand_fill, FALSE);  // NO se expande
    gtk_widget_set_vexpand(boton_noexpand_fill, FALSE);
    gtk_widget_set_halign(boton_noexpand_fill, GTK_ALIGN_FILL);  // Pero llena
    gtk_widget_set_valign(boton_noexpand_fill, GTK_ALIGN_FILL);
    g_signal_connect(boton_noexpand_fill, "clicked", G_CALLBACK(on_boton_clicked),
        "BOTÓN [2,2]: EXPAND=FALSE, FILL=TRUE → NO compito, pero lleno mi espacio");

    // BOTÓN 4: expand=FALSE, fill=FALSE - Diagonal [3,3]
    boton_noexpand_nofill = gtk_button_new_with_label(
        "[Fila 3, Col 3]\n\n"
        "expand=FALSE\nfill=FALSE\n\n"
        "Tamaño mínimo\ny me CENTRO"
    );
    gtk_grid_attach(GTK_GRID(grid), boton_noexpand_nofill, 3, 3, 1, 1);
    gtk_widget_set_hexpand(boton_noexpand_nofill, FALSE);  // NO se expande
    gtk_widget_set_vexpand(boton_noexpand_nofill, FALSE);
    gtk_widget_set_halign(boton_noexpand_nofill, GTK_ALIGN_CENTER);  // Y se centra
    gtk_widget_set_valign(boton_noexpand_nofill, GTK_ALIGN_CENTER);
    g_signal_connect(boton_noexpand_nofill, "clicked", G_CALLBACK(on_boton_clicked),
        "BOTÓN [3,3]: EXPAND=FALSE, FILL=FALSE → NO compito y mantengo tamaño mínimo");

    // Mostrar información en consola
    g_print("\n╔════════════════════════════════════════════════════════════╗\n");
    g_print("║   Comparativa Visual: Expand vs Fill en GTK Grid         ║\n");
    g_print("╚════════════════════════════════════════════════════════════╝\n\n");
    g_print("INSTRUCCIONES:\n");
    g_print("  1. Redimensiona la ventana VERTICALMENTE para ver expand en acción\n");
    g_print("  2. Redimensiona la ventana HORIZONTALMENTE para ver fill en acción\n");
    g_print("  3. Haz click en cada botón para ver su configuración\n\n");
    g_print("EXPLICACIÓN:\n");
    g_print("  • expand: ¿Puede el widget TOMAR espacio extra disponible?\n");
    g_print("            - TRUE:  Competirá por espacio extra (crece con la ventana)\n");
    g_print("            - FALSE: Mantiene su tamaño natural (no crece)\n");
    g_print("  • fill:   ¿El widget LLENA el espacio que le tocó o se centra?\n");
    g_print("            - TRUE:  Se estira para llenar todo el espacio\n");
    g_print("            - FALSE: Mantiene su tamaño y se centra\n\n");
    g_print("NOTA IMPORTANTE:\n");
    g_print("  El grid NO es homogéneo, por eso las filas/columnas pueden tener\n");
    g_print("  tamaños diferentes según el expand de sus widgets.\n\n");
    g_print("ESQUEMA DEL GRID 4×2 (comparación LADO A LADO para máxima claridad):\n");
    g_print("  \n");
    g_print("              Col 0          Col 1    Col 2         Col 3\n");
    g_print("           ┌────────────┬──────────┬──────────┬────────────┐\n");
    g_print("  Fila 0   │ expand=TRUE│          │          │expand=TRUE │\n");
    g_print("(GRANDE)   │ fill=TRUE  │ (vacío)  │ (vacío)  │fill=FALSE  │\n");
    g_print("           │ ┌────────┐ │          │          │  ┌──────┐  │\n");
    g_print("           │ │ LLENA  │ │          │          │  │CENTRA│  │\n");
    g_print("           │ │  TODO  │ │          │          │  │ DO   │  │\n");
    g_print("           │ └────────┘ │          │          │  └──────┘  │\n");
    g_print("           ├────────────┼──────────┼──────────┼────────────┤\n");
    g_print("  Fila 1   │expand=FALSE│          │          │expand=FALSE│\n");
    g_print("(PEQUEÑA)  │ fill=TRUE  │ (vacío)  │ (vacío)  │fill=FALSE  │\n");
    g_print("           │ ┌────────┐ │          │          │  ┌──────┐  │\n");
    g_print("           │ │ LLENA  │ │          │          │  │CENTRA│  │\n");
    g_print("           │ └────────┘ │          │          │  └──────┘  │\n");
    g_print("           └────────────┴──────────┴──────────┴────────────┘\n");
    g_print("  \n");
    g_print("╔═══════════════════════════════════════════════════════════╗\n");
    g_print("║  CLAVE: Compara en HORIZONTAL (izquierda vs derecha)     ║\n");
    g_print("╚═══════════════════════════════════════════════════════════╝\n");
    g_print("\n");
    g_print("🔍 OBSERVACIONES CLAVE:\n\n");
    g_print("  1️⃣  FILA 0 (expand=TRUE): AMBAS celdas son GRANDES\n");
    g_print("     → Izquierda (fill=TRUE):  Botón GRANDE que llena toda la celda\n");
    g_print("     → Derecha (fill=FALSE):   Botón PEQUEÑO centrado en celda grande\n");
    g_print("     ✨ DIFERENCIA OBVIA: Mira el TAMAÑO del botón\n\n");
    g_print("  2️⃣  FILA 1 (expand=FALSE): AMBAS celdas son PEQUEÑAS\n");
    g_print("     → Izquierda (fill=TRUE):  Botón llena su pequeña celda\n");
    g_print("     → Derecha (fill=FALSE):   Botón aún más pequeño, centrado\n");
    g_print("     ✨ DIFERENCIA SUTIL pero visible\n\n");
    g_print("  3️⃣  Columnas 1 y 2 VACÍAS = Separación visual clara\n\n");
    g_print("🎯 EXPERIMENTO:\n");
    g_print("   • Agranda la ventana VERTICALMENTE → Fila 0 crece, Fila 1 NO\n");
    g_print("   • Agranda HORIZONTALMENTE → Col 0 y 3 crecen, Cols 1-2 NO\n");
    g_print("   • Fondo GRIS muestra los límites reales de cada celda\n\n");

    // Conectar señal de cierre
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar todos los widgets
    gtk_widget_show_all(window);

    // Bucle principal
    gtk_main();

    return 0;
}