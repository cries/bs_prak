# Makefile für Timeserver-Beispiel

CC = cc
LD = -lnsl

all:  time_server time_client

# die XDR-Schnittstelle
time_clnt.c time_svc.c time.h time_xdr.c:  time.x
	rpcgen time.x

# die Server-Prozedur
time_server.o:  time_server.c time.h
	${CC} -c time_server.c -o time_server.o

# der Server-Stub
time_svc.o:  time_svc.c time.h
	${CC} -c time_svc.c -o time_svc.o

# der XDR-Filter
#time_xdr.o:  time_xdr.c time.h
#	${CC} -c time_xdr.c      -o time_xdr.o

# der Client-Stub
time_clnt.o: time_clnt.c time.h
	${CC} -c time_clnt.c      -o time_clnt.o

# das Client-Programm
time_client.o:  time_client.c time.h
	${CC} -c time_client.c    -o time_client.o

# der Server
time_server: time_xdr.o time_svc.o time_server.o
	${CC} ${LD} time_xdr.o time_svc.o time_server.o -o time_server

# der Client
time_client: time_client.o time_xdr.o time_clnt.o
	${CC} ${LD} time_client.o time_xdr.o time_clnt.o -o time_client

clean:
	rm -f time.h time_clnt.* time_svc.* time_xdr.* *.o time_client time_server *~ core

fresh:   clean all

