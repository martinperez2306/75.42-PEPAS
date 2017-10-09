# 75.42-PEPAS
Repositorio para los trabajos practicos de Taller de programacion I. Grupo PEPAS.



TP fase 2:

Modelo:

    Servidor:

        1. El servidor va a ser el que haga los calculos de como tiene que dibujar cada cliente, vamos a seguir usando la parte de mensaje privado para que cada cliente le envie al servidor como se movio, el servidor haga los calculos y le envie a los clientes lo que tienen que hacer.
	Ejemplo: el auto se movio a la derecha. El cliente le envia un string(con un protocolo que tenemos que pensar) al servidor, este hace los calculos de lo proximo que tendra que dibujar el cliente, y se lo envia en otro string(con otro protocolo).

	Ejemplo2: 2 autos se encuentran en la misma pantalla. En este caso cuando el servidor calcule lo que tiene que dibujar el cliente, si ve que deben aparecer 2 autos en la pantalla le enviara el string a los 2 clientes para que dibuje al otro cliente y sus movimientos.

	2. La partida debe empezar una vez que esten todos los usuarios conectados por lo que el servidor debera chequear esto constantemente hasta que lo esten. Esto estaba pensado para hacerlo con un thread que este chequeando y cuando llega a la condicion, le manda un mensaje a los clientes de que comenzara la partida.

	3.El parseo del xml de la pista pensamos que estaba en el servidor y que al principio de la partida lo broadcasteee asi lo dibujan todos(Lo repito abajo, pero para esta entrega no es necesario dibujar la posicion de los autos en el mapita, pero para la proxima si. Lo que habiamos pensado que en vez de redibujar todo el mapa todo el tiempo,lo unico que hay que redibujar son los puntos de los autos sobre el mapa).


    Cliente: 

	1.El cliente debe enviar un mensaje al servidor constantemente con el movimiento que esta realizando. Este mensaje se debe a que el servidor calculara la nueva posicion y se la reenviara al cliente para que redibuje la pantalla(Para esta entrega solo redbujara la pantalla del auto, igual pensabamos que el mapita no habia que redibujarlo sino que ir redibujando los puntos sobre el a medida que avanzan los autos, pero esto lo vemos despues).

	2.El cliente es el que se encargara de dibujar. Con el string que le mande el servidor, utilizara esa informacion para dibujar con la libreria sdl.

	3.El cliente no debe pensar, lo unico que hace es enviar, recibir y dibujar, no calcula nada.


