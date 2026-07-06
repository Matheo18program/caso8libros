#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "libros.h"

// Verifica si el código ya existe
int existeCodigo(Libro *lista, int total, char *cod) {
    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].codigo, cod) == 0)
            return 1;
    }
    return 0;
}

// Verifica si el ISBN ya existe
int existeIsbn(Libro *lista, int total, char *isbn) {
    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].isbn, isbn) == 0)
            return 1;
    }
    return 0;
}

// Valida que el código sea correcto
int validarCodigo(char *cod) {
    int len = strlen(cod);
    if (len < 1 || len >= MAX_CODIGO) return 0;
    for (int i = 0; cod[i] != '\0'; i++) {
        if (isspace(cod[i])) return 0; // Sin espacios
    }
    return 1;
}

// Registrar nuevo libro
int registrarLibro(Libro *lista, int *total) {
    if (*total >= MAX_LIBROS) {
        printf(" Almacenamiento lleno.\n");
        return 0;
    }

    Libro nuevo;
    char temp[MAX_TEXTO];

    // Código
    do {
        printf("Código del libro: ");
        fgets(temp, MAX_TEXTO, stdin);
        temp[strcspn(temp, "\n")] = '\0';
        if (!validarCodigo(temp) || existeCodigo(lista, *total, temp))
            printf(" Código inválido, repetido o con espacios.\n");
    } while (!validarCodigo(temp) || existeCodigo(lista, *total, temp));
    strcpy(nuevo.codigo, temp);

    // Título
    do {
        printf("Título: ");
        fgets(nuevo.titulo, MAX_TEXTO, stdin);
        nuevo.titulo[strcspn(nuevo.titulo, "\n")] = '\0';
        if (strlen(nuevo.titulo) == 0)
            printf(" El título no puede estar vacío.\n");
    } while (strlen(nuevo.titulo) == 0);

    // Clasificación
    printf("Clasificación: ");
    fgets(nuevo.clasificacion, MAX_TEXTO, stdin);
    nuevo.clasificacion[strcspn(nuevo.clasificacion, "\n")] = '\0';

    // Autor
    do {
        printf("Autor principal: ");
        fgets(nuevo.autor, MAX_TEXTO, stdin);
        nuevo.autor[strcspn(nuevo.autor, "\n")] = '\0';
        if (strlen(nuevo.autor) == 0)
            printf(" El autor no puede estar vacío.\n");
    } while (strlen(nuevo.autor) == 0);

    // ISBN
    do {
        printf("ISBN: ");
        fgets(temp, MAX_TEXTO, stdin);
        temp[strcspn(temp, "\n")] = '\0';
        if (strlen(temp) == 0 || existeIsbn(lista, *total, temp))
            printf(" ISBN vacío o ya registrado.\n");
    } while (strlen(temp) == 0 || existeIsbn(lista, *total, temp));
    strcpy(nuevo.isbn, temp);

    // Stock
    do {
        printf("Cantidad en stock: ");
        if (scanf("%d", &nuevo.stock) != 1) {
            while (getchar() != '\n');
            nuevo.stock = -1;
        }
        while (getchar() != '\n');
        if (nuevo.stock < 0)
            printf(" El stock no puede ser negativo.\n");
    } while (nuevo.stock < 0);

    lista[*total] = nuevo;
    (*total)++;
    printf("✅ Libro registrado con éxito.\n");
    return 1;
}

// Listar todos los libros
void listarLibros(Libro *lista, int total) {
    if (total == 0) {
        printf("ℹ️ No hay libros registrados.\n");
        return;
    }
    printf("\n%-10s | %-25s | %-15s | %-20s | %-15s | %s\n",
           "CÓDIGO", "TÍTULO", "CLASIFICACIÓN", "AUTOR", "ISBN", "STOCK");
    printf("----------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%-10s | %-25s | %-15s | %-20s | %-15s | %d\n",
               lista[i].codigo, lista[i].titulo, lista[i].clasificacion,
               lista[i].autor, lista[i].isbn, lista[i].stock);
    }
}

// Buscar libro por distintos criterios
void buscarLibro(Libro *lista, int total) {
    if (total == 0) {
        printf(" No hay libros para buscar.\n");
        return;
    }
    int op;
    char criterio[MAX_TEXTO];
    printf("\nBuscar por:\n");
    printf("1. Código\n2. Título\n3. Clasificación\n4. Autor\n5. ISBN\nOpción: ");
    if (scanf("%d", &op) != 1) { while(getchar()!='\n'); return; }
    getchar();

    printf("Ingrese término de búsqueda: ");
    fgets(criterio, MAX_TEXTO, stdin);
    criterio[strcspn(criterio, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < total; i++) {
        int coincide = 0;
        switch(op) {
            case 1: coincide = (strcmp(lista[i].codigo, criterio) == 0); break;
            case 2: coincide = (strstr(lista[i].titulo, criterio) != NULL); break;
            case 3: coincide = (strstr(lista[i].clasificacion, criterio) != NULL); break;
            case 4: coincide = (strstr(lista[i].autor, criterio) != NULL); break;
            case 5: coincide = (strcmp(lista[i].isbn, criterio) == 0); break;
            default: printf(" Opción inválida.\n"); return;
        }
        if (coincide) {
            if (!encontrado) {
                printf("\n--- Resultados ---\n");
                printf("%-10s | %-25s | %-15s | %-20s | %-15s | %s\n",
                       "CÓDIGO", "TÍTULO", "CLASIFICACIÓN", "AUTOR", "ISBN", "STOCK");
            }
            printf("%-10s | %-25s | %-15s | %-20s | %-15s | %d\n",
                   lista[i].codigo, lista[i].titulo, lista[i].clasificacion,
                   lista[i].autor, lista[i].isbn, lista[i].stock);
            encontrado = 1;
        }
    }
    if (!encontrado) printf(" No se encontraron coincidencias.\n");
}

// Actualizar datos de un libro
int actualizarLibro(Libro *lista, int total) {
    char cod[MAX_CODIGO];
    printf("Ingrese el código del libro a actualizar: ");
    fgets(cod, MAX_CODIGO, stdin);
    cod[strcspn(cod, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].codigo, cod) == 0) { pos = i; break; }
    }
    if (pos == -1) { printf(" Libro no encontrado.\n"); return 0; }

    printf("Actualizando: %s - %s\n", lista[pos].codigo, lista[pos].titulo);
    char temp[MAX_TEXTO];

    // Título
    printf("Nuevo título (vacío = no cambiar): ");
    fgets(temp, MAX_TEXTO, stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if (strlen(temp) > 0) strcpy(lista[pos].titulo, temp);

    // Clasificación
    printf("Nueva clasificación (vacío = no cambiar): ");
    fgets(temp, MAX_TEXTO, stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if (strlen(temp) > 0) strcpy(lista[pos].clasificacion, temp);

    // Autor
    printf("Nuevo autor (vacío = no cambiar): ");
    fgets(temp, MAX_TEXTO, stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if (strlen(temp) > 0) strcpy(lista[pos].autor, temp);

    // ISBN
    do {
        printf("Nuevo ISBN (vacío = no cambiar): ");
        fgets(temp, MAX_TEXTO, stdin);
        temp[strcspn(temp, "\n")] = '\0';
        if (strlen(temp) > 0) {
            if (existeIsbn(lista, total, temp) && strcmp(temp, lista[pos].isbn) != 0)
                printf("❌ ISBN ya existe.\n");
            else break;
        } else break;
    } while (1);
    if (strlen(temp) > 0) strcpy(lista[pos].isbn, temp);

    // Stock
    int nuevoStock;
    printf("Nuevo stock (-1 = no cambiar): ");
    if (scanf("%d", &nuevoStock) == 1 && nuevoStock >= 0)
        lista[pos].stock = nuevoStock;
    while (getchar() != '\n');

    printf("✅ Libro actualizado.\n");
    return 1;
}

// Eliminar libro
int eliminarLibro(Libro *lista, int *total) {
    char cod[MAX_CODIGO];
    printf("Ingrese código del libro a eliminar: ");
    fgets(cod, MAX_CODIGO, stdin);
    cod[strcspn(cod, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < *total; i++) {
        if (strcmp(lista[i].codigo, cod) == 0) { pos = i; break; }
    }
    if (pos == -1) { printf("❌ Libro no encontrado.\n"); return 0; }

    char conf;
    printf("¿Eliminar \"%s\"? (S/N): ", lista[pos].titulo);
    scanf(" %c", &conf);
    while (getchar() != '\n');
    if (toupper(conf) != 'S') { printf("Cancelado.\n"); return 0; }

    for (int i = pos; i < *total - 1; i++)
        lista[i] = lista[i + 1];
    (*total)--;
    printf(" Libro eliminado.\n");
    return 1;
}

// Consultar y modificar stock
void consultarYModificarStock(Libro *lista, int total) {
    if (total == 0) { printf("No hay libros.\n"); return; }
    char cod[MAX_CODIGO];
    printf("Ingrese código: ");
    fgets(cod, MAX_CODIGO, stdin);
    cod[strcspn(cod, "\n")] = '\0';

    int pos = -1;
    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].codigo, cod) == 0) { pos = i; break; }
    }
    if (pos == -1) { printf(" Libro no encontrado.\n"); return; }

    printf("Libro: %s | Stock actual: %d\n", lista[pos].titulo, lista[pos].stock);
    int op, cant;
    printf("1. Aumentar\n2. Disminuir\nOpción: ");
    if (scanf("%d", &op) != 1) { while(getchar()!='\n'); return; }
    printf("Cantidad: ");
    if (scanf("%d", &cant) != 1 || cant <= 0) { printf("Cantidad inválida.\n"); while(getchar()!='\n'); return; }
    while (getchar() != '\n');

    if (op == 1) lista[pos].stock += cant;
    else if (op == 2) {
        if (lista[pos].stock >= cant) lista[pos].stock -= cant;
        else { printf(" No hay suficiente stock.\n"); return; }
    } else { printf(" Opción inválida.\n"); return; }

    printf("✅ Nuevo stock: %d\n", lista[pos].stock);
}

// Reportes de stock
void reportesStock(Libro *lista, int total) {
    if (total == 0) { printf(" No hay libros.\n"); return; }
    int op, limite;
    printf("\nReportes:\n1. Libros agotados\n2. Stock bajo\nOpción: ");
    if (scanf("%d", &op) != 1) { while(getchar()!='\n'); return; }
    if (op == 2) {
        printf("Ingrese límite de stock: ");
        if (scanf("%d", &limite) != 1 || limite < 0) { printf("❌ Valor inválido.\n"); while(getchar()!='\n'); return; }
    }
    while (getchar() != '\n');

    int hay = 0;
    for (int i = 0; i < total; i++) {
        if ((op == 1 && lista[i].stock == 0) || (op == 2 && lista[i].stock < limite)) {
            printf("%s - %s | Stock: %d\n", lista[i].codigo, lista[i].titulo, lista[i].stock);
            hay = 1;
        }
    }
    if (!hay) printf("No hay coincidencias.\n");
}
