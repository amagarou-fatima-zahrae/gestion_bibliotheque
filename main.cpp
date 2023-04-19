#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include"projetC.h"
int main(int argc, char** argv) {
    char nom_fichierAdmin[50]="BD_projetC.txt";
	char *email,*fich_pages,choix,ch,*fich_livre,*fich_emprunteur,*fich_emprunt;
    do{
    fflush(stdin);
    ch=menu();
    switch(ch){
            case 'S':{fflush(stdin);
			ajouter(nom_fichierAdmin,sign_in (nom_fichierAdmin));
				break;
			}
            case 'L':{fflush(stdin);
			email=login(nom_fichierAdmin);
				break;
			}
			default:printf("\tchoix invalid!!!!!\n\n");
	}
} while(ch!='L');
fich_pages=rechercher_fichier(1,email,nom_fichierAdmin);
fich_livre=rechercher_fichier(2,email,nom_fichierAdmin);
fich_emprunteur=rechercher_fichier(3,email,nom_fichierAdmin);
fich_emprunt=rechercher_fichier(4,email,nom_fichierAdmin);
do { 
	fflush(stdin);
            choix =menu_admin();
            switch(choix){
            case 'A':{
            	pageAccueil(fich_pages,email);
				break;
			}
            case 'B':{creer_pageAuthentif(fich_pages,email);
				break;
			}
			case 'L':{gestion_livre(fich_pages,fich_livre,email,fich_emprunteur,fich_emprunt);
				break;
			}
		    case 'E':{gestion_emprunt(fich_pages,fich_emprunteur,fich_emprunt,fich_livre,email);
				break;
			}
			case 'P':{
				gestionLien(fich_pages,email);
				break;
			}
			case 'I':{
				 importer();
				break;
			}
             default: printf("choix invalid!!!\n");
            }
            }while (choix!=10);
    return 0;
}
	


