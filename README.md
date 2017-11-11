# 75.42-PEPAS
Repositorio para los trabajos practicos de Taller de programacion I. Grupo PEPAS.



TP fase 3:

Modelo:

    Servidor:
	
	El servidor en este momento recibe la tecla que toca cada auto y le devuelve a cada cliente lo que tiene que dibujar(su posicion en x e y, y si tiene que dibujar a un rival la posicion en x del rival y la distancia que le lleva).

	Cosas que faltan:
	
		1. Colisiones: El servidor tiene que calcular si 2 autos chocan de costado de frente (el de atras al de adelante) o con objetos.
		2.Puntaje: Tiene que calcular puntajes con una logica que no dijeron asique lo pensaremos nosotros por ahora.
		3.Pistas: Tiene que cargar distintas pistas para que se juegue en mas de una.(Primero una despues la otra hasta que se juegue en todas)
		4.Comienzo: El juego debe comenzar luego de una cantidad de segundos desde que se conecto el ultimo cliente, y deben empezar todos al mismo tiempo
		5.Radar: El servidor tambien debera enviar a cada cliente la actualizacion del minimapa de cada jugador.(El minimapa se vera igual para todos los clientes asique esto deberia ser un mensaje tipo broadcast)

    Cliente: 

	El cliente en este momento tiene el login basico, espera a que se conecte la maxima cantidad de jugadores y empieza el juego.
		
	Cosas que faltan:
		
		1.Login: el login que esta ahora es basico, hay que ponerle uno mejor
		2.Cominezo: Como se ve en este item del servidor, la carrera debe empezar luego de unos segundos de que se haya conectado el ultimo cliente, y esto debe avisarse en la pantalla.(3... 2... 1... go)
		3.Radar: Actualizar el radar visualmente
		4.Pistas: no sabemos bien todavia si los clientes deben elegir una pista para correr o que sera al azar, pero debe poder correr las 3 pistas una atras de la otra por ahora.
		5.Puntajes: Luego de cada carrera se deberan visualizar los puntajes en la pantalla
	
	Errores que encontramos hasta ahora:

		1.3-4 jugadores: la logica del juego anda bien para 4 jugadores, pero en la pantalla siempre dibuja 1 o 2 autos, el propio y el rival mas adelante que se pueda ver. Esto hay que arreglarlo porque el juego deberia ser de hasta 4 personas.
		2. Mala visualizacion en la cercania: Cuando el rival esta muy cerca nuestro y se esta corriendo titila mucho su sprite, se ve muy feo.	
		3.Tamanio de sprites: A azcurra no le gusto que los arboles sean tan grandes, habria que achicarles la imagen un poco, nada una boludez pero para acordarse.
		4.Imagen de autos: Hay un problema que cuando se loguean los usuarios al mismo tiempo dibuja los mismos autos ya sea rival y propio cuando tendrian que ser diferentes.Esto no pasa si primero se loguea un usuario, y luego otro.
		5.Error rarisimo Login: A veces despues de loguearse crashea el juego en el cliente, y tambien en el servidor, todavia no sabemos porque, esto no pasaba en la entrega del chat, asique es un problema de ahora.Este error no pasa siempre lo cual lo hace mas raro y dificil de deuguear.

