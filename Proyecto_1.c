// Bryant Mendez - 30705399
// David Duran   - 31447647
// Jhonter Medina - 31863341
// Yohan Jacanamijoy - 31699984
// Lorena Benitez - 32105732

// Bryant
// ========== ARCHIVO DE PACIENTES (HISTÓRICO) ==========

void guardarPaciente(Paciente p) {
    FILE *archivo = fopen("pacientes.txt", "a");
    if (archivo != NULL) {
        fprintf(archivo, "%s|%lld|%d.%d|%s|%s|%d|%s\n", 
                p.nombre_completo, p.ci_num, p.edad_anios, p.edad_meses,
                p.motivo, p.fecha_registro, p.en_cola, p.area);
        fclose(archivo);
        printf("Paciente guardado en historico correctamente.\n");
    } else {
        printf("Error al abrir el archivo para guardar.\n");
    }
}

void cargarPacientes() {
    FILE *archivo = fopen("pacientes.txt", "r");
    if (archivo != NULL) {
        printf("\n======= HISTORICO DE PACIENTES REGISTRADOS =======\n");
        Paciente p;
        int contador = 0;

        while (fscanf(archivo, "%50[^|]|%lld|%d.%d|%59[^|]|%19[^|]|%d|%29[^\n]\n",
                      p.nombre_completo, &p.ci_num, &p.edad_anios, &p.edad_meses,
                      p.motivo, p.fecha_registro, &p.en_cola, p.area) == 8) {

            printf("\nPaciente %d:\n", ++contador);
            printf("Nombre completo: %s\n", p.nombre_completo);
            printf("C.I: %lld\n", p.ci_num);
            printf("Edad: %d años y %d meses\n", p.edad_anios, p.edad_meses);
            printf("Motivo: %s\n", p.motivo);
            printf("Fecha registro: %s\n", p.fecha_registro);
            printf("Area: %s\n", p.area);
            printf("En cola: %s\n", p.en_cola ? "SI" : "NO");
        }

        if (contador == 0)
            printf("No hay pacientes registrados.\n");

        fclose(archivo);
    } else {
        printf("No se encontró archivo de pacientes o está vacío.\n");
    }
}

// ========== GESTIÓN DE COLA ==========

void guardarEnCola(Paciente p) {
    FILE *archivo = fopen("cola_pacientes.txt", "a");
    if (archivo != NULL) {
        fprintf(archivo, "%s|%lld|%d.%d|%s|%s|%s\n",  
                p.nombre_completo, p.ci_num, p.edad_anios, p.edad_meses,
                p.motivo, p.fecha_registro, p.area);
        fclose(archivo);
        printf("Paciente agregado a la cola de espera.\n");
    }
}

void cargarCola() {
    FILE *archivo = fopen("cola_pacientes.txt", "r");
    if (archivo == NULL) {
        printf("\nNo hay pacientes en la cola de espera.\n");
        return;
    }
    
    printf("\n======= PACIENTES EN COLA DE ESPERA =======\n");
    Paciente p;
    char linea[256];
    int contador = 0;
    
    // Leer línea por línea
    while (fgets(linea, sizeof(linea), archivo)) {
        if (sscanf(linea, "%50[^|]|%lld|%d.%d|%59[^|]|%19[^|]|%29[^\n]",
                  p.nombre_completo, &p.ci_num, &p.edad_anios, &p.edad_meses,
                  p.motivo, p.fecha_registro, p.area) == 7) {
            
            contador++;
            printf("\n--- Paciente %d ---\n", contador);
            printf("Nombre: %s\n", p.nombre_completo);
            printf("C.I: %lld\n", p.ci_num);
            printf("Edad: %d años y %d meses\n", p.edad_anios, p.edad_meses);
            printf("Motivo: %s\n", p.motivo);
            printf("Hora registro: %s\n", p.fecha_registro);
            printf("Area: %s\n", p.area);
        }
    }
    
    if (contador == 0) {
        printf("La cola está vacía.\n");
    } else {
        printf("\nTotal de pacientes en cola: %d\n", contador);
    }
    
    fclose(archivo);
}

void eliminarDeCola(long long int ci) {
    FILE *archivo = fopen("cola_pacientes.txt", "r");
    if (archivo == NULL) {
        printf("No hay archivo de cola o está vacío.\n");
        return;
    }
    
    FILE *temp = fopen("temp_cola.txt", "w");
    if (temp == NULL) {
        printf("Error al crear archivo temporal.\n");
        fclose(archivo);
        return;
    }
    
    Paciente p;
    int encontrado = 0;
    char linea[256];
    
    // Leer línea por línea
    while (fgets(linea, sizeof(linea), archivo)) {
        if (sscanf(linea, "%50[^|]|%lld|%d.%d|%59[^|]|%19[^|]|%29[^\n]",
                  p.nombre_completo, &p.ci_num, &p.edad_anios, &p.edad_meses,
                  p.motivo, p.fecha_registro, p.area) == 7) {
            
            if (p.ci_num == ci) {
                encontrado = 1;
                printf("Paciente con CI %lld eliminado de la cola.\n", ci);
            } else {
                fputs(linea, temp);
            }
        }
    }
    
    fclose(archivo);
    fclose(temp);
    
    if (encontrado) {
        remove("cola_pacientes.txt");
        rename("temp_cola.txt", "cola_pacientes.txt");
    } else {
        remove("temp_cola.txt");
        printf("No se encontró al paciente en la cola.\n");
    }
}

// Lorena
// ========== FUNCIÓN DE LLAMADOS ==========

void llamarSiguientePaciente() {
    FILE *archivo = fopen("cola_pacientes.txt", "r");
    if (archivo == NULL) {
        printf("No hay pacientes en la cola de espera.\n");
        return;
    }

    Paciente p;
    char primeraLinea[256];
    
    // Leer la primera línea completa
    if (fgets(primeraLinea, sizeof(primeraLinea), archivo) != NULL) {
        if (sscanf(primeraLinea, "%50[^|]|%lld|%d.%d|%59[^|]|%19[^|]|%29[^\n]",
                   p.nombre_completo, &p.ci_num, &p.edad_anios, &p.edad_meses,
                   p.motivo, p.fecha_registro, p.area) == 7) {
            
            printf("\n📢 LLAMANDO SIGUIENTE PACIENTE 📢\n");
            printf("Nombre: %s\n", p.nombre_completo);
            printf("C.I: %lld\n", p.ci_num);
            printf("Edad: %d años y %d meses\n", p.edad_anios, p.edad_meses);
            printf("Motivo: %s\n", p.motivo);
            printf("Hora registro: %s\n", p.fecha_registro);
            printf("Area: %s\n", p.area);

            fclose(archivo);
            
            eliminarDeCola(p.ci_num);
            
            // Actualizar estado en archivo histórico 
            FILE *hist = fopen("pacientes.txt", "r");
            if (hist == NULL) {
                printf("No se pudo abrir el historico.\n");
                return;
            }
            
            FILE *temp = fopen("temp.txt", "w");
            if (temp == NULL) {
                printf("Error al crear archivo temporal.\n");
                fclose(hist);
                return;
            }
            
            Paciente p2;
            char lineaHist[256];
            int actualizado = 0;
            
            while (fgets(lineaHist, sizeof(lineaHist), hist)) {
                if (sscanf(lineaHist, "%50[^|]|%lld|%d.%d|%59[^|]|%19[^|]|%d|%29[^\n]",
                          p2.nombre_completo, &p2.ci_num, &p2.edad_anios, &p2.edad_meses,
                          p2.motivo, p2.fecha_registro, &p2.en_cola, p2.area) == 8) {
                    
                    if (p2.ci_num == p.ci_num) {
                        p2.en_cola = 0;
                        actualizado = 1;
                    }
                    
                    fprintf(temp, "%s|%lld|%d.%d|%s|%s|%d|%s\n",
                            p2.nombre_completo, p2.ci_num, p2.edad_anios, p2.edad_meses,
                            p2.motivo, p2.fecha_registro, p2.en_cola, p2.area);
                }
            }
            
            fclose(hist);
            fclose(temp);
            
            if (actualizado) {
                remove("pacientes.txt");
                rename("temp.txt", "pacientes.txt");
                printf("Estado actualizado en el historico.\n");
            } else {
                remove("temp.txt");
            }
            
        } else {
            printf("Error al leer datos del paciente.\n");
            fclose(archivo);
        }
    } else {
        printf("\n✅ No quedan pacientes en la cola de espera.\n");
        fclose(archivo);
    }
}

//David  
 // Verificación de datos
                do {
                    printf("\n======= VERIFICACION DE DATOS =====\n");
                    printf("Nombre completo: %s\n", nombre_completo);
                    printf("Area: %s\n", area_nombre);
                    printf("Cédula: %s-%lld\n", (tipo_ci == 1 ? "V" : "E"), ci_num);
                    printf("Edad: %d años y %d meses\n", edad_anios, edad_meses);
                    printf("Motivo: %s\n", motivo);
                    
                    printf("\n[1] Modificar todo\n[2] Confirmar y Guardar\n[3] Modificar dato especifico\n");
                    scanf("%d", &n);

                    if(n == 3) {
                        printf("\n¿Que dato desea modificar?\n");
                        printf("[1] Nombre completo\n[2] Area\n[3] Cedula\n[4] Edad\n[5] Motivo\n");
                        scanf("%d", &opcion_especifica);
                        
                        if(opcion_especifica == 1) {
                            do {
                                printf("Nuevo nombre y apellido: ");
                                scanf(" %[^\n]", nombre_completo);
                                if (!validarSoloLetrasYEspacios(nombre_completo)) {
                                    printf("[Error] Solo puede contener letras y espacios.\n");
                                }
                            } while (!validarSoloLetrasYEspacios(nombre_completo));
                        }
                        else if(opcion_especifica == 2) {
                            do {
                                mostrarAreas();
                                printf("\nNueva área (0-9): ");
                                valido = scanf("%d", &opcion_area);
                                if (valido != 1 || opcion_area < 0 || opcion_area > 9) {
                                    printf("[Error] Opción inválida.\n");
                                    while(getchar() != '\n');
                                    valido = 0;
                                } else {
                                    obtenerNombreArea(opcion_area, area_nombre);
                                }
                            } while(valido == 0);
                        }
                        else if(opcion_especifica == 3) {
                            do {
                                printf("Nuevo tipo de documento (1=Venezolana, 2=Extranjera): ");
                                valido = scanf("%d", &tipo_ci);
                                if (valido != 1 || (tipo_ci != 1 && tipo_ci != 2)) {
                                    printf("[Error] Opción inválida.\n");
                                    while(getchar() != '\n');
                                    valido = 0;
                                } else {
                                    do {
                                        printf("Nuevo número de cédula: ");
                                        valido = scanf("%lld", &ci_num);
                                        if (valido == 1) {
                                            if (tipo_ci == 1) {
                                                if (ci_num < 100000 || ci_num > 99999999) { // 6-8 dígitos
                                                    printf("[Error] Cédula venezolana inválida (6-8 dígitos).\n");
                                                    printf("Ejemplos: 123456, 1234567, 12345678\n");
                                                    valido = 0;
                                                }
                                            } else {
                                                if (ci_num < 1 || ci_num > 999999999999LL) { // 1 a 12 dígitos
                                                    printf("[Error] Identificación extranjera inválida (máximo 12 dígitos).\n");
                                                    valido = 0;
                                                }
                                            }
                                        } else {
                                            printf("[Error] Ingrese un número válido.\n");
                                            while(getchar() != '\n');
                                        }
                                    } while(valido == 0);
                                }
                            } while(valido == 0);
                        }
                        else if(opcion_especifica == 4) {
                            do {
                                printf("Nuevos años (0-120): ");
                                valido = scanf("%d", &edad_anios);
                                if (valido != 1 || edad_anios < 0 || edad_anios > 120) {
                                    printf("[Error] Años inválidos.\n");
                                    while(getchar() != '\n');
                                    valido = 0;
                                } else {
                                    printf("Nuevos meses (0-11): ");
                                    valido = scanf("%d", &edad_meses);
                                    if (valido != 1 || edad_meses < 0 || edad_meses > 11) {
                                        printf("[Error] Meses inválidos (0-11).\n");
                                        printf("Recuerde: 12 meses = 1 año\n");
                                        while(getchar() != '\n');
                                        valido = 0;
                                    } else if (edad_anios == 0 && edad_meses == 0) {
                                        printf("[Error] La edad no puede ser 0 años y 0 meses.\n");
                                        valido = 0;
                                    }
                                }
                            } while(valido == 0);
                        }
                        else if(opcion_especifica == 5) {
                            do {
                                printf("Nuevo motivo: ");
                                scanf(" %[^\n]", motivo);
                                if (!validarSoloLetrasYEspacios(motivo)) {
                                    printf("[Error] Solo puede escribir letras y espacios.\n");
                                }
                            } while (!validarSoloLetrasYEspacios(motivo));
                        }
                    }
                } while(n == 3);

            } while(n == 1);