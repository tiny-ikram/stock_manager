//attention !!!! les données pour se connecter sont identifiant: Admin , mot de passe: 0000
//les fichiers utilisées sont en binaires
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include <stdlib.h>
int connection(char identifiant[25], char mot_de_passe[8]);
int menu_de_choix();
void affichage (char c ,FILE * fs , FILE * fh);
typedef struct produit produit;
struct produit
{
    int ref ;
    char nom [40];
    int quantite ;
    char description [100];
};
typedef struct operation operation ;
struct operation
{
    char nomoperation [40];
    produit produit ;
    int mois ;
    int jour ;
};
long int sizedep,sizedeo ;
int main ()
{
   FILE* fs= NULL , * fh= NULL , *ft=NULL;
   int tentative=0,i=0,c=0,r=0 ;
   char identifiant[25],password[8],autre,nomduproduit[25],choix;
   produit p ;
   operation o;
deconnection:
    fflush(stdin);
    tentative=0;
    printf("\t\t\t\t\t\t\t   ==============================================\n\t\t\t\t\t\t\t   *BIENVENUE A STOCK-MANAGER SYSTEME*\n\t\t\t\t\t\t\t   ==============================================");
    printf("\t\t\t\t\t\t\t\t\t                                                            \n\t\t\t\t\t\t\t   POUR ACCEDER A CE SYSTEME, IL FAUT SE CONNECTER \n\t\t\t\t\t\t\t   ==============================================");
    printf("\t\t\t\t\t\n\t");
    do {

        printf("\t\t\t\t\t           Donner votre identifiant:");
        scanf("%*[\n]");
        fgets(identifiant, 10, stdin);
        identifiant[10] = '\0';
        printf("\n\t\t\t\t\t\t\t   Donner votre mot de passe:");
        for (i = 0;i < 4;i++)
        {
            password[i] = _getch();
            printf("*");
        }
        password[i] = '\0';
        c = connection(identifiant, password);
        tentative++;
        if (c) {
            printf("\t\t\t\t\t\t\t                                   ==============================================\n\t\t\t\t\t\t\t\t#ACCES GARENTIE#\n\n\n");
            break;
        }
        else
            printf("\n\n\t\t\t\t\t\tIDENTIFIANT/MOT DE PASSE INJUSTE----------------ACCES REFUSEE, REESSAYER :<\n\n\n\n");
    }while (tentative != 3);
    if (tentative == 3 && c==0 )
    {
        printf("\n\n/////TOUS LES TENTATIVES ONT ECHOUE .....REDEMARRER LE PROGRAMME/////");
        _getch();
        return 0;
    }
menu:
    system("cls");
    switch(menu_de_choix())
    {
    case 1 : //le menu d'affichage //
        system("cls");
        printf("\t\t\t\t\t\t\t   **********************************************\n\t\t\t\t\t\t\t*LE MENU D'AFFICHAGE*\n\t\t\t\t\t\t\t   **********************************************\n\n");
        printf("p. pour afficher un produit\n");
        printf("s. pour afficher le stock \n");
        printf("h. pour afficher historique des operations\n");
        fflush(stdin);
        printf("\n\n-> Saisir votre choix : ");
        scanf("%s",&choix);
        affichage(choix,fs,fh);
        goto menu ;
        break;
    case 2 :  //la fonction ajout //
        system("cls");
        fs=fopen("stock.txt","rb+");
        fh=fopen("historique.txt","rb+");
        if (fs == NULL)
        {
            fs=fopen("stock.txt","wb+");
            if (fs== NULL)
            {
                printf("fichier ne se trouve pas ");
                exit(1);
            }
        }
        if (fh == NULL)
        {
            fh=fopen("historique.txt","wb+");
        }
        sizedep=sizeof(p); //taille du produit//
        sizedeo=sizeof(o); //taille d'operation//
        fseek(fs, 0, SEEK_END);
        fseek(fh, 0, SEEK_END);
        autre='o';
        while (autre=='o')
       {
           system("cls");
           printf("____________________________________________________\n");
           printf("#####################################################");
           printf("\n\n)-> Donner la reference(entier) du produit :- ");
           scanf("%d", &p.ref);
           printf("\n\n)-> Donner le nom du produit :- ");
           scanf("%s", p.nom);
           printf("\n\n)-> La quantite du %s valable :- ", p.nom);
           scanf("%d", &p.quantite);
           printf("\n\n)-> Donner la description du %s :- ",p.nom);
           scanf("%s", p.description);
           strcpy(o.nomoperation,"ajout");
           o.produit=p;
           printf("\n\n)-> Donner le jour(entier) :- ");
           do
           {
              scanf("%d", &o.jour);
           }
           while (o.jour>31);
           printf("\n\n)-> Donner le mois(entier) :- ");
           do
           {
              scanf("%d", &o.mois);
           }
           while (o.mois>12);
           fwrite(&p, sizedep, 1, fs);
           fwrite(&o, sizedeo, 1, fh);
           printf("\n____________________________________________________\n");
           printf("#####################################################");
           printf("\n\n**Voulez vous ajouter un autre ??---(o/n)** ");
           fflush(stdin);
           autre = _getch();
    }
        fclose(fs);
        fclose(fh);
        system("cls");
        goto menu;
        break ;
    case 3 :  //la fonction suppression //
        system("cls");
        fs=fopen("stock.txt","rb+");
        fh=fopen("historique.txt","rb+");
        if (fs == NULL)
        {
            fs=fopen("stock.txt","wb+");
            if (fs== NULL)
            {
               printf("fichier ne se trouve pas ");
               exit(1);
            }
        }
        if (fh == NULL)
        {
            fh=fopen("historique.txt","wb+");
        }
        sizedep=sizeof(p); //taille du produit//
        sizedeo=sizeof(o); //taille d'operation//
        autre='o';
        while (autre=='o')
        {
            system("cls");
            printf("\nDonner le nom du produit a supprimer : ");
            scanf("%s", nomduproduit);
            ft = fopen("Temporaire.txt", "wb");
            rewind(fs);
            fseek(fh, 1, SEEK_END);
            while (fread(&p,sizedep, 1, fs) == 1)
            {
                if (strcmp(p.nom,nomduproduit) != 0)
                {
                    fwrite(&p,sizedep, 1, ft);
                }
            }
            fclose(fs);
            fclose(ft);
            remove("stock.txt");
            rename("Temporaire.txt", "stock.txt");
            fs = fopen("stock.txt", "rb+");
            printf("\n\n)-> Donner le jour(entier) :- ");
            do
            {
               scanf("%d", &o.jour);
            }
            while (o.jour>31);
            printf("\n\n)-> Donner le mois(entier) :- ");
            do
            {
                scanf("%d", &o.mois);
            }
            while (o.mois>12);
            fwrite(&o, sizedeo, 1, fh);
            printf("\n____________________________________________________\n");
            printf("#####################################################");
            printf("\n\n**Voulez vous supprimer un autre ??---(o/n)** ");
            fflush(stdin);
            autre = _getch();
        }
        fclose(fs);
        fclose(fh);
        system("cls");
        goto menu;
        break ;
    case 4 :  //la fonction modification //
        system("cls");
        fs=fopen("stock.txt","rb+");
        fh=fopen("historique.txt","rb+");
        if (fs == NULL)
        {
            fs=fopen("stock.txt","wb+");
            if (fs== NULL)
            {
               printf("fichier ne se trouve pas ");
               exit(1);
            }
        }
        if (fh == NULL)
        {
            fh=fopen("historique.txt","wb+");
        }
        sizedep=sizeof(p); //taille du produit//
        sizedeo=sizeof(o); //taille d'operation//
        autre='o';
        while (autre=='o')
        {
             system("cls");
             printf(")->Donner le nom du produit a modifier :- ");
             scanf("%s", nomduproduit);
             rewind(fs);
             fwrite(&o, sizedeo, 1, fh);
             while (fread(&p, sizedep, 1, fs) == 1)
             {
                if (strcmp(p.nom,nomduproduit ) == 0)
                {
                    printf("\n)->Donner les nouveaux :reference,nom,description,quantite  :-\n");
                    scanf("%d%s%s%d",&p.ref,p.nom,p.description,&p.quantite);
                    strcpy(o.nomoperation,"modif");
                    o.produit=p;
                    printf("\n\n)-> Donner le jour(entier) :- ");
                    do
                    {
                       scanf("%d", &o.jour);
                    }
                    while (o.jour>31);
                    printf("\n\n)-> Donner le mois(entier) :- ");
                    do
                    {
                        scanf("%d", &o.mois);
                    }
                    while (o.mois>12);
                    fwrite(&o, sizedeo, 1, fh);
                    fseek(fs, -sizedep, SEEK_CUR);
                    fwrite(&p, sizedep, 1, fs);
                    break;
                 }
             }
             printf("\n____________________________________________________\n");
             printf("#####################################################");
             printf("\n\n**Voulez vous modifier un autre ??---(o/n)** ");
             fflush(stdin);
             autre = _getch();
        }
        fclose(fs);
        fclose(fh);
        system("cls");
        goto menu;
        break ;
    case 5 :  //la fonction recherche //
        system("cls");
        fs=fopen("stock.txt","rb+");
        fh=fopen("historique.txt","rb+");
        if (fs == NULL)
        {
           fs=fopen("stock.txt","wb+");
           printf("le stock est vide.");
           if (fs== NULL)
           {
               printf("fichier ne se trouve pas ");
               exit(1);
           }
         }
        if (fh == NULL)
        {
            fh=fopen("historique.txt","wb+");
        }
        sizedep=sizeof(p); //taille du produit//
        sizedeo=sizeof(o); //taille d'operation//
        autre='o';
        while (autre=='o')
        {
            system("cls");
            printf("\nDonner le nom du produit a rechercher : ");
            scanf("%s", &nomduproduit);
            rewind(fs);
            fseek(fh, 0, SEEK_END);
            while (fread(&p, sizedep, 1, fs) == 1)
            {
               if (strcmp(p.nom, nomduproduit)== 0)
               {
                  r=1;
                  break;
               }
            }
            strcpy(o.nomoperation,"reche");
            o.produit=p;
            printf("\n\n)-> Donner le jour(entier) :- ");
            do
            {
              scanf("%d", &o.jour);
            }
            while (o.jour>31);
            printf("\n\n)-> Donner le mois(entier) :- ");
            do
            {
               scanf("%d", &o.mois);
            }
            while (o.mois>12);
            fwrite(&o, sizedeo, 1, fh);
            if (r==1)
            {
               printf("\nle produit recherche %s est trouve.\n",p.nom);
            }
            else
              {
                printf("\nle produit cherche ne se trouve pas dans le stock.\n");
              }
              printf("\n____________________________________________________\n");
              printf("#####################################################");
              printf("\n\n**Voulez vous chercher un autre ??---(o/n)** ");
              fflush(stdin);
              autre = _getch();
        }
        fclose(fs);
        fclose(fh);
        system("cls");
        goto menu;
        break;
    case 6 :
        system("cls");
        goto deconnection ;
        break;
    default :
        system("cls");
        printf("\n\n le caractere donne est faux \n redirection a la page de connection ...........");
        _getch();
        goto deconnection;
    }
    _getch();
    return 0;
}
void affichage (char c ,FILE * fs , FILE * fh)
{
    produit p ;
    operation o ;
    char nomdeproduit[25],autre;
    fs=fopen("stock.txt","rb+");
    fh=fopen("historique.txt","rb+");
    if (fs == NULL)
    {
        fs=fopen("stock.txt","wb+");
        printf("le stock est vide.");
        if (fs== NULL)
        {
            printf("fichier ne se trouve pas ");
            exit(1);
        }
    }
    if (fh == NULL)
    {
        fh=fopen("historique.txt","wb+");
    }
    switch (c)
    {
    case 'p':

        sizedep=sizeof(p); //taille du produit//
        sizedeo=sizeof(o); //taille d'operation//
        autre='o';
        while (autre=='o')
        {
            system("cls");
            printf("\nDonner le nom du produit a afficher :");
            scanf("%s",&nomdeproduit);
            rewind(fs);
            fseek(fh, 0, SEEK_END);
            while (fread(&p, sizedep, 1, fs) == 1)
            {
                 if (strcmp(p.nom, nomdeproduit)== 0)
                 {
                  o.produit=p;
                  printf("\n#reference du produit: %d\n#nom du produit: %s\n#description du produit:%s\n#quantite du produit:%d\n", p.ref,p.nom,p.description,p.quantite);
                  break;
                 }
            }
            strcpy(o.nomoperation,"affiche");
            printf("\n\n)-> Donner le jour(entier) :- ");
            do
            {
               scanf("%d", &o.jour);
            }
            while (o.jour>31);
            printf("\n\n)-> Donner le mois(entier) :- ");
            do
            {
               scanf("%d", &o.mois);
            }
            while (o.mois>12);
            fwrite(&o, sizedeo, 1, fh);
            printf("\n____________________________________________________\n");
            printf("#####################################################");
            printf("\n\n**Voulez vous afficher un autre??---(o/n)** ");
            fflush(stdin);
            autre = _getch();
        }
        fclose(fs);
        fclose(fh);
        break ;
    case 's':
        system("cls");
        fflush(stdin);
        fs=fopen("stock.txt","rb+");
        if (fs == NULL)
        {
           fs=fopen("stock.txt","wb+");
           printf("le stock est vide.");
           if (fs== NULL)
           {
               printf("fichier ne se trouve pas ");
               exit(1);
           }
        }
        sizedep=sizeof(p);
        system("cls");
        rewind(fs);
        printf("\t\t\t\t\tREF\tNOM\t\tDESCRIPTION\tQUANTITE\n");
        printf("\t\t\t\t______________________________________________________________________\n");
        printf("\t\t\t\t######################################################################\n");
        while (fread(&p,sizedep, 1, fs) == 1)
        {
             printf("\n\n\t\t\t\t\t%d\t%s\t\t%s\t\t%d",p.ref,p.nom,p.description,p.quantite);
        }
        printf("\n\n\t\t\t\t######################################################################\n");
        _getch();
        fclose(fs);
        break;
    case 'h':
        system("cls");
        fflush(stdin);
        fh=fopen("historique.txt","rb+");
        if (fh == NULL)
        {
            fh=fopen("historique.txt","wb+");
            printf("pas de historique des operations.");
            if (fh== NULL)
            {
                printf("fichier ne se trouve pas ");
                exit(1);
            }
        }
        sizedeo=sizeof(o);
        system("cls");
        rewind(fh);
        printf("\t\t\t\t\tOPERATION\tJOUR\tMOIS\tNOM DU PRODUIT\n");
        printf("\t\t\t\t______________________________________________________________________\n");
        printf("\t\t\t\t######################################################################\n");
        while (fread(&o,sizedeo, 1, fh) == 1)
        {
             printf("\n\n\t\t\t\t\t%s\t\t%d\t%d\t%s",o.nomoperation,o.jour,o.mois,o.produit.nom);
        }
        printf("\n\n\t\t\t\t######################################################################\n");
        _getch();
        fclose(fh);
        break;
    default:
        printf("le caractere donne est irrone");
        break;
    }
}
int connection(char identifiant[25], char mot_de_passe[8])
{
    if (strcmp(identifiant, "Admin") && strcmp(mot_de_passe, "0000"))
    {
        return 0;
    }
    else
        return 1;
}
int menu_de_choix() {
    int d;
    printf("\n\nBonjour Admin ! Bienvenue dans le menu! \n\nchoisissez l'operation a faire :\n\n#saisir 1 pour afficher le stock ou l'historique ou un produit\n#saisir 2 pour ajouter un produit\n#saisir 3 pour supprimer un produit\n#saisir 4 pour modifier un produit\n#saisir 5 pour rechercher un produit dans le stock\n#saisir 6 pour se deconnecter");
    printf("\n\n Donner votre choix :- ");
    scanf("%d",&d);
    return d;
}
