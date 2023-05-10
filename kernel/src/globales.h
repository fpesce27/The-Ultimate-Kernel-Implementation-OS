#ifndef GLOBALES_H_
#define GLOBALES_H_

#include <utils/logs.h>
#include <commons/collections/list.h>
#include <utils/planificacion/pcb.h>
#include <pthread.h>
#include <semaphore.h>

extern t_log* LOGGER_KERNEL;

//Contador de procesos generados
extern int PID_COUNT;

//Listas para los estados
extern t_list* LISTA_NEW;
extern t_list* LISTA_READY;
extern t_list* LISTA_EXEC;
extern t_list* LISTA_BLOCK;

// Variables de configuracion
extern char* ALGORITMO_PLANIFICACION;
extern int ESTIMACION_INICIAL;
extern float HRRN_ALFA;
extern int GRADO_MAX_MULTIPROGRAMACION;
extern char** RECURSOS;
extern char** INSTANCIAS_RECURSOS;

//Semaforos
extern sem_t CONSOLA_CONECTADA;
extern pthread_mutex_t MUTEX_LISTA_NEW;
extern pthread_mutex_t MUTEX_LISTA_READY;

extern int SOCKET_CPU;

//Declaro las funciones de los monitores
void agregar_a_lista_new(t_pcb* );
void agregar_a_lista_ready(t_pcb* );
void agregar_a_lista_exec(t_pcb* );
void agregar_a_lista_block(t_pcb* );

t_pcb* sacar_de_lista_new(int);
t_pcb* sacar_de_lista_ready(int);
t_pcb* sacar_de_lista_exec(int);
t_pcb* sacar_de_lista_block(int);

#endif