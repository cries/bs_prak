#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {

	DIR *dir;
	struct dirent *dir_st;
	struct stat container;
	unsigned long totalbytes = 0;
	
	// Verzeichnis öffnen
	if ((dir = opendir(".")) == NULL) {
		fprintf(stderr, "Fehler: Verzeichnis konnte nicht geoeffnet werden!\n");
		return 1;
	}
	// Für alle Elemente im Verzeichnis
	while ((dir_st = readdir(dir)) != NULL) {
		// Verzeichnis ".." ignorieren
		if (strcmp("..", dir_st->d_name) == 0) {
			continue;
		}
		// Eintrag in stat-Container schreiben
		stat(dir_st->d_name, &container);
		// Gesamtgröße inkrementieren
		totalbytes += container.st_size;
		// Eintrag mit Größe ausgeben
		printf("%i	%s\n", container.st_size, dir_st->d_name);
	}
	// Gesamtgröße ausgeben
	printf("%i Byte im Verzeichnis\n", totalbytes);
	
	// Verzeichnis schließen
	if (closedir(dir) == -1) {
		fprintf(stderr, "Fehler: Verzeichnis konnte nicht geschlossen werden!\n");
		return 2;
	}
	return 0;
}