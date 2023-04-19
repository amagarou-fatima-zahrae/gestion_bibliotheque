#ifndef projetC
#define projetC

//*****Page******************************
 typedef struct{
 int n_page; 
 char lien[100];
}Page_Html;
//****Admin*******************
typedef struct{
    char nom[40];
    char prenom[40];
    char email[50];
    char password[50];
    char fich_pages[50];//le fichier ou on va stocher les info(numero ,lien) des pages de cet admin (accueil,ajouter,supprrimer...)
    char fich_livres[50];//le fichier ou on va stocher les info de chaque livre 
    char fich_emprunt[50];//le fichier ou on va stocher les info de chaque empruteur
    char emprunt[50]; //le fichier ou on va stocher les info de chaque opération d'emprunt effectuee 
}Admin;
//*********************Emprunteur**********************
typedef struct{
char nom[50];
char prenom[50];
char email[50];
int nbr_livres_emp;	
}Emprunteur; 
//******************Livre***************************************
typedef struct{
char code_livre[20];
char auteur[50];
char titre[50];
int nbr_exemplaires;
float prix;	
}Livre;
//******************Emprunt(table d'association entre le livre et l'emprunteur***************************************
typedef struct{
 char code_livre[50]; 
 char email[100];
}Emprunt;
//**********************************************************************************************************************

//**********************defintion des fonctions du programme*************************************************************************
char* rechercher_fichier(int i,char *email,char *fich_admin);
char menu();
void decryptage(char *T);
void cryptage( char*T);
void ajouter(char *nom_fichierAdmin,Admin *u1);
char* rechercher_dans_fichier(char *email,char *nom_fichierAdmin);
Admin* sign_in (char *nom_fichierAdmin);
char* login(char*nom_fichierAdmin);
char menu_admin();
//***********************************
char* verifier_creation(int i,char *nom_fich);
char * ajouter_page(int numero,char *email,char *fich_pages);
char menu_front();
void creer_pageAuthentif(char *fich_pages,char *email);
void pageAccueil(char *fich_pages,char *email);
char *gestionLien(char *fich_pages,char *email);
void modifier(int i,char*code,char *fich_livres,char *email,char *fich_emprunteur);
void importer();
//*****************************************
int NbrExemplaire_emp(char*code,char *emprunt);
int rechercher_livre(char*code,char *fich_livres);
char sous_menuS();
char sous_menuL();
Livre* Saisir_livre(char *fich_livres,char *email,char*fich_emprunteur);
void Ajouter_livre(char *fich_livre, Livre *newl);
char menu_livre();
void Page_ajouter_livre(char *fich_pages,char*fich_livres,char*email,char*fich_emprunteur);
void supprimer_livre(char*code,char *nom_fich_livres);
void Page_supprimer_livre(char *fich_pages,char*fich_livres,char*email,char *emprunt,char *emprunteur);
int lister_livres(char *nom_fich,char *email,char *fich_livres);
void Afficher_livre(char *nom_fich_livres);
void Page_rechercher_livre(char *fich_pages,char*fich_livres,char*email);
 void gestion_livre(char *fich_pages,char *fich_livres,char *email,char*fich_emprunteur,char*emprunt);
 //**********************************************************************************
 void Ajouter_Emprunteur(char *fich_emprunteur,Emprunteur *e );
 char menu_emprunteur();
 char* verifier_emprunteur(int i,char *email,char *fich_emprunteur);
 char menu_emprunt();
 void verifier_livre(int signe,char *fich_livres,char *fich_emprunteur,char *emprunt,Emprunteur *e,char *email);
 Emprunteur* Saisir_Emprunt(char *fich_emprunteur ,char *emprunt,char *fich_livres);
 void Page_ajouter_emprunt(char *fich_pages,char *fich_emprunteurs,char*emprunt,char*email,char *fich_livres);
 int supprimer_emprunt(char *email,char *code,char*emprunt);
 void supprimer_tot(char *email,char *fich_livres,char *fich_emprunteurs,char*emprunt);
 void Page_supprimer_emprunt(char *fich_pages,char *fich_livres,char *fich_emprunteurs,char*emprunt,char*email);
int lister_emprunt(char *nom_fich,char *email,char *fich_emprunt,char *emprunt);
void Afficher_emprunt(char *fich_emprunteur);
void Page_rechercher_emprunt(char *fich_pages,char*fich_emprunt,char*email);
void gestion_emprunt(char *fich_pages,char *fich_emprunteurs,char *fich_emprunt,char *fich_livres,char *email);
 #endif


