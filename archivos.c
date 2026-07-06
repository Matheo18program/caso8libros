#include <stdio.h>
#include "archivos.h"

// Guardar todos los libros en formato CSV
int guardarLibrosCSV(Libro *lista, int total, const char *ruta) {
    FILE *archivo = fopen(ruta, "w");
    if (!archivo) {
        printf("❌ No se pudo crear/abrir el archivo.\n");
        return 0;
    }
    for (int i = 0; i < total; i++) {
        fprintf(archivo, "%s,%s,%s,%s,%s,%d\n",
                lista[i].codigo,
                lista[i].titulo,
                lista[i].clasificacion,
                lista[i].autor,
                lista[i].isbn,
                lista[i].stock);
    }
    fclose(archivo);
    printf("✅ Datos guardados en %s\n", ruta);
    return 1;
}

// Cargar libros desde archivo CSV
int cargarLibrosCSV(Libro *lista, int *total, const char *ruta) {
    FILE *archivo = fopen(ruta, "r");
    if (!archivo) {
        printf("ℹ️ Archivo no encontrado. Se iniciará vacío.\n");
        *total = 0;
        return 0;
    }
    *total = 0;
    while (*total < MAX_LIBROS &&
           fscanf(archivo, "%[^,],%[^,],%[^,],%[^,],%[^,],%d\n",
                  lista[*total].codigo,
                  lista[*total].titulo,
                  lista[*total].clasificacion,
                  lista[*total].autor,
                  lista[*total].isbn,
                  &lista[*total].stock) == 6) {
        (*total)++;
    }
    fclose(archivo);
    printf("✅ Se cargaron %d libros desde %s\n", *total, ruta);
    return 1;
}
