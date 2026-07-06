#include <stdio.h>
#include "libros.h"
#include "archivos.h"

int main() {
    Libro listaLibros[MAX_LIBROS];
    int totalLibros = 0;
    int opcion;
    const char RUTA_ARCHIVO[] = "libros.csv";

    // Cargar datos al iniciar
    cargarLibrosCSV(listaLibros, &totalLibros, RUTA_ARCHIVO);

    do {
        printf("\n========== GESTIÓN DE LIBROS ==========\n");
        printf("1. Registrar libro\n");
        printf("2. Listar libros\n");
        printf("3. Buscar libro\n");
        printf("4. Actualizar libro\n");
        printf("5. Eliminar libro\n");
        printf("6. Consultar / Modificar stock\n");
        printf("7. Reportes de stock\n");
        printf("8. Guardar cambios\n");
        printf("9. Salir\n");
        printf("========================================\n");
        printf("Ingrese opción: ");

        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            opcion = -1;
        }
        while (getchar() != '\n');

        switch(opcion) {
            case 1: registrarLibro(listaLibros, &totalLibros); break;
            case 2: listarLibros(listaLibros, totalLibros); break;
            case 3: buscarLibro(listaLibros, totalLibros); break;
            case 4: actualizarLibro(listaLibros, totalLibros); break;
            case 5: eliminarLibro(listaLibros, &totalLibros); break;
            case 6: consultarYModificarStock(listaLibros, totalLibros); break;
            case 7: reportesStock(listaLibros, totalLibros); break;
            case 8: guardarLibrosCSV(listaLibros, totalLibros, RUTA_ARCHIVO); break;
            case 9:
                guardarLibrosCSV(listaLibros, totalLibros, RUTA_ARCHIVO);
                printf("👋 Programa finalizado.\n");
                break;
            default:
                printf("❌ Opción inválida.\n");
        }
    } while (opcion != 9);

    return 0;
}
