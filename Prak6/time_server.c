#include <rpc/rpc.h>
#include <time.h>
#include "time.h"



ergebnis *timefunc_1() {
	/* Datum und Zeit */
	struct tm *datum;
	time_t heute;
	time(&heute);
	datum = localtime(&heute);
	static ergebnis ergebnis;
	/*sprintf(ergebnis.result, "%02d:%02d:%2d", datum->tm_hour, datum->tm_min, datum->tm_sec);*/
	sprintf(ergebnis.result, "%02d:%02d:%2d\n", datum->tm_hour, datum->tm_min, datum->tm_sec);
	printf("[Server]	%s", ergebnis.result);
	return &ergebnis;
}

ergebnis *datefunc_1() {
	/* Datum und Zeit */
	struct tm *datum;
	time_t heute;
	time(&heute);
	datum = localtime(&heute);
	static ergebnis ergebnis;
	/*sprintf(ergebnis.result, "%02d.%02d.%4d", datum->tm_mday, datum->tm_mon+1, datum->tm_year+1900);*/
	sprintf(ergebnis.result, "%02d.%02d.%4d\n", datum->tm_mday, datum->tm_mon+1, datum->tm_year+1900);
	printf("[Server]	%s", ergebnis.result);
	return &ergebnis;
}

ergebnis *wdayfunc_1() {
	/* Datum und Zeit */
	char *day[] = {"Sonntag","Montag","Dienstag","Mittwoch","Donnerstag","Freitag","Samstag"};
	struct tm *datum;
	time_t heute;
	time(&heute);
	datum = localtime(&heute);
	static ergebnis ergebnis;
	/*sprintf(ergebnis.result, "%s", day[datum->tm_wday]);*/
	sprintf(ergebnis.result, "%s\n", day[datum->tm_wday]);
	printf("[Server]	%s", ergebnis.result);
	return &ergebnis;
}