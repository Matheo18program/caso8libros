#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "libros.h"

// Prototipos para operaciones con archivos
int guardarLibrosCSV(Libro *lista, int total, const char *ruta);
int cargarLibrosCSV(Libro *lista, int *total, const char *ruta);

#endif
