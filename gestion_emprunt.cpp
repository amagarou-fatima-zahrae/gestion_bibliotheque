#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include"projetC.h"


//****************************fonctions pour gerer les emprunteurs*****************************
void Ajouter_Emprunteur(char *fich_emprunteur,Emprunteur *e ){
	FILE *fp=fopen(fich_emprunteur,"a+");
	if(fp!=NULL){
	fprintf(fp,"%s  %s  %s  %d\n",e->nom,e->prenom,e->email,e->nbr_livres_emp);
	 fclose(fp);
	}
	else{
		printf("erreur d\'ouverture du fichier pour ajouter l\'emprunteur!!!\n");
	}
}
 
char menu_emprunteur(){
 printf("\n\n");
printf("______ajouter un Emprunteur ______ a\n") ; 
printf("_______supprimer un Emprunteur ______s\n") ;
printf("_______ lister les Emprunteurs________ l\n") ;	
printf("_______ rechercher un Emprunteur________ r\n") ;
printf("_______quitter ______q\n") ; 
printf("_______veuillez entrer votre choix:_________\n");
return getchar();	
}
char* verifier_emprunteur(int i,char *email,char *fich_emprunteur){
	char nbrStr[5];
   Emprunteur *e=(Emprunteur*)malloc(sizeof(Emprunteur));
    FILE *fp1=fopen(fich_emprunteur,"r+");
    if(fp1!=NULL){
        while(!feof(fp1)){
            if(fscanf(fp1,"%s  %s  %s  %d\n",e->nom,e->prenom,e->email,&e->nbr_livres_emp)!=-1){
              if(strcmp(e->email,email)==0){
                    fclose(fp1);
                    switch(i){
                      case 1:{
                    	return e->nom;
						break;
					    }
					  case 2:{
					 	sprintf(nbrStr,"%d", e->nbr_livres_emp);
						return nbrStr;
						break;
					  }	
					}
                    
                }
            }
        }
        fclose(fp1);
    }
    else{
	printf("une erreur d'ouverture des fichier \n");
	}
    return NULL;
}
 
 
char menu_emprunt(){
	 printf("\n\n");
  printf("_______________Vous voulez ajouter:_____________\n");
  printf("\t__Tappez N pour un \"nouveau emprunteur\"\n");
  printf("\t__Tappez E pour emprunter un autre livre pour un emprunteur deja existe \n");
  fflush(stdin);
  printf("________Veuillez entrer votre choix________\n");
  getchar();
}

void verifier_livre(int signe,char *fich_livres,char *fich_emprunteur,char *emprunt,Emprunteur *e,char *email){
	 int resultat;
	 char code[20];
	fflush(stdin);
	indice:
    printf("________veuillez entrer le code du livre que l\'emprunteur veut empreinter\n");
    scanf("%s",code);
    resultat=rechercher_livre(code,fich_livres);
    if(resultat!=-1 && resultat!=0){
      	 if(signe==1){
      			e->nbr_livres_emp=1;
		  }
		 else{
		 modifier(2,code,fich_livres,email,fich_emprunteur);
		}
        FILE *fp=fopen(emprunt,"a+");
        if(fp!=NULL){
     	modifier(1,code,fich_livres,email,fich_emprunteur);
        fprintf(fp,"%s  %s\n",code,email);
        fclose(fp);
	    }
	    else{
	 	  printf("erreur d\'ouverture le fichier des emprunts!!!\n");
	    }
   }
   else if(resultat==-1){
     	printf("<<<<le livre n\'existe pas!!!>>>>\n");
     	goto indice;
	}
	else{
	 	printf("<<<<tous les exemplaires de ce livre ont ete deja empruntes (ou) supprimes!!!>>>>\n");
	 	goto indice;
	}
}
Emprunteur* Saisir_Emprunt(char *fich_emprunteur ,char *emprunt,char *fich_livres){
	char choix;
	char *exister,*nb_livre_emprunt,*valid;
	int nbr;
	Emprunteur *e=(Emprunteur*)malloc(sizeof(Emprunteur));
do{
   indice:
   choix=menu_emprunt();
	switch(choix){
		case 'N':{
		fflush(stdin);
     printf("______entrer le nom du Emprunteur \n");
     scanf("%s",e->nom);
     fflush(stdin);
     printf("______entrer le prenom du Emprunteur \n");
     scanf("%s",e->prenom);
     fflush(stdin);
     printf("______entrer l\'email du Emprunteur \n");
     place:
     scanf("%s",e->email);
     valid=strstr(e->email,"@gmail.com");
     exister=verifier_emprunteur(1,e->email,fich_emprunteur);
    if(valid==NULL){
         printf("______Veuilez saisir une adresse email valide:!!!\n");
		 goto place;	
		}
	else{
      if(exister!=NULL){
        printf("______Cet email existe deja. Veuilez saisir un autre:\n");
        goto place;
        }
  }
    verifier_livre(1,fich_livres,fich_emprunteur,emprunt,e,e->email);
    return e;
			break;
		}
		case 'E':{
				do{
   	     nbr=1;
   	     fflush(stdin);
       	 printf("______entrer l\'email du Emprunteur :\n");
   	     gets(e->email);
   	     exister=verifier_emprunteur(1,e->email,fich_emprunteur);
   	     fflush(stdin);
         printf("______entrer le nom du Emprunteur \n");
         gets(e->nom);
        if(exister==NULL){
   	    printf("______veuillez reentrer vos info car ils sont invalides\n");
   	    nbr=0;
         }
        else{
         if(strcmp(exister,e->nom)!=0){  
   	     nbr=0;
   	     printf("______veuillez reentrer vos info car ils sont invalides\n");
   	     }
        }
   }while(nbr==0);
   nb_livre_emprunt=verifier_emprunteur(2,e->email,fich_emprunteur);
   nbr=atoi(nb_livre_emprunt);
    if(nbr==3){
   	printf("<<<<<<<cet emprunteur ne peut pas emprunter plus car il a atteint le nombre max 3!!!>>>>>>>\n");
   	goto indice;
    }
    else{ 
     verifier_livre(2,fich_livres,fich_emprunteur,emprunt,NULL,e->email);
     return NULL;
	}
		break;
 }
}
}while(choix!='E' && choix!='N');
}   
void Page_ajouter_emprunt(char *fich_pages,char *fich_emprunteurs,char*emprunt,char*email,char *fich_livres){//nom_fich:fichier des pages
	FILE *p;
	Emprunteur *e= Saisir_Emprunt(fich_emprunteurs ,emprunt,fich_livres);
		if(e!=NULL){
		Ajouter_Emprunteur(fich_emprunteurs,e);
	}

	char *lien,*c1,*c2,*c3;
	c3=NULL;
	lien=verifier_creation(7,fich_pages);
	c1=verifier_creation(11,fich_pages);
	c2=verifier_creation(1,fich_pages);
	if(c1!=NULL && c2!=NULL){
		c3=c2;
	}
 if(lien!=NULL){
		printf("_____votre page d\'ajouter l\'emprunteur  est deja cree \n______et les info du emprunteur ont ete bien ajoutes\n");
		printf("______Voici le lien pour acceder a la page ajouter <%s> :______ \n",lien);
		goto label;
	  }	
else{
     lien=ajouter_page(7,email,fich_pages);
     printf("____la page a ete cree avec succes______\n______et les info du emprunteur ont ete bien ajoutes dans la page lister\n______Voici le lien pour acceder a la page ajouter: <%s>:\n",lien);
     label:
	 p=fopen(lien,"w");
     if(lien!=NULL){
     fprintf(p,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Ajouter Emprunteur</title><link rel=\"stylesheet\" href=\"css/tooplate-style.css\"><link rel=\"stylesheet\" href=\"styleForm.css\"><link rel=\"stylesheet\" href=\"styleRechercher.css\"></head><body><div id=\"tm-bg\"></div><div id=\"tm-wrap\"><a target=\"_blank\"  href=\"%s\">Acceuil</a><div class=\"card-body\"><h2 class=\"title\">Ajouter un Emprunteur</h2><form method=\"POST\"><div class=\"input-group\"><input class=\"input--style-1\" type=\"text\" placeholder=\"nom de l\'emprunteur\" name=\"name\"></div><div class=\"input-group\"><input class=\"input--style-1\" type=\"text\" placeholder=\"prenom de l\'emprunteur\" name=\"name\"></div><div class=\"input-group\"><input class=\"input--style-1\" type=\"text\" placeholder=\"email de l\'emprunteur\" name=\"name\"></div><div class=\"input-group\"><input class=\"input--style-1\" type=\"text\" placeholder=\"Nombre livres empruntes\" name=\"name\"></div><div class=\"p-t-20\"><button class=\"btn btn--radius btn--green\" type=\"submit\">Submit</button></div></form></div></body></html>",c3);
     
     fclose(p);
	 }
	 else{
	 	printf("erreur d\'ouverture du fichier!!!\n");
	 }
	 }
	  printf("\n\n");
}
int supprimer_emprunt(char *email,char *code,char*emprunt){
	int seul=0;
 	FILE *f_in=fopen(emprunt,"r");
 	FILE *f_out=fopen("supprimer.txt","w");
 	if(f_in!=NULL && f_out!=NULL){
 	 Emprunt *em=(Emprunt*)malloc(sizeof(Emprunt));
		while(!feof(f_in)){
		 if(fscanf(f_in,"%s  %s\n",em->code_livre,em->email)!=-1){
		 	if(((strcmp(em->code_livre,code)!=0) || (strcmp(em->email,email)!=0))|| (seul==1) ){
		     fprintf(f_out,"%s  %s\n",em->code_livre,em->email);
		 }
		 else{
		 	seul=1;
		 }
		}
      }	
	  	 fclose(f_in);
		 fclose(f_out);
		 remove(emprunt);
		 rename("supprimer.txt",emprunt);
		 if(seul){
		 printf("<<<<<la suppression de l\'empreinte(exemplaire du livre) est reussie>>>>>\n");
		 return 1;
		}
		else{
			printf("______ce livre n\'existe pas!!!! (ou) ce livre n\'est pas emprunte par cet emprunteur!!______\n");//ou ce livre nest pas emprunter par ce emrunteur
		}
		 
	 }
	 else{
	 	printf("______une erreur d\'ouverture du fichier des emprunts!!!!\n");
	 }
	 return 0;
 }
void supprimer_tot(char *email,char *fich_livres,char *fich_emprunteurs,char*emprunt){
	FILE *f=fopen(emprunt,"r");
 	FILE *f_in=fopen(fich_emprunteurs,"r");
 	FILE *f_out=fopen("supprimer.txt","w");
 	FILE *fq=fopen("delete.txt","w");
 	if(f_in!=NULL && f_out!=NULL && f!=NULL && fq!=NULL){
 		Emprunteur *e=(Emprunteur*)malloc(sizeof(Emprunteur));
 		while(!feof(f_in)){
		 if(fscanf(f_in,"%s  %s  %s  %d\n",e->nom,e->prenom,e->email,&e->nbr_livres_emp)!=-1){
		 	if(strcmp(e->email,email)!=0){
		 fprintf(f_out,"%s  %s  %s  %d  \n",e->nom,e->prenom,e->email,e->nbr_livres_emp);
		 }
		 else{
		 Emprunt *em=(Emprunt*)malloc(sizeof(Emprunt));
		 while(!feof(f)){
		 if(fscanf(f,"%s  %s\n",em->code_livre,em->email)!=-1){
		 	if(strcmp(em->email,email)!=0){
		    fprintf(fq,"%s  %s\n",em->code_livre,em->email);
		  }
		  else{
		  	modifier(4,em->code_livre,fich_livres,em->email,fich_emprunteurs);
		  }
		}
      }	
	}
}
}
	  	fclose(f_in);
		 fclose(f_out);
		 remove(fich_emprunteurs);
		 rename("supprimer.txt",fich_emprunteurs);
		 fclose(f);
		 fclose(fq);
		 remove(emprunt);
		 rename("delete.txt",emprunt);
	
	 }
 }
void Page_supprimer_emprunt(char *fich_pages,char *fich_livres,char *fich_emprunteurs,char*emprunt,char*email){//nom_fich:fichier des pages
 FILE *p;
 int nbr,n,i=0,j=0;
 char*verifier;
 char email_emp[20];
 essayer:
 printf("______veuillez entrer l\'email du emprunteur que vous voulez supprimer:______\n");
 scanf("%s",email_emp);
 verifier=verifier_emprunteur(2,email_emp,fich_emprunteurs);
 if(verifier==NULL){
 	printf("______Cet empreinteur n\'existe pas!!!! \nEssayer une autre fois!!______\n");
 	goto essayer;
 }
else{
  nbr=atoi(verifier);
  printf("______Voici le nombre de livres que cet emprunteur a empreinte: <%d> ______\n",nbr);
  do{
  printf("______Combien de livres cet emprunteur va retourner?______");
  scanf("%d",&n);
  }while(n<=0 || n>nbr);
  if((nbr-n)==0){
 	supprimer_tot(email_emp,fich_livres,fich_emprunteurs,emprunt);
 	printf("______cet empreinteur a retourne tous les livres ===>il ete supprime definitivement______ \n");
   }
   else{
 	do{
 	char code[20];
	printf("______veuillez entrer le code du livre numero %d que vous voulez retourner:______\n",i+1);
	scanf("%s",code);
     if(supprimer_emprunt(email_emp,code,emprunt)){
	modifier(3,code,fich_livres,email_emp,fich_emprunteurs);
	modifier(4,code,fich_livres,email_emp,fich_emprunteurs);	
    i++;
  }
	 else{
		printf("______Le code du livre que vous avez entrer n\'est pas correcte______\n");
	}
		
	}while(i<n);
	printf("______cet empreinteur a retourne %d livre(s) ===>il le reste %d livre(s)______ \n",n,nbr-n);
 }
 
	char *lien,*c1,*c2,*c3;
	c3=NULL;
	c1=verifier_creation(11,fich_pages);
	c2=verifier_creation(1,fich_pages);
	if(c1!=NULL && c2!=NULL){
		c3=c2;
	}
	lien=verifier_creation(9,fich_pages);
    if(lien!=NULL){
		printf("_____votre page de supprimer l\'empreinteur  est deja cree \n______et les info du empreinteur  ont ete bien supprimes\n");
		printf("______Voici le lien pour acceder a la page supprimer <%s> :______ \n",lien);
		goto label;
	  }	
     else{
     lien=ajouter_page(9,email,fich_pages);
      printf("____la page supprimer un empreinteur  a ete cree avec succes______\n______et les info du empreinteur  ont ete bien supprimes dans la page lister\n______Voici le lien pour acceder a la page supprimer: <%s>:\n",lien);
     label:
	 p=fopen(lien,"w");
     if(lien!=NULL){
     fprintf(p,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>supprimer emprunteur</title><link rel=\"stylesheet\" href=\"css/tooplate-style.css\">   <link rel=\"stylesheet\" href=\"styleForm.css\"> <link rel=\"stylesheet\" href=\"styleRechercher.css\"></head><body><div id=\"tm-bg\"></div><div id=\"tm-wrap\"><a target=\"_blank\" href=\"%s\">Acceuil</a><div class=\"card-body\"><h2 class=\"title\">Supprimer un emprunteur</h2><form method=\"POST\"><div class=\"input-group\"><input class=\"input--style-1\" type=\"text\" placeholder=\"Email de l'emprunteur\" name=\"name\"></div><div class=\"input-group\"><input class=\"input--style-1\" type=\"text\" placeholder=\"Code du livre a emprunte\" name=\"name\"></div><div class=\"input-group\"><div class=\"p-t-20\"><button class=\"btn btn--radius btn--green\" type=\"submit\">Submit</button></div></form></div></body></html>",c3);
     fclose(p);
	 }
	 else{
	 	printf("erreur d\'ouverture du fichier!!!\n");
	 }
	 }
}
 printf("\n\n");
 }
   int lister_emprunt(char *nom_fich,char *email,char *fich_emprunt,char *emprunt){
   FILE *fp,*fq,*f;
	char *lien,*c1,*c2,*c3;
	c3=NULL;
	c1=verifier_creation(11,nom_fich);
	c2=verifier_creation(1,nom_fich);
	if(c1!=NULL && c2!=NULL){
		c3=c2;
	}
	lien=verifier_creation(8,nom_fich);
	if(lien!=NULL){
		printf("_____votre page de lister les emprunteurs est deja cree\ntoutes les mises a jour sont faites\n ");
		printf("______Voici le lien pour acceder a la page et visualiser les emprunteurs<%s>:\n",lien);
		lieu:
		fq=fopen(fich_emprunt,"r");
		f=fopen(emprunt,"r");
	  if(fq!=NULL && f!=NULL){
	 	fp=fopen(lien,"w");
	 	if(fp!=NULL){
	 	fprintf(fp,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\"content=\"width=device-width,initial-scale=1\"><title>Liste des emprunteurs & emprunts</title><link rel=\"stylesheet\"href=\"css/bootstrap.min.css\"><link rel=\"stylesheet\"href=\"css/tooplate-style.css\"><link rel=\"stylesheet\"href=\"lister.css\"></head><body><div id=\"tm-bg\"></div><div id=\"tm-wrap\"><div class=\"card-body\"><!--HEEERE--><a target=\"_blank\" href=\"%s\">Acceuil</a><h1> liste des emprunteurs </h1><table><tr><th scope=\"col\">NOM de l\'emprunteur</th><th scope=\"col\">Prenom de l\'emprunteu</th><th scope=\"col\">Email de l\'emprunteu</th><th scope=\"col\">Nombre de livres Empruntes</th></tr>",c3);
  	    Emprunteur *e=(Emprunteur*)malloc(sizeof(Emprunteur));
  		while(!feof(fq)){
  		if(fscanf(fq,"%s  %s  %s  %d\n",e->nom,e->prenom,e->email,&e->nbr_livres_emp)!=-1){
		fprintf(fp,"<tr><th scope=\"row\">%s</th><td>%s</td><td>%s</td><td style=\"color:white;font-weight: bolder;font-size: 1.5rem;\">%d</td></tr>\n",e->nom,e->prenom,e->email,e->nbr_livres_emp);
         }	
	 }
      fprintf(fp,"</table></div>\n<br><br><br>\n");
     Emprunt *em=(Emprunt*)malloc(sizeof(Emprunt));
      fprintf(fp,"<div id=\"tm-bg\"></div><div id=\"tm-wrap\"><div class=\"card-body\"><h1> liste des empruntes </h1><table><tr><th scope=\"col\">le code du livre empreinte</th><th scope=\"col\">Email de l\'emprunteur</th></tr>\n");
      while(!feof(f)){
  		if(fscanf(f,"%s  %s\n",em->code_livre,em->email)!=-1){
		fprintf(fp,"<tr><th scope=\"row\" style=\"color:white;font-weight: bolder;font-size: 1.5rem;\">%s</th><td >%s</td></tr>\n",em->code_livre,em->email);
         }	
	 }
   fprintf(fp,"</table></div>\n</body></html>\n");
   fclose(fp);
   }
   else{
   	printf("erreur d\'ouverture le fichier html de lister!!\n");
   }
    fclose(f);
	fclose(fq);
	return 0;
	}
	else{
   	printf("______erreur d\'ouverture le fichier des emprunteurs ou des empreintes!!\n");
   } 
}
	else{
  lien=ajouter_page(8,email,nom_fich);
  printf("____la page lister les emprunteurs a ete cree avec succes______\n______Voici le lien pour acceder a la page et visualiser les emprunteurs: <%s>:\n",lien);
  goto lieu;
  
  }
	 fclose(fp);
	  printf("\n\n");
	 return 0;	
} 
void Afficher_emprunt(char *fich_emprunteur){
	int exister=0;
 	char email[20];
	printf("______veuillez entrer l\'email de l\'empreinteur que vous voulez rechercher:______\n");
	scanf("%s",email);
 	FILE *f_in=fopen(fich_emprunteur,"r");
 	 if(f_in!=NULL){
      Emprunteur *e=(Emprunteur*)malloc(sizeof(Emprunteur));
 		while(!feof(f_in)){
		 if(fscanf(f_in,"%s  %s  %s  %d\n",e->nom,e->prenom,e->email,&e->nbr_livres_emp)!=-1){
		 	if(strcmp(e->email,email)==0){
		 	exister=1;
		 	printf("\tle nom de l\'empreinteur est :%s \n",e->nom);
 			printf("\tle prenonm de l\'empreinteur est :%s \n",e->prenom);
 			printf("\tl\'email de l\'empreinteur recherche est: %s\n",e->email);
 			printf("\tle nombre de livres que l\'empreinteur a empreintes est:%d \n",e->nbr_livres_emp);
 		
		 }
		}
	}
	 fclose(f_in);
	 if(!exister){
		 printf("______l\'emprunteur recherche n\'existe pas______\n");
		}
}
 else{
 	printf("______il y a une erreur d\'ouverture du fichier des emprunteurs pour rechercher!!______\n");
 }
  printf("\n\n");
}

void Page_rechercher_emprunt(char *fich_pages,char*fich_emprunt,char*email){//nom_fich:fichier des pages
    FILE *p;
    Afficher_emprunt(fich_emprunt);
    char *lien,*c1,*c2,*c3;
	c3=NULL;
	c1=verifier_creation(11,fich_pages);
	c2=verifier_creation(1,fich_pages);
	if(c1!=NULL && c2!=NULL){
		c3=c2;
	}
	lien=verifier_creation(10,fich_pages);
 if(lien!=NULL){
		printf("_____votre page de rechercher l\'emprunteur est deja cree ___________\n");
		printf("____Voici le lien pour acceder a la page rechercher <%s> :_____ \n",lien);
		goto label;
	  }	
     else
     lien=ajouter_page(10,email,fich_pages);
      printf("____la page a ete cree avec succes______\n________Voici le lien pour acceder a la page rechercher: <%s>:\n",lien);
      label:
	  p=fopen(lien,"w");
     if(lien!=NULL){
     fprintf(p,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Rechercher emprunteur</title><link rel=\"stylesheet\" href=\"css/tooplate-style.css\">   <link rel=\"stylesheet\" href=\"styleForm.css\"> <link rel=\"stylesheet\" href=\"styleRechercher.css\"></head><body><div id=\"tm-bg\"></div><div id=\"tm-wrap\"><a target=\"_blank\" href=\"%s\">Acceuil</a><div class=\"card-body\"><h2 class=\"title\">Rechercher un emprunteur</h2><form method=\"POST\"><div class=\"input-group\"><input class=\"input--style-1\" type=\"text\" placeholder=\"Email de l'emprunteur\" name=\"name\"></div><div class=\"input-group\"><div class=\"p-t-20\"><button class=\"btn btn--radius btn--green\" type=\"submit\">Submit</button></div></form></div></body></html>",c3);
      fclose(p);
	 }
	 else{
	 	printf("erreur d\'ouverture du fichier!!!\n");
	 }
	  printf("\n\n");
	 }
	 
void gestion_emprunt(char *fich_pages,char *fich_emprunteurs,char *fich_emprunt,char *fich_livres,char *email){
	char choix;
	FILE *fp1=fopen(fich_emprunteurs,"a+");
	fclose(fp1);
	do{
		fflush(stdin);
	   choix=menu_emprunteur();
	   switch(choix){
	   	 case 'a':fflush(stdin);
			Page_ajouter_emprunt(fich_pages,fich_emprunteurs,fich_emprunt,email,fich_livres);
	   	 	break;
	   	 case 's':
	   	 	fflush(stdin);
	   	 	Page_supprimer_emprunt(fich_pages,fich_livres,fich_emprunteurs,fich_emprunt,email);
	   	 	break;
	   	case 'l':
	   		fflush(stdin);
	   	 lister_emprunt(fich_pages,email,fich_emprunteurs,fich_emprunt);
	   	 	break;
	   	case 'r':
	   		fflush(stdin);
	   	 Page_rechercher_emprunt(fich_pages,fich_emprunteurs,email);
	   	 	break;
	   	default:
		  printf("______un choix invalide!!!______\n");
	   }	
	}while(choix!='q');
}
 //************************************************************************************************************************************


