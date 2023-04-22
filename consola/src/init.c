#include <init.h>

void inicializar_conexiones(int *conexion_kernel, t_config* config) {
    char* ip_kernel = config_get_string_value(config, "IP_KERNEL");
    char* puerto_kernel = config_get_string_value(config, "PUERTO_KERNEL");

    *conexion_kernel = inicializar_cliente(ip_kernel, puerto_kernel, logger_consola);
    
    if (*conexion_kernel == -1) {
        exit(1);
    }
}