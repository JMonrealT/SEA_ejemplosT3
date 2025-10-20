# Batería de Ejemplos Básicos de GTK

Esta colección contiene ejemplos progresivos para aprender a crear interfaces gráficas sencillas con GTK en C. Cada ejemplo introduce nuevos conceptos mientras refuerza los anteriores, proporcionando una base sólida para el desarrollo de aplicaciones con GTK.

## Estructura y Progresión de los Ejemplos

### Nivel Básico (Conceptos Fundamentales)

**1. ejemplo1_ventana_basica.c** - Ventana vacía mínima

- **Conceptos:** Inicialización GTK, creación de ventanas, bucle principal
- **Jerarquía:** `GtkWindow` (ventana raíz)
- **Aprenderás:** La estructura básica de una aplicación GTK
- **Funciones clave:** `gtk_init()`, `gtk_window_new()`, `gtk_main()`

```text
GtkWindow
(ventana vacía - punto de partida)
```

**Ciclo básico de vida de GTK:** Toda aplicación GTK sigue el mismo patrón: `gtk_init()` → crear widgets → `gtk_widget_show_all()` → `gtk_main()`. Este es el esqueleto fundamental.

---

**2. ejemplo2_ventana_con_titulo.c** - Ventana con título y propiedades

- **Conceptos:** Propiedades de ventanas, posicionamiento, tamaños
- **Jerarquía:** `GtkWindow` (con propiedades personalizadas)
- **Aprenderás:** Personalización básica de comportamiento de ventanas
- **Funciones clave:** `gtk_window_set_title()`, `gtk_window_set_default_size()`, `gtk_window_set_position()`

```text
GtkWindow
(misma estructura básica, pero con propiedades)
```

**Propiedades de ventanas:** GTK permite personalizar título, tamaño inicial y posición de las ventanas. Estas propiedades básicas no requieren CSS y son fundamentales para cualquier aplicación.

---

**2b. ejemplo2b_ventana_con_css.c** - Ventana con estilo CSS básico

- **Conceptos:** CSS styling, proveedores de estilo, personalización visual
- **Jerarquía:** `GtkWindow` + `GtkCssProvider` (estilo visual)
- **Aprenderás:** Cómo aplicar estilos CSS sencillos a widgets GTK
- **Funciones clave:** `gtk_css_provider_new()`, `gtk_css_provider_load_from_data()`

```text
GtkWindow + CSS
(misma estructura, pero con estilo visual aplicado)
```

**Styling básico con CSS:** GTK soporta CSS para personalización visual. Un `GtkCssProvider` carga el CSS y se aplica a la pantalla. Este ejemplo usa solo colores y fuentes - lo esencial para empezar con estilos.

---

**3. ejemplo3_boton_simple.c** - Ventana con un botón básico

- **Conceptos:** Widgets hijo, contenedores, jerarquía de widgets
- **Jerarquía:** `GtkWindow` → `GtkButton` (relación padre-hijo)
- **Aprenderás:** Cómo añadir widgets a ventanas y mostrarlos
- **Funciones clave:** `gtk_button_new_with_label()`, `gtk_container_add()`

```text
GtkWindow
└── GtkButton
    (primer widget hijo)
```

**Principio fundamental:** En GTK, los widgets forman una jerarquía tipo árbol. Cada widget puede tener un padre y múltiples hijos. `gtk_container_add()` establece esta relación padre-hijo.

---

### Nivel Intermedio (Interactividad y Layout)

**4. ejemplo4_etiqueta_y_boton.c** - Combinación de etiqueta y botón

- **Conceptos:** Múltiples widgets, layout managers, actualización dinámica
- **Jerarquía:** `GtkWindow` → `GtkBox` → [`GtkLabel`, `GtkButton`]
- **Aprenderás:** Cómo organizar varios widgets y hacer que interactúen
- **Funciones clave:** `GtkBox`, `gtk_label_set_text()`

```text
GtkWindow
└── GtkBox (contenedor lineal)
    ├── GtkLabel
    └── GtkButton
```

**Layout Managers - GtkBox:** Cuando necesitas múltiples widgets, necesitas un contenedor. `GtkBox` organiza widgets en línea (horizontal o vertical). Es el layout manager más simple y común para formularios básicos.

**Sistema de Señales:** Los widgets comunican eventos mediante señales. `g_signal_connect()` conecta señales (como "clicked") con funciones callback que definen qué hacer cuando ocurre el evento.

---

**4b. ejemplo4b_grid_expand_fill.c** - Layout en cuadrícula con variables configurables

- **Conceptos:** Layout managers avanzados, propiedades expand/fill, experimentación didáctica
- **Jerarquía:** `GtkWindow` → `GtkGrid` → [`GtkLabel`, `GtkButton`] (en cuadrícula 2×2)
- **Aprenderás:** Cómo controlar el comportamiento de expansión y alineación de widgets
- **Funciones clave:** `GtkGrid`, `gtk_widget_set_hexpand()`, `gtk_widget_set_halign()`

```text
GtkWindow
└── GtkGrid (2×2 homogéneo)
    ├── GtkLabel (0,0)
    ├── GtkLabel (1,0)
    ├── GtkButton (0,1)
    └── GtkButton (1,1)
```

**Layout Managers - GtkGrid:** Para layouts más complejos que líneas simples, `GtkGrid` permite organizar widgets en filas y columnas. Las propiedades `expand` y `fill` controlan cómo los widgets utilizan el espacio disponible.

**Variables didácticas:** Este ejemplo usa variables `expand_widgets` y `fill_widgets` que puedes modificar para experimentar con diferentes comportamientos de layout y entender visualmente las diferencias.

---

**5. ejemplo5_boton_con_callback.c** - Botón avanzado con funcionalidad especial

- **Conceptos:** Callbacks, señales, programación dirigida por eventos, redirección de salida
- **Jerarquía:** `GtkWindow` → `GtkButton` (con terminal separado)
- **Aprenderás:** Diferencia entre `printf()` y `g_print()`, callbacks personalizados
- **Funciones clave:** `g_signal_connect()`, `g_set_print_handler()`, named pipes

```text
GtkWindow
└── GtkButton
    + Terminal separado (named pipe)
```

**Programación dirigida por eventos:** GTK es reactivo - tu código responde a eventos del usuario. Los callbacks son funciones que se ejecutan cuando ocurre una señal específica.

**Redirección de salida:** GTK permite redirigir `g_print()` a diferentes destinos (archivos, terminales, etc.). Este ejemplo demuestra cómo separar la salida de debug de la interfaz principal.

---

**6. ejemplo6_entrada_de_texto.c** - Campo de entrada de texto con validación

- **Conceptos:** Entrada de usuario, validación de texto, múltiples callbacks, texto placeholder
- **Jerarquía:** `GtkWindow` → `GtkBox` → [`GtkEntry`, `GtkButton` (×2), `GtkLabel`]
- **Aprenderás:** Cómo capturar, validar y procesar datos del usuario con múltiples acciones
- **Funciones clave:** `gtk_entry_new()`, `gtk_entry_get_text()`, `gtk_entry_set_placeholder_text()`

```text
GtkWindow
└── GtkBox (vertical)
    ├── GtkEntry (entrada con placeholder)
    ├── GtkButton ("Mostrar Texto")
    ├── GtkButton ("Limpiar")
    └── GtkLabel (feedback al usuario)
```

**Entrada de usuario avanzada:** Los widgets de entrada (`GtkEntry`) capturan texto del usuario. Este ejemplo muestra validación básica (texto vacío), múltiples acciones (mostrar/limpiar), y cómo proporcionar feedback inmediato al usuario.

**Eventos múltiples:** El entry responde tanto al botón "Mostrar Texto" como a la tecla Enter (`activate` signal), demostrando cómo un mismo callback puede conectarse a diferentes eventos para mejorar la experiencia de usuario.

---

**7. ejemplo7_multiples_widgets.c** - Varios widgets en contenedor vertical

- **Conceptos:** Formularios complejos, diferentes tipos de widgets, feedback visual
- **Jerarquía:** `GtkWindow` → `GtkBox` → [`GtkLabel`, `GtkEntry`, `GtkCheckButton`, `GtkProgressBar`, `GtkButton`]
- **Aprenderás:** Cómo crear interfaces más sofisticadas y completas
- **Funciones clave:** `GtkCheckButton`, `GtkProgressBar`, layout avanzado

```text
GtkWindow
└── GtkBox (vertical)
    ├── GtkLabel
    ├── GtkEntry
    ├── GtkCheckButton
    ├── GtkProgressBar
    └── GtkButton
```

**Formularios complejos:** Combinando múltiples tipos de widgets (texto, checkboxes, barras de progreso) puedes crear interfaces completas. Cada tipo de widget tiene su propia API y comportamiento.

---

### Nivel Avanzado (Aplicaciones Completas)

**8. ejemplo8_menu_simple.c** - Ventana con barra de menú

- **Conceptos:** Sistema de menús, diálogos modales, organización jerárquica
- **Jerarquía:** `GtkWindow` → `GtkBox` → [`GtkMenuBar` → múltiples `GtkMenu` → múltiples `GtkMenuItem`]
- **Aprenderás:** Elementos de aplicaciones profesionales, estructura de menús complejos
- **Funciones clave:** `GtkMenuBar`, `GtkMessageDialog`, `gtk_menu_item_set_submenu()`

```text
GtkWindow
└── GtkBox (vertical)
    ├── GtkMenuBar (barra horizontal)
    │   ├── GtkMenuItem "Archivo"
    │   │   └── GtkMenu (desplegable)
    │   │       ├── GtkMenuItem "Nuevo"
    │   │       ├── GtkMenuItem "Abrir"
    │   │       ├── GtkMenuItem "Guardar"
    │   │       ├── GtkSeparatorMenuItem ----
    │   │       └── GtkMenuItem "Salir"
    │   └── GtkMenuItem "Ayuda"
    │       └── GtkMenu (desplegable)
    │           └── GtkMenuItem "Acerca de..."
    └── GtkLabel (área de contenido/estado)
```

**Sistemas de menús:** Los menús añaden profesionalismo a las aplicaciones. La jerarquía completa es `MenuBar` (barra) → `MenuItem` (elementos principales) → `Menu` (contenedores desplegables) → `MenuItem` (acciones específicas). Los separadores organizan visualmente las opciones.

**Diálogos modales:** `GtkMessageDialog` muestra ventanas temporales que requieren respuesta del usuario antes de continuar. Son esenciales para confirmaciones y alertas.

---

**9. ejemplo9_dialogo_archivo.c** - Editor con diálogos del sistema operativo

- **Conceptos:** Diálogos modales complejos, manipulación de archivos reales, editor de texto funcional
- **Jerarquía:** `GtkWindow` → `GtkBox` → [`GtkButton` (×2), `GtkLabel`, `GtkScrolledWindow` → `GtkTextView`]
- **Aprenderás:** Interacción real con el sistema de archivos, diálogos nativos del OS
- **Funciones clave:** `GtkFileChooserDialog`, `GtkTextView`, `GtkTextBuffer`, operaciones de archivo

```text
GtkWindow
└── GtkBox (vertical)
    ├── GtkBox (horizontal - botones)
    │   ├── GtkButton "Abrir Archivo"  → GtkFileChooserDialog
    │   └── GtkButton "Guardar Archivo" → GtkFileChooserDialog
    ├── GtkLabel (muestra archivo actual)
    └── GtkScrolledWindow
        └── GtkTextView (editor multilínea)
```

**Evolución del Ejemplo 8:** Mientras el ejemplo 8 solo actualiza texto en pantalla cuando haces click en menús, **el ejemplo 9 abre diálogos reales del sistema operativo** que te permiten navegar carpetas y seleccionar/guardar archivos verdaderos.

**Editor funcional:** No es solo mostrar texto - puedes **abrir archivos reales** (documentos, código fuente, etc.), **editarlos** en el `GtkTextView`, y **guardarlos** de vuelta al disco. Es un editor de texto básico pero completamente funcional.

**Diálogos nativos:** `GtkFileChooserDialog` usa la interfaz nativa del sistema operativo (igual que Notepad, gedit, etc.), proporcionando una experiencia familiar al usuario.

---

**10. ejemplo10_calculadora_simple.c** - Aplicación completa con estado persistente

- **Conceptos:** Estado complejo, lógica matemática, layout profesional, manejo de decimales
- **Jerarquía:** `GtkWindow` → `GtkBox` → [`GtkFrame` → `GtkLabel`, `GtkGrid` → 16 `GtkButton`]
- **Aprenderás:** Aplicación 100% funcional con múltiples operaciones y validación de errores
- **Funciones clave:** `GtkGrid`, variables globales de estado, `setlocale()`, callbacks complejos

```text
GtkWindow (calculadora 280×350px, no redimensionable)
└── GtkBox (vertical)
    ├── GtkFrame (marco del display)
    │   └── GtkLabel "0" (display numérico, alineado derecha)
    └── GtkGrid (4 columnas × 5 filas)
        │
        │  Col 0   Col 1   Col 2   Col 3
        │ ┌─────┬─────┬─────┬─────┐
        │ │  C  │  /  │  *  │  -  │ ← Fila 0
        │ ├─────┼─────┼─────┼─────┤
        │ │  7  │  8  │  9  │     │ ← Fila 1
        │ ├─────┼─────┼─────┤  +  │   (+) ocupa 2 filas
        │ │  4  │  5  │  6  │     │ ← Fila 2
        │ ├─────┼─────┼─────┼─────┤
        │ │  1  │  2  │  3  │     │ ← Fila 3
        │ ├─────┴─────┼─────┤  =  │   (=) ocupa 2 filas
        │ │     0     │  .  │     │ ← Fila 4, (0) ocupa 2 cols
        │ └───────────┴─────┴─────┘
```

**Calculadora visual:**

```text
┌─────────────────────────────────┐
│            "0"                  │ ← Display
├───────┬───────┬───────┬─────────┤
│   C   │   /   │   *   │    -    │
├───────┼───────┼───────┼─────────┤
│   7   │   8   │   9   │         │
├───────┼───────┼───────┤    +    │
│   4   │   5   │   6   │         │
├───────┼───────┼───────┼─────────┤
│   1   │   2   │   3   │         │
├───────────────┼───────┤    =    │
│       0       │   .   │         │
└───────────────┴───────┴─────────┘
```

**Aplicación profesional completa:** A diferencia de ejemplos anteriores que demuestran widgets individuales, **esta es una calculadora real y funcional** que mantiene estado entre operaciones, maneja decimales correctamente, y previene errores (división por cero).

**Estado persistente avanzado:** Usa 4 variables globales (`numero_actual`, `numero_anterior`, `operacion`, `nuevo_numero`) que coordinan para recordar números y operaciones pendientes mientras el usuario navega por múltiples cálculos.

**Layout profesional:** `GtkGrid` con botones de tamaño fijo (60×50px), algunos ocupando múltiples celdas ("+" y "=" ocupan 2 filas, "0" ocupa 2 columnas), creando una interfaz similar a calculadoras reales.

**Layout Managers - GtkGrid:** Para layouts complejos como calculadoras, `GtkGrid` permite posicionar widgets en filas y columnas específicas. Cada botón ocupa una celda definida con `gtk_grid_attach()`.

**Estado de aplicación:** Aplicaciones reales mantienen estado (números, operaciones, resultados). Variables globales y callbacks coordinan la lógica de negocio con la interfaz visual.

**Manejo de locales:** `setlocale(LC_NUMERIC, "C")` fuerza el uso del punto decimal en lugar de coma, crucial para aplicaciones numéricas en sistemas internacionales.

---

## Compilación y Ejecución

### Usando Make (Recomendado)

```bash
make           # Compila todos los ejemplos
make ejemplo1  # Compila solo el ejemplo 1
make clean     # Elimina ejecutables
```

### Compilación Manual

```bash
gcc `pkg-config --cflags gtk+-3.0` ejemplo1_ventana_basica.c -o ejemplo1 `pkg-config --libs gtk+-3.0`
```

### Dependencias

```bash
# Ubuntu/Debian
sudo apt-get install libgtk-3-dev

# Fedora
sudo dnf install gtk3-devel

# Arch
sudo pacman -S gtk3
```

## Siguientes Pasos

1. **Experimenta:** Modifica los ejemplos para entender mejor los conceptos
2. **Combina:** Usa elementos de diferentes ejemplos en tus propios proyectos  
3. **Explora:** Investiga widgets adicionales como `GtkTreeView`, `GtkNotebook`, etc.
4. **Construye:** Crea tu propia aplicación combinando los conceptos aprendidos
