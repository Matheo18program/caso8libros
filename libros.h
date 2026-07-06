#ifndef LIBROS_H
#define LIBROS_H

#define MAX_LIBROS 100      // Máximo número de libros
#define MAX_TEXTO 100       // Longitud máxima para textos
#define MAX_CODIGO 16       // Longitud para código (1-15 caracteres)
#define MAX_ISBN 20         // Longitud para ISBN

// Estructura de datos de un libro
typedef struct {
    char codigo[MAX_CODIGO];
    char titulo[MAX_TEXTO];
    char clasificacion[MAX_TEXTO];
    char autor[MAX_TEXTO];
    char isbn[MAX_ISBN];
    int stock;
} Libro;

// Prototipos de funciones de gestión
int existeCodigo(Libro *lista, int total, char *cod);
int existeIsbn(Libro *lista, int total, char *isbn);
int validarCodigo(char *cod);
int registrarLibro(Libro *lista, int *total);
void listarLibros(Libro *lista, int total);
void buscarLibro(Libro *lista, int total);
int actualizarLibro(Libro *lista, int total);
int eliminarLibro(Libro *lista, int *total);
void consultarYModificarStock(Libro *lista, int total);
void reportesStock(Libro *lista, int total);

#endif
    