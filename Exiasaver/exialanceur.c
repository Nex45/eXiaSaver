#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// on appel le fichier c qui contient le code permettant d'afficher l'�cran de veille statique
#include "statique.c"


// Fonctions qui permettent d'enregistrer l'hsitorique des �crans de veille lanc�s dans le fichier stats.txt

int ecrireStatique (char *nom){
       
        FILE *fichier = fopen ("stats.txt", "a+");

        if (fichier != NULL){

//cette fonction nous permet de lire le temps qui s'est �couler depuis le 1er janvier 1970
		time_t t = time (NULL);

//on convertie ce temps pour qu'il affiche l'heure locale 
          	struct tm tm_t = *localtime(&t);

// on cr�er une chaine de caract�re qui nous permet d'afficher l'heure et la date dans un format qui nous convient
         	 char s_t[sizeof "JJ/MM/AAAA HH:MM:SS"];
	
	  	// Cette fonction permet de red�finir la structure de donn�es utilis�e par la fonction time

          	strftime(s_t, sizeof s_t, "%d/%m/%y %H:%M:%S", &tm_t);

// on inscrit notre chaine de caractere � la suite de notre fichier
         	fprintf (fichier, "%s Statique;\t%s \n", s_t,nom);
          	fclose (fichier);
       }
}

int ecrireDyn (void){
 
        FILE *fichier = fopen ("stats.txt", "a+");

        if (fichier != NULL){

          time_t t = time (NULL);
          struct tm tm_t = *localtime(&t);

          char s_t[sizeof "JJ/MM/AAAA HH:MM:SS"];
	
	  // Cette fonction permet de red�finir la structure de donn�es utilis�e par la fonction time
          strftime(s_t, sizeof s_t, "%d/%m/%y %H:%M:%S", &tm_t);

          fprintf (fichier, "%s Dynamique;\tTaille de l'ecran\n", s_t);
          fclose (fichier);
       }
}

int ecrireInte (void){
       
        FILE *fichier = fopen ("stats.txt", "a+");

        if (fichier != NULL){

          time_t t = time (NULL);
          struct tm tm_t = *localtime(&t);

          char s_t[sizeof "JJ/MM/AAAA HH:MM:SS"];
	
	  // Cette fonction permet de red�finir la structure de donn�es utilis�e par la fonction time
          strftime(s_t, sizeof s_t, "%d/%m/%y %H:%M:%S", &tm_t);

          fprintf (fichier, "%s Interactif;\tPosition de l'avion\n", s_t);
          fclose (fichier);
       }
}

//Fonctions permettant de lancer les diff�rents programmes des �crans de veille

int lancementStatique(void){
	int alea;

// on cr�er une chaine de caract�re dans laquelle on placera le chemin de l'image
	char nomImg[50];
	srand(time(NULL));
	alea = rand()%5+1;
	
//cette fonction permet de placer le chemin de l'image dans la chaine de caract�res nomImg
	sprintf(nomImg, "/home/tete/projet/Images/images_statique/img%d.pbm", alea);

//on appel la fonction statique avec comme argument le chemin de notre image
	statique(nomImg);
	ecrireStatique(nomImg);
}

int lancementDynamique(void){
system("clear");

// cette fonction permet de lancer le l'executable du programme de l'�cran de veille
system("/home/tete/projet/dynamique");
ecrireDyn();

}

int lancementInteractif(void){
system("clear");
system("/home/tete/projet/maini");

ecrireInte();
}

int lancementDynamiqueB(void){
system("clear");
system("/home/tete/projet/dynamiqueb");
}

//Fonctions pour l'affichage du menu des statistiques

int menu(void)

{
	system("clear");
        printf("==============MENU=================\n\n");
        printf("Affichez l'ecran des statistiques\n");
        printf("Appuyez sur la touche 's'\n\n");
        printf("Pour quitter le programme appuyez sur la touche 'p'\n\n ");
}

//Fonction qui permet d'afficher le fichier stats.txt
void affichageStats(void){
	char caractere;
	FILE* fichier = NULL;
	fichier = fopen("stats.txt", "r+");

// Tant que le fichier est ouvert
	if(fichier != NULL){

// Tant qu'il y a des caract�res dans le fichier
		while(caractere !=EOF){

//on recup�re le caract�re puis on l'affiche
			caractere = fgetc(fichier);
			printf("%c", caractere);
		}
		printf("\n");
	}
	
	else{
		printf("impossible d'ouvrir le fichier");
	}
}

//Fonction qui permet la selection et l'affichage des diff�rents sous menu
int affichageMenu(void)
{
        char touche;
	int fin = 0;
	menu();

	/*affichage des diff�rents �crans*/

    	while(fin !=1){
        	scanf("%c", &touche);

		if(touche == 's'){

            		system("clear");
            		affichageStats();
	    		printf("Pour revenir sur le menu appuyez sur la touche 'm'\n");
            		continue;

        	}

		else if(touche == 'm'){

			system("clear");
			menu();

		}

		else if(touche == 'p'){

            		system("clear");
            		printf("A bientot\n");
			fin = 1;
            		break;
        	}
	}
}

/*Fonction permettant de choisir al�atoirement un nombre entre 1 et 3 pour ouvrir al�atoirement 1 des 3 types d'�crans de veille*/
void  aleatoire(int *pointeurNbr){

	srand(time(NULL));
	*pointeurNbr = rand()%3+1;

}

int main(int argc, char *argv[])
{

	//detection du nombre d'arguments ajouter apr�s le ./lanceur
	if(argc < 1){

		printf("Erreur, nombre d'arguments invalide");}

	//choix entre les diff�rents arguments
  	else if(argc == 2){

   		if(strcmp(argv[1], "-stats") == 0){
			//printf("test\n");
			affichageMenu(); 
		}

		if(strcmp(argv[1], "-statique") == 0){
			//printf("lancement de l'ecran de veille statique.\n");
			lancementStatique();
		}

		if(strcmp(argv[1], "-dynamique") == 0){

			//printf("lancement de l'ecran de veille dynamique.\n");
			lancementDynamique();
		}

		if(strcmp(argv[1], "-dynamiqueb") == 0){

			//printf("lancement de l'ecran de veille dynamiqueB.\n");
			lancementDynamiqueB();
		}

		if(strcmp(argv[1], "-interactif") == 0){
			//printf("lancement de l'ecran de veille interactif.\n");
			lancementInteractif();
		}
	}
	
	else{
		sleep(2); // temps d'attente avant la mise en veille
	
		//Choix aleatoire des �crans

		int nombre = 0;
		aleatoire(&nombre);
	
		//En fonction du nombre s�lectionn� par la fonction aleatoire on lance un programme parmis les trois que nous avons cr��s

		if(nombre == 1){
			lancementStatique();
		}
	
		else if(nombre == 2){
			lancementDynamique();
		}
	
		else if(nombre == 3){
			lancementInteractif();
		}

 	}

       return 0;

}

