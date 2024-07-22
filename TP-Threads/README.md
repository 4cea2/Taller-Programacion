# Threads

## **Diagrama**

![img](/DiagramaThreads.png)

### **Aclaracion**

Los recursos compartidos como **is_alive**, **continue_accepting** y **state** no tienen metodos *write* y *read*.
En realidad, son asignaciones y lecturas lo que representan.

Ejemplo: el thread main es el unico que escribe a los recursos **continue_accepting** y **state**.
Los hilos Acceptor y GameLoop solo leen estos recursos compartidos.  

## **Fuentes**


Los TDAs **Socket**, **Resolver**, **ResolverError** y **LibError** fueron sacados de https://github.com/eldipa/sockets-en-cpp.

Los TDAs **BoundedQueueBlocking** y **Thread** fueron sacados de https://github.com/eldipa/hands-on-threads. 

Autor: La materia Taller de programacion (TA045), catedra Veiga.

## **Pregunta del enunciado**

Estas queues deberán ser thread-safe para prevenir las RC entre el gameloop y los hilos recibidor y enviador respectivamente. 
Es decisión del alumno qué tipo de queue usar (blocking/nonblocking, bounded/unbounded) y deberá justificarlo.

Use **queues bounded** ya que me parecia útil controlar y limitar el uso de memoria de este programa, asi evitando que la queues consuman demasiada memoria.
De esta manera me ahorro casos de desbordamientos indeseables.

Estas queues cuenta con metodos **blocking** y **nonblocking**, por lo cual, su uso no fue para uno en especifico.

Algunos hilos usaban metodos bloqueantes para evitar que esten en ejecucion todo el tiempo (Receiver y Sender), y otros usaban los no-bloqueantes para seguir en ejecucion siempre (GameLoop).
