# TPs

- **Sockets**: Se implementó un protocolo para que el cliente envíe comandos al servidor en un juego, permitiendo a los personajes realizar acciones especiales. El servidor procesa estos comandos, aplica las acciones según la secuencia y mantiene un contador. Se modularizó el código en clases como Socket, Protocolo, Cliente y Servidor, y se gestionaron los recursos con memoria dinámica, archivos, RAII y la STL de C++. Además, se mejoró la comunicación entre cliente y servidor mediante encapsulación y manejo de Sockets en C++.

- **Threads**: Se desarrollo un esquema cliente-servidor basado en threads. El servidor maneja una partida con 5 enemigos, quienes reviven 3 segundos después de ser eliminados. Los jugadores pueden unirse a la partida y eliminar enemigos. El servidor comunica eventos de revivir o morir de enemigos a todos los clientes conectados, actualizando el estado global de los enemigos. Se utilizó la encapsulación y manejo de threads en C++, y se implementó la comunicación entre threads mediante monitores y queues. Los mensajes de eventos y el estado de los enemigos son impresos tanto por el servidor como por los clientes.

- [**Final**](https://github.com/tomdv18/TpFinalTaller): Se desarrollo un remake multiplayer del juego Jazz Jackrabbit 2 de Epic MegaGames, un
shooter de plataformas 2D de fines de los 90s.
El objetivo es afianzar los conocimientos adquiridos de los anteriores tps, coordinar tareas en grupo y desarrollar una aplicación de complejidad media con buena calidad y usabilidad. Formamos un grupo de 4 alumnos para completar este tp, determinando el ritmo de desarrollo con revisiones semanales con un docente a cargo.
