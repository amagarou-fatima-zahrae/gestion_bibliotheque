#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include"projetC.h"

//************fonctions pour gerer les livres*******************************************
int NbrExemplaire_emp(char*code,char *emprunt){
	int nbr=0;
	FILE*f=fopen(emprunt,"a+");
	Emprunt *em=(Emprunt*)malloc(sizeof(Emprunt));
	if(f!=NULL){
		while(!feof(f)){
		 if(fscanf(f,"%s  %s\n",em->code_livre,em->email)!=-1){
		 	if(strcmp(code,em->code_livre)==0){ 
		 	nbr++;	
	        }
	      }
	     }
	fclose(f);
  }
  else{
  	printf("erreur d\'ouverture le fichier des emprunts!!!\n");
  }
  return nbr;		 
}
int rechercher_livre(char*code,char *fich_livres){//livre unique

	Livre *newl=(Livre*)malloc(sizeof(Livre));
    FILE *fp1=fopen(fich_livres,"r+");
    if(fp1!=NULL){
        while(!feof(fp1)){
            if(fscanf(fp1,"%s  %s  %s  %d  %f\n",newl->code_livre,newl->auteur,newl->titre,&newl->nbr_exemplaires,&newl->prix)!=-1){
              if(strcmp(newl->code_livre,code)==0){
                    fclose(fp1);
                    return newl->nbr_exemplaires;
                }
            }
        }
        fclose(fp1);
    }
    else{
	printf("une erreur d'ouverture des fichier de livres \n");
	}
    return -1;
}
char sous_menuS(){
  printf("\n\n");
  printf("_______________ voulez vous supprimer:_____________\n");
  printf("\tTappez T pour un Livre totalement avec tous ses exemplaires\n");
  printf("\tTappez E pour un exemplaire d\'un livre \n");
  fflush(stdin);
  printf("___________Veuillez entrer votre choix___________\n");
  getchar();
}
char sous_menuL(){
   printf("\n\n");
  printf("_______________Vous voulez ajouter:_____________\n");
  printf("\tTappez N pour un \"nouveau Livre\"\n");
  printf("\tTappez E pour un exemplaire d\'un livre deja existe \n");
  fflush(stdin);
  printf("___________Veuillez entrer votre choix___________\n");
  getchar();
}
Livre* Saisir_livre(char *fich_livres,char *email,char*fich_emprunteur){
	char choix;
	Livre *l=(Livre*)malloc(sizeof(Livre));
    int exister;
do{
	choix=sous_menuL();
	switch(choix){
		  case 'N':{
		fflush(stdin);
          printf("----- entrer le code du livre-------\n");
    etic:
    scanf("%s",l->code_livre);
    exister=rechercher_livre(l->code_livre,fich_livres);
        if(exister!=-1){
            printf("-----Cet code du livre existe deja. Veuilez entrer un autre:-----\n");
            goto etic;
        }
    
    fflush(stdin);
    printf("-----entrer l\'auteur du livre------\n");
    scanf("%s",l->auteur);
    fflush(stdin);
    printf("-----entrer le titre du livre------- \n");
    gets(l->titre);
    fflush(stdin);
    do{
    printf(" -----entrer le nombre des exemplaires du livre-----\n");
    scanf("%d",&l->nbr_exemplaires);
	}while(l->nbr_exemplaires<=0);
    fflush(stdin);
    printf(" -----entrer le prix du livre------\n");
    scanf("%f",&l->prix);
    printf("\n\n");
    return l;
}
    case 'E':{
    	indice:
    	fflush(stdin);
        printf(" -----entrer le code du livre-----\n");
        scanf("%s",l->code_livre);
		exister=rechercher_livre(l->code_livre,fich_livres);
		if(exister!=-1){
		 modifier(4,l->code_livre,fich_livres,email,fich_emprunteur);
		 return NULL;	
		}
		else{
		printf("-----le livre n\'existe pas!!!-----\n");
     	goto indice;
     	}
	}
	  break;
} 
 }while(choix!='E' && choix!='N');  
   
}
void Ajouter_livre(char *fich_livre, Livre *newl){
	FILE *fp=fopen(fich_livre,"a+");
	 if(fp!=NULL){
	fprintf(fp,"%s  %s  %s  %d  %f\n",newl->code_livre,newl->auteur,newl->titre,newl->nbr_exemplaires,newl->prix);
	 fclose(fp);
	}
	else{
		printf("erreur d\'ouverture du fichier!!!\n");
	}
}

char menu_livre(){
 printf("\n\n");
printf("______ajouter un livre ______ a\n") ; 
printf("_______supprimer un livre ______s\n") ;	
printf("_______ lister les livres________ l\n") ;	
printf("_______ rechercher un livre________ r\n") ;
printf("_______quitter ______q\n") ; 
printf("-----veuillez entrer votre choix:-----\n");
return getchar();	
}

void Page_ajouter_livre(char *fich_pages,char*fich_livres,char*email,char*fich_emprunteur){//nom_fich:fichier des pages
	FILE *p;
	Livre *l=(Livre*)malloc(sizeof(Livre));
	l=Saisir_livre(fich_livres,email,fich_emprunteur);
	if(l!=NULL){
	Ajouter_livre(fich_livres,l);
	}
	char *lien,*c1,*c2,*c3;
	c3=NULL;
	lien=verifier_creation(3,fich_pages);
	c1=verifier_creation(11,fich_pages);
	c2=verifier_creation(1,fich_pages);
	if(c1!=NULL && c2!=NULL){
		c3=c2;
	}
 if(lien!=NULL){
 	     printf("\n\n");
		printf("______votre page d\'ajouter le livre  est deja cree \n________et les info du livre ont ete bien ajoutes\n");
		printf("_________Voici le lien pour acceder a la page ajouter < %s > : \n",lien);
		goto label;
	  }	
     else{
     lien=ajouter_page(3,email,fich_pages);
      printf("\n\n");
      printf("____la page a ete cree avec succes______\n________et les info du livre ont ete bien ajoutes dans la page lister\n_______Voici le lien pour acceder a la page ajouter: <%s>:\n",lien);
	 label:
     p=fopen(lien,"w");
     if(lien!=NULL){
     fprintf(p,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Ajouter livre</title><link rel=\"stylesheet\" href=\"css/tooplate-style.css\"><link rel=\"stylesheet\" href=\"styleForm.css\"><link rel=\"stylesheet\" href=\"styleRechercher.css\"></head><body><div id=\"tm-bg\"></div><div id=\"tm-wrap\"><a target=\"_blank\"  href=\"%s\">Acceuil</a><div class=\"card-body\"><h2 class=\"title\">Ajouter un livre</h2><form method=\"POST\"><div class=\"input-group\"><input class=\"input--style-1\" type=\"text\" placeholder=\"Code du livre\" name=\"name\"></div><div class=\"input-group\"><input class=\"input--style-1\" type=\"text\" placeholder=\"Titre du livre\" name=\"name\"></div><div class=\"input-group\"><input class=\"input--style-1\" type=\"text\" placeholder=\"Auteur\" name=\"name\"></div><div class=\"input-group\"><input class=\"input--style-1\" type=\"text\" placeholder=\"Nombre d\'exemplaire\" name=\"name\"></div><div class=\"p-t-20\"><button class=\"btn btn--radius btn--green\" type=\"submit\">Submit</button></div></form></div></body></html>",c3);
    
     fclose(p);
	 }
	 else{
	 	printf("erreur d\'ouverture du fichier!!!\n");
	 }
	 }
	  printf("\n\n");
}
void supprimer_livre(char*code,char *nom_fich_livres){
 	FILE *f_in=fopen(nom_fich_livres,"r");
 	FILE *f_out=fopen("supprimer.txt","w");
 	if(f_in!=NULL && f_out!=NULL){
 		Livre *newl=(Livre*)malloc(sizeof(Livre));
 		while(!feof(f_in)){
		 if(fscanf(f_in,"%s  %s  %s  %d  %f\n",newl->code_livre,newl->auteur,newl->titre,&newl->nbr_exemplaires,&newl->prix)!=-1){
		 	if(strcmp(newl->code_livre,code)!=0){
		 fprintf(f_out,"%s  %s  %s  %d %.2f \n",newl->code_livre,newl->auteur,newl->titre,newl->nbr_exemplaires,newl->prix);
		 }
		}
	}
	  	fclose(f_in);
		 fclose(f_out);
		 remove(nom_fich_livres);
		 rename("supprimer.txt",nom_fich_livres);
		 printf("-----la suppression du livre est reussie-----\n");
		  printf("\n\n");

	 }
 }
void Page_supprimer_livre(char *fich_pages,char*fich_livres,char*email,char *emprunt,char *emprunteur){//nom_fich:fichier des pages
 FILE *p;
 int test,exister;
 char choix;
 char code[20];
 repeter:
 printf("_______veuillez entrer le code du livre que vous voulez supprimer:__________\n");
 scanf("%s",code);
 exister=rechercher_livre(code,fich_livres);
 if(exister==-1){
	printf("-----le livre n\'existe pas!!!-----\n");
	goto repeter;	
		}
 else{
 	test=NbrExemplaire_emp(code,emprunt);
 do{
  choix=sous_menuS();
  switch(choix){
  	case 'T':{
	  if(test==0){
	  	effacer:
	  	supprimer_livre(code,fich_livres);
	  }	
	  else{
	  	printf("__Vous ne pouvez pas supprimer ce livre totalement \n_______car il est empreinte par %d emprunteurs!!!\n ",test);
	  }
		break;
}
	case 'E':{
		if(exister!=0){
		modifier(1,code,fich_livres,email,emprunteur);
		printf("____la suppression d\'un exemplaire de ce livre a ete faite avec succes_____\n");
		}
		else{
			if(test!=0){
				printf("____Il n\'existe pas un exemplaire libre de ce livre pour le supprimer\n________car tous ses exemplaires sont deja empruntes!!\n");
			}
		    else{
		    	goto effacer;
			}
		}
		break;
	}
  }
 }while(choix!='T' && choix!='E');
}
 
	char *lien,*c1,*c2,*c3;
	c3=NULL;
	c1=verifier_creation(11,fich_pages);
	c2=verifier_creation(1,fich_pages);
	if(c1!=NULL && c2!=NULL){
		c3=c2;
	}
	lien=verifier_creation(5,fich_pages);
 if(lien!=NULL){
		printf("_____votre page de supprimer le livre  est deja cree \n______et les info du livre ont ete bien supprimes\n");
		printf("_______Voici le lien pour acceder a la page supprimer <%s> : \n",lien);
		goto label;
	  }	
     else{
     	lien=ajouter_page(5,email,fich_pages);
     	printf("____la page supprimer un livre a ete cree avec succes______\net les info du livre ont ete bien supprimes dans la page lister\n______Voici le lien pour acceder a la page supprimer: <%s>:\n",lien);
     	label:
     p=fopen(lien,"w");
     if(lien!=NULL){
     fprintf(p,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Supprimer un livre</title><link rel=\"stylesheet\" href=\"css/bootstrap.min.css\"><link rel=\"stylesheet\" href=\"css/tooplate-style.css\"><link rel=\"stylesheet\" href=\"styleForm.css\"> <link rel=\"stylesheet\" href=\"styleRechercher.css\">  </head><body><div id=\"tm-bg\"></div><div id=\"tm-wrap\"><div class=\"container tm-site-header-container\"><a target=\"_blank\" href=\"%s\">Acceuil</a><form id= \"searchbox\"><input name= \"q\"  type= \"text\"  size= \"15\" placeholder=\"Entrer le code du livre a supprimer\"  /><input id=\"button-submit\"  type=\"submit\"  value=\"Supprimer\" /></form></div></div></div></div></body></html>",c3);
     
     fclose(p);
	 }
	 else{
	 	printf("erreur d\'ouverture du fichier!!!\n");
	 }
	 }
	  printf("\n\n");
}

int lister_livres(char *nom_fich,char *email,char *fich_livres){
FILE *fp,*fq;
	char *lien,*c1,*c2,*c3;
	c3=NULL;
	c1=verifier_creation(11,nom_fich);
	c2=verifier_creation(1,nom_fich);
	if(c1!=NULL && c2!=NULL){
		c3=c2;
	}
	lien=verifier_creation(4,nom_fich);
	if(lien!=NULL){
	 printf("\n\n");
		printf("_____votre page de lister les livres est deja cree\ntoutes les mises a jour sont faites\n ");
		printf("______Voici le lien pour acceder a la page et visualiser les livres<%s>:\n",lien);
		lieu:
		fq=fopen(fich_livres,"r");
	 if(fq!=NULL){
	 	fp=fopen(lien,"w");
	 	if(fp!=NULL){
	 	fprintf(fp,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\"content=\"width=device-width,initial-scale=1\"><title>Liste des livres</title><link rel=\"stylesheet\"href=\"css/bootstrap.min.css\"><link rel=\"stylesheet\"href=\"css/tooplate-style.css\"><link rel=\"stylesheet\"href=\"lister.css\"></head><body><div id=\"tm-bg\"></div><div id=\"tm-wrap\"><div class=\"card-body\"><!--HEEERE--><a target=\"_blank\" href=\"%s\">Acceuil</a><table><tr><th scope=\"col\">Code du livre</th><th scope=\"col\">Auteur du livre</th><th scope=\"col\">Titre du livre</th><th scope=\"col\">Nombre d'exemplaire</th><th scope=\"col\">Prix</th></tr>",c3);
  	    Livre *newl=(Livre*)malloc(sizeof(Livre));
  		while(!feof(fq)){
  		if(fscanf(fq,"%s %s %s %d %f \n",newl->code_livre,newl->auteur,newl->titre,&newl->nbr_exemplaires,&newl->prix)!=-1){
		fprintf(fp,"<tr><th scope=\"row\">%s</th><td>%s</td><td>%s</td><td style=\"color:white;font-weight: bolder;font-size: 1.5rem;\">%d</td><td>%.2f</td></tr>\n",newl->code_livre,newl->auteur,newl->titre,newl->nbr_exemplaires,newl->prix);
         }	
	 }
   fprintf(fp,"</table></div></body></html>");
   fclose(fp);
   }
   else{
   	printf("erreur d\'ouverture le fichier html de lister!!\n");
   }
    
	fclose(fq);
	return 0;
	}
	else{
   	printf("erreur d\'ouverture le fichier des livres!!\n");
   } 
}
	else{
  lien=ajouter_page(4,email,nom_fich);
   printf("\n\n");
  printf("____la page a ete cree avec succes______\nVoici le lien pour acceder a la page et visualiser les livres: <%s>:\n",lien);
  goto lieu;
  
  }
	 fclose(fp);
	  printf("\n\n");
	 return 0;	
} 
void Afficher_livre(char *nom_fich_livres){
	int exister=0;
 	char code_livre[20];
	printf("_____veuillez entrer le code du livre que vous voulez rechercher:____\n");
	scanf("%s",code_livre);
 	FILE *f_in=fopen(nom_fich_livres,"r");
 	 if(f_in!=NULL){
 	  Livre newl;
 		while(!feof(f_in)){
		 if(fscanf(f_in,"%s %s %s %d %f \n",newl.code_livre,newl.auteur,newl.titre,&newl.nbr_exemplaires,&newl.prix)!=-1){
		 	if(strcmp(newl.code_livre,code_livre)==0){
		 	exister=1;
 			printf("\tle code du livre recherche est: %s\n",newl.code_livre);
 			printf("\tl\'auteur du livre est :%s \n",newl.auteur);
 			printf("\tle titre du livre est :%s \n",newl.titre);
 			printf("\tle nombre des exemplaires du livre est:%d \n",newl.nbr_exemplaires);
 			printf("\tle prix du livre est:%.2f \n",newl.prix);
 			 printf("\n\n");
		 }
		}
	}
	 fclose(f_in);
	 if(!exister){
		 printf("________le livre recherche n\'existe pas_________\n");
		  printf("\n\n");
		}
}
 else{
 	printf("il y a une erreur d\'ouverture du fichier des livres pour rechercher!!\n");
 }
  }

void Page_rechercher_livre(char *fich_pages,char*fich_livres,char*email){//nom_fich:fichier des pages
 FILE *p;
    Afficher_livre(fich_livres);
	char *lien,*c1,*c2,*c3;
	c3=NULL;
	c1=verifier_creation(11,fich_pages);
	c2=verifier_creation(1,fich_pages);
	if(c1!=NULL && c2!=NULL){
		c3=c2;
	};
	lien=verifier_creation(6,fich_pages);
 if(lien!=NULL){
		printf("_____votre page de rechercher le livre est deja cree ___________\n");
		printf("______Voici le lien pour acceder a la page rechercher <%s> :_____ \n\n",lien);
		goto label;
	  }	
     else{
     	lien=ajouter_page(6,email,fich_pages);
     	 printf("____la page a ete cree avec succes______\nVoici le lien pour acceder a la page rechercher: <%s>:\n",lien);
     	label:
     p=fopen(lien,"w");
     if(lien!=NULL){
     fprintf(p,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>rechercher un livre</title><link rel=\"stylesheet\" href=\"css/bootstrap.min.css\"><link rel=\"stylesheet\" href=\"css/tooplate-style.css\"><link rel=\"stylesheet\" href=\"styleForm.css\"> <link rel=\"stylesheet\" href=\"styleRechercher.css\">  </head><body><div id=\"tm-bg\"></div><div id=\"tm-wrap\"><div class=\"container tm-site-header-container\"><a target=\"_blank\" href=\"%s\">Acceuil</a><form id= \"searchbox\"><input name= \"q\"  type= \"text\"  size= \"15\" placeholder=\"Entrer le code du livre a rechercher\"  /><input id=\"button-submit\"  type=\"submit\"  value=\"rechercher\" /></form></div></div></div></div></body></html>",c3);
     fclose(p);
	 }
	 else{
	 	printf("erreur d\'ouverture du fichier!!!\n");
	 }
	 }
	  printf("\n\n");
}
 
 void gestion_livre(char *fich_pages,char *fich_livres,char *email,char*fich_emprunteur,char*emprunt){
	char choix;
	FILE *fp1=fopen(fich_livres,"a+");
	fclose(fp1);
	do{
		fflush(stdin);
	   choix=menu_livre();
	   switch(choix){
	   	 case 'a':fflush(stdin);
			Page_ajouter_livre(fich_pages,fich_livres,email,fich_emprunteur);
	   	 	break;
	   	 case 's':Page_supprimer_livre(fich_pages,fich_livres,email,emprunt,fich_emprunteur);
	   	 	fflush(stdin);
	   	 	
	   	 	break;
	   	case 'l':lister_livres(fich_pages,email,fich_livres);
	   		fflush(stdin);
	   	 
	   	 	break;
	   	case 'r':Page_rechercher_livre(fich_pages,fich_livres,email);
	   		fflush(stdin);
	   	 
	   	 	break;
	   	default:
		  printf("un choix invalide!!!\n");
	   }	
	}while(choix!='q');
}
 //**********************************************************************************************************************************

