#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {

	DIR *dir;
	struct dirent *d;
	struct stat st;
	unsigned long bytes = 0;
	
	// Verzeichnis öffnen
	if ((dir = opendir(".")) == NULL) {
		fprintf(stderr, "Fehler: Verzeichnis konnte nicht geoeffnet werden!\n");
		return 1;
	}
	// Für alle Elemente im Verzeichnis
	while ((d = readdir(dir)) != NULL) {
		// Verzeichnis ".." ignorieren
		if (strcmp("..", d->d_name) == 0) {
			continue;
		}
		// Eintrag in stat-Struktur schreiben
		stat(d->d_name, &st);
		// Gesamtgröße inkrementieren
		bytes += st.st_size;
		// Eintrag mit Größe ausgeben
		printf("%i	%s\n", st.st_size, d->d_name);
	}
	// Gesamtgröße ausgeben
	printf("%i Byte im Verzeichnis\n", bytes);
	
	// Verzeichniss schließen
	if (closedir(dir) == -1) {
		fprintf(stderr, "Fehler: Verzeichnis konnte nicht geschlossen werden!\n");
		return 2;
	}
	return 0;
}