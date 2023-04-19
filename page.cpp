#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include"projetC.h"

char* verifier_creation(int i,char *nom_fich){
	FILE *fq=fopen(nom_fich,"a+");
	Page_Html *Pg=(Page_Html*)malloc(sizeof(Page_Html));
	if(fq!=NULL){
	 while(!feof(fq)){
	  	if(fscanf(fq,"%d %s\n",&Pg->n_page,Pg->lien)!=-1){
		 	if(Pg->n_page==i){
		 	fclose(fq);
		 	return Pg->lien;
		 }
		}	
	}
	fclose(fq);
  }
	else{
		printf("erreur d\'ouverture du fichier!!! (verif)\n");
	}
return NULL;
}
//--------------------------------------------------------------------------------
char * ajouter_page(int numero,char *email,char *fich_pages){
	FILE *fp=fopen(fich_pages,"a+");
	Page_Html *p=(Page_Html*)malloc(sizeof(Page_Html*));
	char lien[50];
	char* num;
	asprintf(&num,"%d",numero);
   if(fp!=NULL){
	    p->n_page=numero;
		strcat(strcat(strcpy(p->lien,email),num),".html");
		fprintf(fp,"%d %s\n",p->n_page,p->lien);
	    fclose(fp);	
	    return p->lien;
	}
	else{
	 	printf("erreur d\'ouverture du fichier (ajouter)!!!\n");	
	}
	return NULL;
}
//***************** Pge authentif***********************************************************
char menu_front(){
	printf("\t\ta : modifier la couleur de fond\n");
    printf("\t\tb : modifier la couleur de police \n");
    printf("\t\tc : modifier la taille de police \n");
    printf("\t\tq : Quitter\n");
    printf("\t\tVeuillez entrer votre choix:\n");
    return getchar();
}
void creer_pageAuthentif(char *fich_pages,char *email){
   char*trouver,*lien;
   char*c1,*c2,*c3;
   c3=NULL;
   char reponse,choix1;
   char choix2[12]="#",choix3[12]="#",choix4[12]="#";
    trouver=verifier_creation(2,fich_pages);//rechercherPageCree();
   	c1=verifier_creation(1,fich_pages);
   	c2=verifier_creation(11,fich_pages);
   	if(c1!=NULL && c2!=NULL){
	  c3=c1 ;
   }
   if(trouver!=NULL){
        printf("_____votre page est deja cree !__________\n");
        printf("-----Voici son lien pour la consulter : <%s>-----\n",trouver);
        fflush(stdin);
        printf("-----vous voulez faire des modifications sur la page o|n:-----\n\n");
		scanf("%c",&reponse);
		if(reponse=='n'){
			printf("____Bienvenue bonne consultation_________ \n");
			lien=trouver;
			goto label;
		}
      else{
		do{
	printf("-----quelle critere vous voulez modifier?-----\n");
	fflush(stdin);
	choix1=menu_front();	
  	switch(choix1){
  		case 'a':{
  			FILE *fic=fopen(trouver,"w+");
  			fflush(stdin);
  			printf("-----veuillez entrer la couleur du fond:-----\n");
  			gets(choix2);
  			fprintf(fic,"<html>\n<head>\n<meta charset=\"utf-8\">\n<link rel=\"stylesheet\" href=\"style.css\"/>\n</head>\n<body style=\"background-color:%s ;\">\n<div id=\"container\"> \n<center><a style=\"text-decoration: none;\" target=\"_blank\" href=\"%s\"><h1 style=\"color:%s;font-weight:bolder;\">Accueil</h1></a></center><form>\n<h1 style=\"color:%s;font-size:%s;\">Connexion</h1>\n<label style=\"color:%s;font-size:%s;\"><b>Email</b></label>\n<input type=\"text\" placeholder=\"Entrer l\'email'\" name=\"username\" required>\n<label style=\"color:%s;font-size:%s;\"><b>Mot de passe</b></label>\n<input type=\"password\" placeholder=\"Entrer le mot de passe\" name=\"password\" required>\n<input type=\"submit\" id=\'submit\' value=\'LOGIN\' >\n</form>\n</div>\n</body>\n</html>",choix2,c3,choix3,choix3,choix4,choix3,choix4,choix3,choix4);
  			fclose(fic);
			  break;
  		}
  		case 'b':{
  			FILE *fic=fopen(trouver,"w+");
  			fflush(stdin);
		  printf("-----veuillez entrer la couleur du police:-----\n");
  			gets(choix3);
  			fprintf(fic,"<html>\n<head>\n<meta charset=\"utf-8\">\n<link rel=\"stylesheet\" href=\"style.css\"/>\n</head>\n<body style=\"background-color:%s ;\">\n<div id=\"container\"> \n<center><a style=\"text-decoration: none;\" target=\"_blank\" href=\"%s\"><h1 style=\"color:%s;font-weight:bolder;\">Accueil</h1></a></center><form>\n<h1 style=\"color:%s;font-size:%s;\">Connexion</h1>\n<label style=\"color:%s;font-size:%s;\"><b>Email</b></label>\n<input type=\"text\" placeholder=\"Entrer l\'email\" name=\"username\" required>\n<label style=\"color:%s;font-size:%s;\"><b>Mot de passe</b></label>\n<input type=\"password\" placeholder=\"Entrer le mot de passe\" name=\"password\" required>\n<input type=\"submit\" id=\'submit\' value=\'LOGIN\' >\n</form>\n</div>\n</body>\n</html>",choix2,c3,choix3,choix3,choix4,choix3,choix4,choix3,choix4);
  		    fclose(fic);
			  break;}
  		case 'c':{
  			FILE *fic=fopen(trouver,"w+");
  			fflush(stdin);
  			printf("-----veuillez entrer la taille du police en <rem>:-----\n");
  			gets(choix4);
  			fprintf(fic,"<html>\n<head>\n<meta charset=\"utf-8\">\n<link rel=\"stylesheet\" href=\"style.css\"/>\n</head>\n<body style=\"background-color:%s ;\">\n<div id=\"container\"> \n<center><a style=\"text-decoration: none;\" target=\"_blank\" href=\"%s\"><h1 style=\"color:%s;font-weight:bolder;\">Accueil</h1></a></center><form>\n<h1 style=\"color:%s;font-size:%s;\">Connexion</h1>\n<label style=\"color:%s;font-size:%s;\"><b>Email</b></label>\n<input type=\"text\" placeholder=\"Entrer l\'email\" name=\"username\" required>\n<label style=\"color:%s;font-size:%s;\"><b>Mot de passe</b></label>\n<input type=\"password\" placeholder=\"Entrer le mot de passe\" name=\"password\" required>\n<input type=\"submit\" id=\'submit\' value=\'LOGIN\' >\n</form>\n</div>\n</body>\n</html>",choix2,c3,choix3,choix3,choix4,choix3,choix4,choix3,choix4);
  			fclose(fic);
			  break;}
  		default:
		  printf("-----un choix invalide!!!-----\n");
	 }	
	}while(choix1!='q');
  }
    }
   else {
         lien=ajouter_page(2,email,fich_pages);
         label:
         FILE *fic=fopen(lien,"w+");
         fprintf(fic,"<html>\n<head>\n<meta charset=\"utf-8\">\n<link rel=\"stylesheet\" href=\"style.css\"/>\n</head>\n<body >\n<div id=\"container\"> \n<form>\n<center><a style=\"text-decoration: none;\" target=\"_blank\" href=\"%s\"><h1 style=\"color:black;font-weight:bolder;\">Accueil</h1></a></center><h1>Connexion</h1>\n<label><b>Email</b></label>\n<input type=\"text\" placeholder=\"Entrer l\'email\" name=\"username\" required>\n<label><b>Mot de passe</b></label>\n<input type=\"password\" placeholder=\"Entrer le mot de passe\" name=\"password\" required>\n<input type=\"submit\" id=\'submit\' value=\'LOGIN\' >\n</form>\n</div>\n</body>\n</html>",c3);
         fflush(stdin);
         printf("Votre page d'authentification est bien cree\n");
         printf("Voici son lien pour la consulter : <%s>\n",lien);
         fclose(fic);
}
    }
 //*******************page Accueil*********************************************************************************
 void pageAccueil(char *fich_pages,char *email){//nom_fich:fichier des pages
 char *trouver,*lien;
 lien=verifier_creation(1,fich_pages);//rechercherPageCree();
   if(lien!=NULL){
   	    printf("___________________votre page est deja cree !__________\n");
	    printf("_________Touts les liens des pages deja crees ont ete bien ajoutes__________\n");
	    label:
   	FILE *fic=fopen(lien,"w+");
   	    fprintf(fic,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Project C</title><link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/css?family=Open+Sans:300\">  <!-- Google web font \"Open Sans\" --><link rel=\"stylesheet\" href=\"css/bootstrap.min.css\">  <!-- https://getbootstrap.com/ --><link rel=\"stylesheet\" href=\"fontawesome/css/fontawesome-all.min.css\"><link rel=\"stylesheet\" href=\"css/tooplate-style.css\"><link rel=\"stylesheet\" href=\"styleForm.css\"> <!-- Templatemo style --><link rel=\"stylesheet\" href=\"styleRechercher.css\"><script>document.documentElement.className=\"js\";var supportsCssVars=function(){var e,t=document.createElement(\"style\");return t.innerHTML=\"root: { --tmp-var: bold; }\",document.head.appendChild(t),e=!!(window.CSS&&window.CSS.supports&&window.CSS.supports(\"font-weight\",\"var(--tmp-var)\")),t.parentNode.removeChild(t),e};supportsCssVars()||alert(\"Please view this in a modern browser such as latest version of Chrome or Microsoft Edge.\");</script></head><body><div id=\"tm-bg\"></div><div id=\"tm-wrap\"><div class=\"tm-main-content\">");
		trouver=verifier_creation(2,fich_pages);
		fprintf(fic,"  <center><a target=\"_blank\"  href=\"%s\"><h1 style=\"color:white;font-weight:bolder;\">Authentification</h1></a></center>",trouver); 
   		fprintf(fic," <div class=\"container tm-site-header-container\"><div class=\"row\"><div class=\"col-sm-12 col-md-6 col-lg-6 col-md-col-xl-6 mb-md-0 mb-sm-4 mb-4 tm-site-header-col\"><div class=\"tm-site-header\"><h1 class=\"mb-4\">Gestion des LIVRES</h1><img src=\"img/underline.png\" class=\"img-fluid mb-4\"></div></div><div class=\"col-sm-24 col-md-6 col-md-6 col-lg-12 col-xl-12\"><div class=\"content\"><div class=\"grid\"><div class=\"grid_item\" id=\"home-link\"><div class=\"product\"><div class=\"tm-nav-link\"><i class=\"fas fa-home fa-3x tm-nav-icon\"></i><span class=\"tm-nav-text\">Ajouter un livre</span><div class=\"productbg\"></div></div><div class=\"productdescription\">");
		trouver=verifier_creation(3,fich_pages);
		fprintf(fic,"<a target=\"_blank\" href=\"%s\">Ajouter un livre</a>",trouver);
		fprintf(fic,"</div></div></div><div class=\"griditem\" id=\"team-link\"><div class=\"product\"><div class=\"tm-nav-link\"><i class=\"fas fa-users fa-3x tm-nav-icon\"></i><span class=\"tm-nav-text\">Lister les livres</span><div class=\"productbg\"></div></div><div class=\"productdescription\">");
		trouver=verifier_creation(4,fich_pages);
		fprintf(fic,"<a target=\"_blank\" href=\"%s\">Liste des livres</a>",trouver);
		fprintf(fic,"</div></div></div><div class=\"griditem\"><div class=\"product\"><div class=\"tm-nav-link\"><i class=\"fas fa-handshake fa-3x tm-nav-icon\"></i><span class=\"tm-nav-text\">Supprimer un livre</span><div class=\"productbg\"></div></div><div class=\"productdescription\">");
		trouver=verifier_creation(5,fich_pages);
		fprintf(fic,"<a target=\"_blank\"  href=\"%s\">Supprimer un livre</a>",trouver);
		fprintf(fic,"</div></div></div><div class=\"griditem\"><div class=\"product\"><div class=\"tm-nav-link\"><i class=\"fas fa-comments fa-3x tm-nav-icon\"></i><span class=\"tm-nav-text\">Rechercher un livre</span><div class=\"productbg\"></div></div><div class=\"productdescription\">");
		trouver=verifier_creation(6,fich_pages);
		fprintf(fic,"<a target=\"_blank\" href=\"%s\">Rechercher un livre</a>",trouver);
		fprintf(fic,"</div></div></div></div></div></div></div></div><div class=\"container tm-site-header-container\"><div class=\"row\"><div class=\"col-sm-12 col-md-6 col-lg-6 col-md-col-xl-6 mb-md-0 mb-sm-4 mb-4 tm-site-header-col\"><div class=\"tm-site-header\"><h1 class=\"mb-4\">Gestion des EMPRUNTEURS</h1><img src=\"img/underline.png\" class=\"img-fluid mb-4\"></div></div><div class=\"col-sm-24 col-md-6 col-md-6 col-lg-12 col-xl-12\"><div class=\"content\"><div class=\"grid\"> <div class=\"griditem\" id=\"home-link\"><div class=\"product\"><div class=\"tm-nav-link\"><i class=\"fas fa-home fa-3x tm-nav-icon\"></i><span class=\"tm-nav-text\">Ajouter un emprunteur</span><div class=\"productbg\"></div></div><div class=\"productdescription\">");
		trouver=verifier_creation(7,fich_pages);
		fprintf(fic,"<a target=\"_blank\" href=\"%s\">Ajouter un emprunteur</a>",trouver);
		fprintf(fic,"</div> </div></div><div class=\"griditem\" id=\"team-link\"><div class=\"product\"><div class=\"tm-nav-link\"><i class=\"fas fa-users fa-3x tm-nav-icon\"></i><span class=\"tm-nav-text\">Lister les emprunteurs</span><div class=\"productbg\"></div></div><div class=\"productdescription\">");
		trouver=verifier_creation(8,fich_pages);
		fprintf(fic,"<a target=\"_blank\"  href=\"%s\">Liste des emprunteurs</a>",trouver);
		fprintf(fic,"</div></div></div><div class=\"griditem\"><div class=\"product\"><div class=\"tm-nav-link\"><i class=\"fas fa-handshake fa-3x tm-nav-icon\"></i><span class=\"tm-nav-text\">Supprimer un emprunteur</span><div class=\"productbg\"></div></div><div class=\"productdescription\">");
		trouver=verifier_creation(9,fich_pages);
		fprintf(fic,"<a  target=\"_blank\"href=\"%s\">Supprimer un emprunteur</a>",trouver);
		fprintf(fic,"</div></div></div><div class=\"griditem\"><div class=\"product\"><div class=\"tm-nav-link\"><i class=\"fas fa-comments fa-3x tm-nav-icon\"></i><span class=\"tm-nav-text\">Rechercher un emprunteur</span><div class=\"productbg\"></div></div><div class=\"product_description\">");
		trouver=verifier_creation(10,fich_pages);
		fprintf(fic,"<a target=\"_blank\"href=\"%s\">Rechercher un emprunteur</a>",trouver);   
        fprintf(fic,"</div></div></div></div></div></div></div></div></div></div><script src=\"js/jquery-3.2.1.slim.min.js\"></script><script src=\"slick/slick.min.js\"></script><script src=\"js/anime.min.js\"></script><script src=\"js/main.js\"></script><script>function setupFooter() {var pageHeight = $('.tm-site-header-container').height() + $('footer').height() + 100;var main = $('.tm-main-content');if($(window).height() < pageHeight) {main.addClass('tm-footer-relative');}else { main.removeClass('tm-footer-relative'); }}        $(function(){setupFooter();$(window).resize(function(){setupFooter();});$('.tm-current-year').text(new Date().getFullYear());});</script></body></html>");
		
        printf("_______________Voici son lien pour la consulter : <%s>__________________\n",lien);
	 	fclose(fic);	   
  }
else{
	    printf("___________________votre page est bien cree !__________\n");
	    printf("_________Touts les liens des pages deja crees ont ete bien ajoutes__________\n");
         lien=ajouter_page(1,email,fich_pages);
         goto label;
    }
  }
  ///************************gestion des lien:pour ajouter un lien à partir des pages cree vers la page d'accueil*******
char *gestionLien(char *fich_pages,char *email){
  char*lien,*trouver;
  char choix;
  fflush(stdin);
  printf("______Voulez vous que toutes les pages crees ont lien vers la page d\'accueil? (o|n):______\n");
  scanf("%c",&choix);
  if(choix=='o'){
  	trouver=verifier_creation(1,fich_pages);
  	if(trouver==NULL){
  		printf("______Vous ne pouvez pas avoir un lien a partir des pages vers la page d\'accueil alors qu\'elle n\'existe pas!!!!______\n");
	    printf("______veuillez creer la page d\'accueil d\'abord puis refaire ce choix!!______\n");
	  }
	else{
	  trouver=verifier_creation(11,fich_pages);
	  if(trouver==NULL){
	  	lien=ajouter_page(11,email,fich_pages);
	  }
	  
      printf("__________Toutes les pages que vous allez creer et consulter auront un lien vers la page d\'accueil\n________");
   }
 }	
 //****************************************************************************************************************************
}
 //********fonction qui modifie le nombre (d'exemplaires/livres empruntes) lors de la (suppression du livre/suppression d'emprunt)/ajouter...
 void modifier(int i,char*code,char *fich_livres,char *email,char *fich_emprunteur){//livre unique
 switch(i){
   case 1:{
   	Livre *newl=(Livre*)malloc(sizeof(Livre));
   	FILE *f_out=fopen("modifier.txt","w");
    FILE *fp1=fopen(fich_livres,"r");
    if(fp1!=NULL && f_out!=NULL){
        while(!feof(fp1)){
            if(fscanf(fp1,"%s  %s  %s  %d  %f\n",newl->code_livre,newl->auteur,newl->titre,&newl->nbr_exemplaires,&newl->prix)!=-1){
              if(strcmp(newl->code_livre,code)==0){
              	newl->nbr_exemplaires--;
                }
                fprintf(f_out,"%s  %s  %s  %d  %f\n",newl->code_livre,newl->auteur,newl->titre,newl->nbr_exemplaires,newl->prix);
            }
        }
         fclose(fp1);
		 fclose(f_out);
		 remove(fich_livres);
		 rename("modifier.txt",fich_livres);
    }
    else{
	printf("une erreur d'ouverture des fichier de livres \n");
	}
	break;
   }
 case 2:{
 	Emprunteur*e=(Emprunteur*)malloc(sizeof(Emprunteur));
    FILE *fp1=fopen(fich_emprunteur,"r");
     FILE *f_out=fopen("modifier.txt","w");
    if(fp1!=NULL && f_out!=NULL){
        while(!feof(fp1)){
            if(fscanf(fp1,"%s  %s  %s  %d\n",e->nom,e->prenom,e->email,&e->nbr_livres_emp)!=-1){
              if(strcmp(e->email,email)==0){
              	e->nbr_livres_emp++;   
                }
                fprintf(f_out,"%s  %s  %s  %d\n",e->nom,e->prenom,e->email,e->nbr_livres_emp);
            }
        }
        fclose(fp1);
		 fclose(f_out);
		 remove(fich_emprunteur);
		 rename("modifier.txt",fich_emprunteur);
    }
    else{
	printf("une erreur d'ouverture des fichier de emprunteurs \n");
	}
	break;
 } 
 case 3:{
 	 	Emprunteur*e=(Emprunteur*)malloc(sizeof(Emprunteur));
    FILE *fp1=fopen(fich_emprunteur,"r");
    FILE *f_out=fopen("modifier.txt","w");
    if(fp1!=NULL && f_out!=NULL){
        while(!feof(fp1)){
            if(fscanf(fp1,"%s  %s  %s  %d\n",e->nom,e->prenom,e->email,&e->nbr_livres_emp)!=-1){
              if(strcmp(e->email,email)==0){
              	e->nbr_livres_emp--;     
                }
                fprintf(f_out,"%s  %s  %s  %d\n",e->nom,e->prenom,e->email,e->nbr_livres_emp); 
            }
        }
         fclose(fp1);
		 fclose(f_out);
		 remove(fich_emprunteur);
		 rename("modifier.txt",fich_emprunteur);
    }
    else{
	printf("une erreur d'ouverture des fichier de emprunteurs \n");
	}
	break;
 }
 case 4:{
   	Livre *newl=(Livre*)malloc(sizeof(Livre));
    FILE *fp1=fopen(fich_livres,"r");
    FILE *f_out=fopen("modifier.txt","w");
    if(fp1!=NULL && f_out!=NULL){
        while(!feof(fp1)){
            if(fscanf(fp1,"%s  %s  %s  %d  %f\n",newl->code_livre,newl->auteur,newl->titre,&newl->nbr_exemplaires,&newl->prix)!=-1){
              if(strcmp(newl->code_livre,code)==0){
              	newl->nbr_exemplaires++;
                }
                fprintf(f_out,"%s  %s  %s  %d  %f\n",newl->code_livre,newl->auteur,newl->titre,newl->nbr_exemplaires,newl->prix);
            }
        }
         fclose(fp1);
		 fclose(f_out);
		 remove(fich_livres);
		 rename("modifier.txt",fich_livres);
    }
    else{
	printf("-----une erreur d'ouverture des fichier de livres-------- \n");
	}
	break;
   }
 default:printf("choix invalid!!!\n");
 }
}//*************Importer****************************************
void importer(){         //  par exemple==>F:\html_example\exo2.html ou ==>F:/monProjetCSS/exo2.html
	char ch[100];
	char chcorige[100];
	int i,j;
	char tmp;
	fflush(stdin);
	printf("veuillez entrer le chemin du fichier html que vous voulez importer sur votre repertoire\n");
	gets(ch);
	for(i=strlen(ch)-1,j=0;i>=0;i--,j++){
	 if(ch[i]!=92 && ch[i]!=47) {
	 	chcorige[j]=ch[i];
	 }
	 else{
	 		chcorige[j]='\0';
	 	    break;
	 }
}
	 for(i=0,j=strlen(chcorige)-1;i<j;j--,i++){
	   tmp=chcorige[i];
	   chcorige[i]=chcorige[j];
	   chcorige[j]=tmp;	
	 }
  FILE*f_in=fopen(ch,"r");
  FILE*f_out=fopen("copie.html","w");
  if(f_in!=NULL && f_out!=NULL){
	  while(!feof(f_in)){
	  	fprintf(f_out,"%c",fgetc(f_in));
	  }	
	 fclose(f_in);
	 fclose(f_out);
	 remove(ch);
	 rename("copie.html",chcorige);
	}
	else{
		printf("erreur d'ouverture!!!\n");
	}	
	printf("L\'importation du fichier a ete faite avec succes\n");
}
//**********************************************************************************************************


