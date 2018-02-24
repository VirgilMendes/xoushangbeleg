//_CRT_SECURE_NO_WARNINGS
#include "Carte.h";
#include <stdio.h>
#include <stdlib.h>

namespace Modele
{
	Carte::Carte()
	{

		char * buffer[32];
		unsigned long size = 0;

		FILE* fichier = NULL, *sortie = NULL;
		fichier = fopen("ressources/Carte.bmp", "rb");
		sortie = fopen("ressources/sortieCarte.txt", "w+");

		if (fichier == NULL) {
			printf("Impossible d'ouvrir le fichier specifie");
			system("PAUSE");
			exit(0);
		}

		fseek(fichier, 0, SEEK_END);
		size = ftell(fichier);
		fseek(fichier, 0, SEEK_SET);
		if (!size) {
			printf("Le fichier specifie est vide");
			system("PAUSE");
			exit(0);
		}


		for (int i = 0; i < size; i++) {
			fread(buffer, 1, 1, fichier);
			fprintf(sortie, "%s", buffer);
		}

		fclose(fichier);
		fclose(sortie);
	}
}