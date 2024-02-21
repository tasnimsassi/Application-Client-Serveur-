#building the application PIPE 
buildpipe:Tubes/source/Handlers_Serv.c Tubes/source/Serveur.c  Tubes/source/Handlers_Serv.h Tubes/source/Handlers_Cli.h Tubes/source/serv_cli_fifo.h Tubes/source/Client.c 
	
	gcc -c Tubes/source/Handlers_Serv.c -o Tubes/binary/Handlers_Serv.o
	gcc -c Tubes/source/Serveur.c -o Tubes/binary/Serveur.o
	gcc Tubes/binary/Handlers_Serv.o Tubes/binary/Serveur.o -o Tubes/binary/Serv.out
	gcc -c Tubes/source/Handlers_Cli.c -o Tubes/binary/Handlers_Cli.o
	gcc -c Tubes/source/Client.c -o Tubes/binary/Client.o
	gcc Tubes/binary/Handlers_Cli.o Tubes/binary/Client.o -o Tubes/binary/clien.out
	chmod 777 Tubes/binary/*.o

#building the application TCP Socket
buildtcp:SocketTCP/source/client.c SocketTCP/source/serveur.c SocketTCP/source/message.h
	gcc SocketTCP/source/serveur.c -o SocketTCP/binary/server.out
	gcc SocketTCP/source/client.c -o SocketTCP/binary/client.out
	chmod 777 SocketTCP/binary/*.out

#building the application UDP Socket
buildudp:SocketUDP/source/client.c SocketUDP/source/serveur.c SocketUDP/source/message.h
	gcc SocketUDP/source/serveur.c -o SocketUDP/binary/server.out
	gcc SocketUDP/source/client.c -o SocketUDP/binary/client.out
	chmod 777 SocketUDP/binary/*.out

#building the graphic application
buildgraphic:./myapp.c
	gcc -o MyApp myapp.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic


#Running the application PIPE 
runclientPipe: 
	./Tubes/binary/clien.out	
runServerPipe: 
	./Tubes/binary/Serv.out

myAppServerPipe : buildpipe runServerPipe

myAppClientPipe : runclientPipe

#Running the application TCP Socket 
runclientTcp: 
	./SocketTCP/binary/client.out	

runServerTcp: 
	./SocketTCP/binary/server.out

myAppServerTcp : buildtcp runServerTcp

myAppClientTcp : runclientTcp

#Running the application UDP Socket 
runclientUdp: 
	./SocketUDP/binary/client.out	

runServerUdp: 
	./SocketUDP/binary/server.out

myAppServerUdp : buildudp runServerUdp

myAppClientUdp : runclientUdp

		
#Running the graphic application 
rungraphic: 
	./MyApp

myGraphicApp : buildgraphic rungraphic