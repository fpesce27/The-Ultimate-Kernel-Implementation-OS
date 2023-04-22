#include <consola.h>

int main(int argc, char *argv[])
{

  logger_consola = iniciar_logger("./logs/consola.log", "CONSOLA");

  FILE *f = verificar_argumentos(argc, argv);
  if (f == NULL)
  {
    return EXIT_FAILURE;
  }

  t_config *config = iniciar_config(argv[1]);

  int conexion_kernel;
  inicializar_conexiones(&conexion_kernel, config);

  char buffer[100]; // No sabemos para que sirve


  t_paquete *paquete = crear_paquete(INSTRUCCION);

  while ((fgets(buffer, 100, f)) != NULL)
  {
    t_instruccion *instruccion = crear_estructura_instruccion(buffer);
    
    int tamanio_instruccion = serializar_instruccion(instruccion, buffer);
    
    agregar_a_paquete(paquete, instruccion, tamanio_instruccion);

  }
  // Probablemente usemos el enviar_paquete del tp0
  enviar_paquete(paquete, conexion_kernel);

  log_info(logger_consola, "Paquete enviado");

  terminar_conexiones(1, conexion_kernel);
  terminar_programa(logger_consola, config);

  return 0;
}
