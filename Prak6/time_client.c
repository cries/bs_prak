#include <rpc/rpc.h>
#include "time.h"

int main(int argc, char *argv[]) {
	
	CLIENT *cl;
	ergebnis *ergebnis;
	
	if (argc != 3) {
		printf("Aufruf: %s <host> <time|date|wday>\n", argv[0]);
		exit(1);
	}
	
	cl = clnt_create(argv[1], TIMEPROG, TIME_VERSION, "tcp");
	if (cl == NULL) {
		clnt_pcreateerror(argv[1]);
		exit(2);
	}
	
	if (strcmp(argv[2], "date") != 0 &&
		strcmp(argv[2], "time") != 0 &&
		strcmp(argv[2], "wday") != 0)
	{
		printf("Angegebener Dienst '%s' ist unbekannt!\n", argv[2]);
		printf("Verfuegbare Dienste: <date|time|wday>\n");
		exit(3);
	}
	
	
	
	if (strcmp(argv[2], "date") == 0) {
		ergebnis = datefunc_1(NULL, cl);
	} else if (strcmp(argv[2], "time") == 0) {
		ergebnis = timefunc_1(NULL, cl);
	} else if (strcmp(argv[2], "wday") == 0) {
		ergebnis = wdayfunc_1(NULL, cl);
	}
	
	if (ergebnis == NULL) {
		clnt_perror(cl, "Host");
		exit(4);
	}
	
	printf("[Client]	%s\n", ergebnis->result);
	
	return 0;
	
}