#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include"projetC.h"



char* rechercher_fichier(int i,char *email,char *fich_admin){
	FILE*fp=fopen(fich_admin,"r+");
	Admin *u1=(Admin*)malloc(sizeof(Admin));
	if(fp!=NULL){
	 while(!feof(fp)){
		if(fscanf(fp,"%s  %s  %s  %s  %s  %s  %s  %s\n",u1->nom,u1->prenom,u1->email,u1->password,u1->fich_pages,u1->fich_livres,u1->fich_emprunt,u1->emprunt)!=-1){
			if(strcmp(email,u1->email)==0){
			 fclose(fp);
			 if(i==1){
			 	return u1->fich_pages;
			 }
			 else if(i==2){
			 	return u1->fich_livres;
			 }
			 else if(i==3){ 
			 return u1->fich_emprunt;
			 }
			 else{
			 	return u1->emprunt;
			 }
			 	
			}
		}	
	}	
 }
	else{
		printf("erreur d'ouvrir le fichier d\'admin!!!!\n");
	}
	return NULL;
}
//------------------------------Menu d'inscription||login------------------------------------------------------------------------
char menu(){
	printf("\n\n");
    printf("\t\t_________vous etes le bienvenue________\n\n");
    printf("\t\t tappez: <S> pour s\'inscrire\n\n");
    printf("\t\t tappez: <L> pour se connecter dans votre site\n\n");
     printf("\t\t Veuillez entrer votre choix:");
    return getchar();
}
//*************************************cryptage && decryptage**********************************************
void decryptage(char *T){
   int i;
      for(i=0;i<100;i++) {
        if(T[i]=='<')T[i]='a';
        if(T[i]==']')T[i]='b';
		if(T[i]=='Æ')T[i]='c';
		if(T[i]=='€')T[i]='d';
		if(T[i]=='ƒ')T[i]='e';
        if(T[i]=='†')T[i]='f';
        if(T[i]=='‡')T[i]='g';
        if(T[i]=='•')T[i]='h';
        if(T[i]=='—')T[i]='i';
        if(T[i]=='š')T[i]='j';
        if(T[i]=='¢')T[i]='k';
        if(T[i]=='£')T[i]='l';
        if(T[i]=='¤')T[i]='m';
        if(T[i]=='¥')T[i]='n';
        if(T[i]=='¦')T[i]='o';
        if(T[i]=='§')T[i]='p';
        if(T[i]=='¨')T[i]='q';
        if(T[i]=='¬')T[i]='r';
        if(T[i]=='«')T[i]='s';
        if(T[i]=='µ')T[i]='t';
        if(T[i]=='¶')T[i]='u';
        if(T[i]=='¿')T[i]='v';
        if(T[i]=='÷')T[i]='w';
        if(T[i]=='ß')T[i]='x';
        if(T[i]=='â')T[i]='y';
        if(T[i]=='ð')T[i]='z';
        if(T[i]=='ñ')T[i]='1';
        if(T[i]=='ø')T[i]='2';
        if(T[i]=='ý')T[i]='3';
        if(T[i]=='þ')T[i]='4';
        if(T[i]=='ÿ')T[i]='5';
        if(T[i]=='è')T[i]='6';
        if(T[i]=='*')T[i]='7';
        if(T[i]==':')T[i]='8';
        if(T[i]=='!')T[i]='9';
        if(T[i]=='^')T[i]='0';
      }
     // printf("\n%s\n",T);

}

void cryptage( char*T){
   int i;
   for(i=0;i<13;i++) {
      if(T[i]=='a')T[i]='<';
      if(T[i]=='b')T[i]=']';
      if(T[i]=='c')T[i]='Æ';
      if(T[i]=='d')T[i]='€';
      if(T[i]=='e') T[i]='ƒ';
      if(T[i]=='f')T[i]='†';
      if(T[i]=='g') T[i]='‡';
      if(T[i]=='h')T[i]='•';
      if(T[i]=='i')T[i]='—';
      if(T[i]=='j') T[i]='š';
      if(T[i]=='k') T[i]='¢';
      if(T[i]=='l')T[i]='£';
      if(T[i]=='m')T[i]='¤';
      if(T[i]=='n')T[i]='¥';
      if(T[i]=='o') T[i]='¦';
      if(T[i]=='p')T[i]='§';
      if(T[i]=='q') T[i]='¨';
      if(T[i]=='r')T[i]='¬';
      if(T[i]=='s') T[i]='«';
      if(T[i]=='t') T[i]='µ';
      if(T[i]=='u')T[i]='¶';
      if(T[i]=='v') T[i]='¿';
      if(T[i]=='w')T[i]='÷';
      if(T[i]=='x') T[i]='ß';
      if(T[i]=='y') T[i]='â';
      if(T[i]=='z')T[i]='ð';
      if(T[i]=='1') T[i]='ñ';
      if(T[i]=='2') T[i]='ø';
      if(T[i]=='3') T[i]='ý';
      if(T[i]=='4')T[i]='þ';
      if(T[i]=='5') T[i]='ÿ';
      if(T[i]=='6') T[i]='è';
      if(T[i]=='7') T[i]='*';
      if(T[i]=='8')T[i]=':';
      if(T[i]=='9')T[i]='!';
      if(T[i]=='0') T[i]='^';
       }
  
}
//***************************fonction d'ajout un nouveau admin******************************
void ajouter(char *nom_fichierAdmin,Admin *u1){
    FILE *fp;
    fp= fopen(nom_fichierAdmin,"a+");
    if(fp!=NULL){
      if(u1!=NULL){
        fprintf(fp,"%s  %s  %s  %s  %s  %s  %s  %s\n",u1->nom,u1->prenom,u1->email,u1->password,u1->fich_pages,u1->fich_livres,u1->fich_emprunt,u1->emprunt);
        printf("_________vous avez bienvenue ,votre info sont bien ajoutes_________\n");
         printf("\n\n");
		}
        else{
        	printf("________!!!erreur d\'ajout d\'admin!!!______\n");
		}
		 fclose(fp);
       }
       else{
       	printf("erreur d\'ouverture du fichier!!\n");
	   }	  
}
//****fonction pour verifier que l'email est unique pour chaque nouveau admin et pour verifier les info lors de l'eatpe de login******
char* rechercher_dans_fichier(char *email,char *nom_fichierAdmin){
    Admin *u1=(Admin*)malloc(sizeof(Admin));
    FILE *fp1=fopen(nom_fichierAdmin,"r+");
    if(fp1!=NULL){
        while(!feof(fp1)){
            if(fscanf(fp1,"%s  %s  %s  %s  %s  %s  %s  %s\n",u1->nom,u1->prenom,u1->email,u1->password,u1->fich_pages,u1->fich_livres,u1->fich_emprunt,u1->emprunt)!=-1){
			  if(strcmp(u1->email,email)==0){
                     fclose(fp1);
                     decryptage(u1->password);
                     return u1->password;
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
//****************inscription********************************************************
Admin* sign_in (char *nom_fichierAdmin){
    char pw[10];  
    int x=-1;  
    Admin *u=(Admin*)malloc(sizeof(Admin));
    char *valid;
    char*exister;
    	printf("____Veuillez entrer votre nom :____\n");
        gets(u->nom);
        printf("____Veuillez entrer votre prenom :____\n");
        gets(u->prenom);
        printf("____Veuillez entrer votre Email :____\n");
        place:
        gets(u->email);
        valid=strstr(u->email,"@gmail.com"); 
        exister=rechercher_dans_fichier(u->email,nom_fichierAdmin);
        if(valid==NULL){
         printf("____Veuilez saisir une adresse email invalide:!!!____\n");
		 goto place;	
		}
		else{
			if(exister!=NULL){
            printf("____Cet email existe deja. Veuilez saisir un autre:____\n");
            goto place;
        }
		}
        
        printf("____Veuillez entrer votre Password :____\n");
        while(pw[x]!=13 && pw[x]!=' '){
		x++;  
        pw[x] = getch(); 
        printf("*");
        
        } 
        pw[x]='\0';
		strcpy(u->password,pw);
        cryptage(u->password);
        strcat(strcpy(u->fich_pages,u->email),".txt");
        strcat(strcpy(u->fich_livres,u->email),"livres.txt");//ou on va stocker les livres de l'utilisateur
        strcat(strcpy(u->fich_emprunt,u->email),"emprunteur.txt");//ou on va stocker les empruteurs de l'utilisateur
        strcat(strcpy(u->emprunt,u->email),"emprunt.txt");
         printf("\n\n");
   return u;     
}
//*********************fonction login************************************************************************
char* login(char*nom_fichierAdmin){
	char pw[20];
	char c[20];
    char*var_rechercher;
    Admin *u=(Admin*)malloc(sizeof(Admin));
    int login;
   	do{
   	int x=-1;
   	login=1;
   	fflush(stdin);
   	printf("____Veuillez entrer votre Email :____\n");
   	gets(u->email);
   var_rechercher=rechercher_dans_fichier(u->email,nom_fichierAdmin);
   printf("____Veuillez entrer votre Password :____\n");
   fflush(stdin);
   while(pw[x]!=13 && pw[x]!=' '){
		x++;  
		fflush(stdin);
        pw[x] = getch(); 
        printf("*");
        } 
        pw[x]='\0';
		strcpy(u->password,pw); 
   if(var_rechercher==NULL){
   	printf("____veuillez reentrer vos info car ils sont invalides____\n");
   	login=0;
   }
   else{
   if(strcmp(var_rechercher,u->password)!=0){
   	login=0;
   	printf("____veuillez reentrer vos info car ils sont invalides____\n");
   	}
    }
   }while(login==0);
   printf("\n\n");
   return u->email;
}



//---------------------------Menu principal---------------------------------------------------------------------------------------
char menu_admin(){
    printf("\t**************Menu*****************\n");
    printf("\tA : Creer la page d\'accueil.\n");
    printf("\tB : Creer la page d\'authentification de votre site\n");
    printf("\tL : Gestion des Livres\n");
    printf("\tE : Gestion des emprunteurs\n");
    printf("\tI : Importer un fichier html 1\n");
    printf("\tP : Gestion des liens entre les pages web.\n");
    printf("\tQ : Quitter\n");
    printf("\tVeuillez entrer votre choix:\n");
    return getchar();
}


