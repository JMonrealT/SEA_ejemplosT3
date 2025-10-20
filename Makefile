# Makefile para los ejemplos de GTK
# Uso:
#   make          - Compila todos los ejemplos
#   make ejemplo1 - Compila solo el ejemplo 1
#   make clean    - Elimina ejecutables

# Configuración
CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall
LIBS = `pkg-config --libs gtk+-3.0` -lm
# Nota: no funciona con $( ), solo con $(shell ), 
# porque sin shell no ejecuta el comando pkg-config.
# Con $(shell ) funciona pero hace eco de toda la sustitución de comandos.

# Lista de ejemplos
EJEMPLOS = ejemplo1 ejemplo2 ejemplo2b ejemplo3 ejemplo4 ejemplo4b ejemplo5 ejemplo6 ejemplo7 ejemplo8 ejemplo9 ejemplo10

# Regla por defecto
all: $(EJEMPLOS)

# Reglas para cada ejemplo
ejemplo1: ejemplo1_ventana_basica.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

ejemplo2: ejemplo2_ventana_con_titulo.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

ejemplo2b: ejemplo2b_ventana_con_css.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

ejemplo3: ejemplo3_boton_simple.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

ejemplo4: ejemplo4_etiqueta_y_boton.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

ejemplo4b: ejemplo4b_grid_expand_fill.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

ejemplo5: ejemplo5_boton_con_callback.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

ejemplo6: ejemplo6_entrada_de_texto.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

ejemplo7: ejemplo7_multiples_widgets.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

ejemplo8: ejemplo8_menu_simple.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

ejemplo9: ejemplo9_dialogo_archivo.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

ejemplo10: ejemplo10_calculadora_simple.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

# Limpiar ejecutables
clean:
	rm -f $(EJEMPLOS)

# Evitar conflictos with files del mismo nombre
.PHONY: all clean