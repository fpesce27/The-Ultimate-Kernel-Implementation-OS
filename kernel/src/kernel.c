#include <kernel.h>

int main(int argc, char *argv[]) {


  if (argc != 2) {
    printf("Debe ingresar el archivo de configuracion\n");
    exit(1);
  }

  t_config* config = iniciar_config(argv[1]);
  t_config* configIp = iniciar_config("/home/utnso/Desktop/tp-2023-1c-Los-pibardos-de-operativos/utils/src/utils/config/ips.config");
  inicializar_variables_globales(config);

  //Hilos que maneja el kernel
  pthread_t hilo_planificacion_largo, hilo_planificacion_corto,hilo_comunicacion_fs;

  inicializar_conexiones(config);

  char *puerto_escucha = config_get_string_value(config, "PUERTO_ESCUCHA");
  char *ip = config_get_string_value(configIp, "IP_KERNEL");
  int socket_servidor = crear_servidor(ip, puerto_escucha);
  
  pthread_create(&hilo_planificacion_largo, NULL, (void *)planificador_largo,NULL);

  pthread_create(&hilo_planificacion_corto, NULL,(void *)planificador_corto,NULL);

  pthread_create(&hilo_comunicacion_fs, NULL,(void *)comunicacion_fs,NULL);

  conectar_consola(socket_servidor);

  pthread_join(hilo_planificacion_corto,NULL);

  pthread_join(hilo_planificacion_largo,NULL);

  pthread_join(hilo_comunicacion_fs,NULL);

  
  terminar_conexiones(3, SOCKET_CPU, SOCKET_MEMORIA, SOCKET_FILESYSTEM);
  terminar_programa(LOGGER_KERNEL, config);

  return 0;
}
