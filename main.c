/************************************************************************************************
*                           Ce qu'il reste … faire                                              *
*                                                                                               *
*   - Mettre des DEFAULT_VALUE                                                                  *
*   - Mettre des commentaires avec Doxygen                                                      *
*   - Mise en page et pr‚sentation du jeu -> titres, grille, aide, mettre milieu, ...           *
*   - Titre pour le code (comme celui-l…)                                                       *
*   - Faire le dossier ! -> Possibilit‚ de faire la prob sur un IA                              *
*
************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAILLEGRILLE 10
#define MAX_NOM 9
#define COUPS 4

//********************************************FUNCTIONS INIT******************************************************
void authentification(char tab[TAILLEGRILLE][TAILLEGRILLE], char tab2[TAILLEGRILLE][TAILLEGRILLE], char nom[MAX_NOM]);
void menuPrincipal(char tab[TAILLEGRILLE][TAILLEGRILLE], char tab2[TAILLEGRILLE][TAILLEGRILLE], char nom[MAX_NOM]);
void menuAide(char tab[TAILLEGRILLE][TAILLEGRILLE], char tab2[TAILLEGRILLE][TAILLEGRILLE], char nom[MAX_NOM]);
void grille(char tab[TAILLEGRILLE][TAILLEGRILLE]);
void initTab(char tab[TAILLEGRILLE][TAILLEGRILLE]);
void initNavires(char tab[TAILLEGRILLE][TAILLEGRILLE]);
void jouer(char tab[TAILLEGRILLE][TAILLEGRILLE], char tab2[TAILLEGRILLE][TAILLEGRILLE], char nom[MAX_NOM]);
void choix(char tab[TAILLEGRILLE][TAILLEGRILLE], char tab2[TAILLEGRILLE][TAILLEGRILLE],int *coups, int *coule);
int changement(char choix);
void resultat(char tab[TAILLEGRILLE][TAILLEGRILLE], char tab2[TAILLEGRILLE][TAILLEGRILLE], char nom[MAX_NOM]);
int count(int number, char tab[TAILLEGRILLE][TAILLEGRILLE]);
//***********************************************************************************************************************

int main()
{
    char nomJoueur[MAX_NOM];
    char tableau[TAILLEGRILLE][TAILLEGRILLE];
    char tableauNavires[TAILLEGRILLE][TAILLEGRILLE];

    authentification(tableau, tableauNavires, nomJoueur);

    return EXIT_SUCCESS;
}

//********************************************FUNCTIONS******************************************************
void authentification(char tab[TAILLEGRILLE][TAILLEGRILLE], char tab2[TAILLEGRILLE][TAILLEGRILLE], char nom[MAX_NOM])
{

    int espacement = 15, longueur, existant, joueurNb;
    char i = ' ', rep, choix1;
    char verif[MAX_NOM];
    FILE *source = NULL;

   //HEADER
    printf("\n\n%*c***************\n",espacement,i);
    printf("%*cBATAILLE NAVALE\n",espacement,i);
    printf("%*c***************\n",espacement,i);
    //DIALOGUE
    printf("\nBonjour et bienvenue a toi matelot !\n");
    printf("Si tu veux venir sur mon bateau...\n");
    printf("\nIl me faudra ton nom !\n");
    do
    {
        printf("\nSouhaites-tu voir la liste des marins avant d'entrer ton nom ? O/N\n");
        printf("Choix : ");
        scanf("%c", &choix1);
        fflush(stdin);
    }while(choix1 != 'O' && choix1 != 'N');
    if(choix1 == 'O')
    {
        joueurNb = 1;

        source = fopen("player.txt", "r");
        if(source != NULL)
        {
            printf("\n");
            while(fgets(verif, MAX_NOM, source) != NULL)
            {
                printf("%i. %s", joueurNb, verif);
                joueurNb++;
            }
        }
        else
        {
            printf("Aucun marin n'a ete enregistre pour le moment !\n");
        }
    }
    do
    {
        rep = ' ';
        existant = 0;

        do{
            printf("\nChoisi un nom !\n");
            printf("(Maximum 8 caracteres)\n");
            printf("Nom : ");
            fflush(stdin);
            gets(nom);
            longueur = strlen(nom);
        }while(longueur > 8);

        //REGISTER NAME
        source = fopen("player.txt", "r+");
        if(source != NULL)
        {
            while(fgets(verif, MAX_NOM, source) != NULL)
            {
                longueur = strlen(verif);
                verif[longueur-1] = '\0';
                if(strcmp(nom, verif) == 0)
                {
                    //NAME ALREADY REGISTERED
                    existant = 1;
                }
            }
        }
        else
        {
            printf("Erreur implementation nom !");
        }
        if(existant != 1)
        {
            fputs(nom, source);
            fputs("\n", source);
        }
        else
        {
            printf("\nNom deja existant !\n");
            do
            {
            printf("Souhaites-tu continuer avec ce nom ? O/N\n");
            printf("Choix : ");
            //CONTINUER AVEC CHOIX ET DEMANDER LA POSSIBILITE DE VOIR LES NOMS !!!!
            fflush(stdin);
            scanf("%c", &rep);
            }while(rep != 'O' && rep != 'N');
        }
        fclose(source);
    }while(rep == 'N');

    menuPrincipal(tab, tab2, nom);
}

void menuPrincipal(char tab[TAILLEGRILLE][TAILLEGRILLE], char tab2[TAILLEGRILLE][TAILLEGRILLE], char nom[MAX_NOM])
{
    int espacement = 15;
    char i = ' ', choix;

    //BOAT INIT
    initTab(tab2);
    initNavires(tab2);
    //GAME INIT
    initTab(tab);

    system("cls");
    //HEADER
    printf("\n\n%*c**************\n",espacement,i);
    printf("%*cMENU PRINCIPAL\n",espacement,i);
    printf("%*c**************\n",espacement,i);
    //DIALOGUE ET CHOICES
    printf("Cela me fait plaisir de te voir %s !\n\n", nom);
    printf("J'espere que tu vas bien\n");
    printf("Que souhaites-tu faire ?\n");
    printf("-Entre la lettre [j] pour JOUER\n");
    printf("-Entre la lettre [m] pour le MENU D'AIDE\n");
    printf("-Entre la lettre [r] pour tes SCORES\n");
    printf("-Entre la lettre [q] pour nous QUITTER\n\n");
    printf("Choisis ta lettre mousaillon: ");
    fflush(stdin);
    scanf("%c", &choix);
    //CHOICE VERIFICATION
    while((choix != 'j') && (choix != 'm') && (choix != 'r') && (choix != 'q'))
    {
        printf("\nAurais-tu trop bu mousaillon ?\n\n");
        printf("Que souhaites-tu faire ?\n");
        printf("-Entre la lettre [j] pour JOUER\n");
        printf("-Entre la lettre [m] pour le MENU D'AIDE\n");
        printf("-Entre la lettre [r] pour tes SCORES\n");
        printf("-Entre la lettre [q] pour nous QUITTER\n\n");
        printf("Et choisis une lettre possible s'il te plait: ");
        fflush(stdin);
        scanf("%c", &choix);
    }
    //NAVIGATION MENU
    switch(choix)
    {
    case 'j' : jouer(tab, tab2, nom);
        break;
    case 'm' : menuAide(tab, tab2, nom);
        break;
    case 'r' : resultat(tab, tab2, nom);
        break;
    default : return EXIT_SUCCESS;
        }
}

void menuAide(char tab[TAILLEGRILLE][TAILLEGRILLE], char tab2[TAILLEGRILLE][TAILLEGRILLE], char nom[MAX_NOM])
{
    int espacement = 15;
    char i = ' ', choix, suite;
    char tableauExemple[TAILLEGRILLE][TAILLEGRILLE];

    system("cls");
    //HEADER
    printf("\n\n%*c***********\n",espacement,i);
    printf("%*cMENU D'AIDE\n",espacement,i);
    printf("%*c***********\n",espacement,i);
    //GAME EXPLANATION
    printf("Je vois que nous avons affaire a un marin d'eau douce !!!\n");
    printf("Ne t'inquietes pas, il faut bien commencer quelque part !\n");
    printf("Voici quelques explications pour t'en sortir :\n");

    do{
        printf("\nPour lire la suite entre s: ");
        fflush(stdin);
        scanf("%c", &suite);
    }while(suite != 's');

    system("cls");
    printf("\n\nTout d'abord, voici a quoi va ressembler ton terrain de guerre :\n\n");
    initTab(tableauExemple);
    grille(tableauExemple);
    do{
        printf("Pour lire la suite entre s: ");
        fflush(stdin);
        scanf("%c", &suite);
    }while(suite != 's');

    system("cls");
    printf("\nEnsuite il te faudra choisir sur quelle parcelle bombarder ton ennemi !\n");
    printf("Pour ca, rien de plus simple...\nIl te faudra choisir une ligne (c'est-a-dire un nombre) ou une colonne (c'est-a-dire une lettre).\n\n");
    printf("Voici comment cela sera mis :\n");
    printf("Entrez votre colonne(lettre) : _\n");
    printf("Entrez votre ligne(nombre) : _\n\n");
    printf("Rien de sorcier non ?\n\n");
    printf("Choisisson la lettre C et la nombre 5 et voyons ce qu'il se passe...\n\n");
    tableauExemple[4][2]= 'O';
    do{
        printf("Pour lire la suite entre s: ");
        fflush(stdin);
        scanf("%c", &suite);
    }while(suite != 's');
    system("cls");
    printf("\n");
    printf("\nMince, c'est rate ! On fera mieux la prochaine fois mousaillon : Nombre de coups(1), Navires coules (0/6)\n\n");
    grille(tableauExemple);
    printf("Mille millards de mille sabords !\nRetentons notre chance !\n");
    printf("Bombardons la case E8 !\n");
    tableauExemple[9][4]= 'X';
    do{
        printf("\nPour lire la suite entre s: ");
        fflush(stdin);
        scanf("%c", &suite);
    }while(suite != 's');

    system("cls");
    printf("\n");
    printf("\nBravo ! Vous venez de touche un navire adverse : Nombre de coups(2/50), Navires coules (0/6)\n\n");
    grille(tableauExemple);
    printf("WOOOOHOOOOOO AHAHAHAHA !\nBien fait pour eux !\n\n");
    printf("Et bien ! J'espere que tu as compris comment ca fonctionne ici mousaillon.\nMaintenant a toi de jouer !\n");
    do{
        printf("Pour lire la suite entre s: ");
        fflush(stdin);
        scanf("%c", &suite);
    }while(suite != 's');

    system("cls");
    //HEADER
    printf("\n\n%*c***************\n",espacement,i);
    printf("%*cFIN MENU D'AIDE\n",espacement,i);
    printf("%*c***************\n",espacement,i);

    printf("\nQue souhaites-tu faire ?\n");
    printf("-Entre la lettre [j] pour JOUER\n");
    printf("-Entre la lettre [m] pour le MENU PRINCIPAL\n");
    printf("-Entre la lettre [r] pour tes SCORES\n");
    printf("-Entre la lettre [q] pour nous QUITTER\n\n");
    printf("Choisis ta lettre mousaillon: ");
    fflush(stdin);
    scanf("%c", &choix);
    //ENTRY VERIFICATION
    while((choix != 'j') && (choix != 'm') && (choix != 'r') && (choix != 'q'))
    {
        printf("\nAurais-tu trop bu mousaillon ?\n\n");
        printf("Que souhaites-tu faire ?\n");
        printf("-Entre la lettre [j] pour JOUER\n");
        printf("-Entre la lettre [m] pour le MENU PRINCIPAL\n");
        printf("-Entre la lettre [r] pour tes SCORES\n");
        printf("-Entre la lettre [q] pour nous QUITTER\n\n");
        printf("Et choisis une lettre possible s'il te plait: ");
        fflush(stdin);
        scanf("%c", &choix);
    }
    //NAVIGATION MENU
    switch(choix)
    {
    case 'j' : jouer(tab, tab2, nom);
        break;
    case 'm' : menuPrincipal(tab, tab2, nom);
        break;
    case 'r' : resultat(tab, tab2, nom);
        break;
    default : return EXIT_SUCCESS;
        }
}

void grille(char tab[TAILLEGRILLE][TAILLEGRILLE])
{
    int esp = 5, i, j;
    char vide = ' ';

    printf("%6cA%*cB%*cC%*cD%*cE%*cF%*cG%*cH%*cI%*cJ\n", vide,
           esp, vide, esp, vide, esp, vide, esp, vide, esp, vide, esp,
           vide, esp, vide, esp, vide, esp, vide);
    for(i = 0; i < TAILLEGRILLE; i++)
    {
        printf("   -------------------------------------------------------------\n");
        //IF == 9, SO THE MATRICE DOESN'T MOVE DUE TO THE 10 THAT HAS 2 BITS
        if(i == 9){
            printf("%i |", i+1);
        }
        else{
            printf("%i  |", i+1);
        }
        for(j = 0; j < TAILLEGRILLE; j++)
        {
            printf("%3c  |", tab[i][j]);
        }
        printf("\n");
    }
    printf("   -------------------------------------------------------------\n");

}

void initTab(char tab[TAILLEGRILLE][TAILLEGRILLE])
{
    int i, j;
    for(i = 0; i < TAILLEGRILLE; i++)
    {
        for(j = 0; j < TAILLEGRILLE; j++)
        {
            tab[i][j] = ' ';
        }
    }
}

void initNavires(char tab[TAILLEGRILLE][TAILLEGRILLE])
{
    int choix, i, n1, n2;
    char c = ' ';
    long placement = 0;
    FILE *source = NULL;

    srand(time(NULL));
    choix = 0;//rand() % 3;
    switch(choix)
    {
        case 0: source = fopen("placement1.txt", "r");
            break;
        case 1: source = fopen("placement2.txt", "r");
            break;
        case 2: source = fopen("placement3.txt", "r");
            break;
    }
    if (source != NULL)
    {
        for(i = 0; i < 19; i++)
        {
            fseek(source, placement, SEEK_SET);
            c = fgetc(source);
            n1 = c -48;
            placement++;
            fseek(source, placement, SEEK_SET);
            c = fgetc(source);
            n2 = c -48;
            placement++;
            fseek(source, placement, SEEK_SET);
            c = fgetc(source);
            tab[n1][n2] = c;
            placement++;
            placement++;
            placement++;
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier !");
    }
    fclose(source);
}

void jouer(char tab[TAILLEGRILLE][TAILLEGRILLE], char tab2[TAILLEGRILLE][TAILLEGRILLE], char nom[MAX_NOM])
{
    int espacement = 15, nbCoups = 0, naviresCoule = 0;
    char i = ' ', rep = ' ';
    char nomComplet[20] = "";
    FILE *source = NULL;


    system("cls");
    //HEADER
    printf("\n\n%*c***************\n",espacement,i);
    printf("%*cBATAILLE NAVALE\n",espacement,i);
    printf("%*c***************\n",espacement,i);

    grille(tab);
    printf("\nA l'abordage !");
    //CHANGE THE MATRICE WITH SHOOTS
    do
    {
        choix(tab, tab2, &nbCoups, &naviresCoule);

    }while((nbCoups < COUPS) && naviresCoule < 6);

    system("cls");
    if(naviresCoule == 6)
    {
        printf("\nBravo vous avez coule tous les navires ennemis en %i coups !", nbCoups);
    }
    else
    {
        printf("\nMalheureusement on n'a pas coule tous les navires et nous n'avons plus de coups possibles moussaillon !");
    }
    //REGISTER NAME AND SCORE
    strcat(nomComplet, "player");
    strcat(nomComplet, nom);
    strcat(nomComplet, ".txt");

    source = fopen(nomComplet, "a");
    if(source != NULL)
    {
        fprintf(source, "%i\n", nbCoups);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier !");
    }
    fclose(source);

    //END PROPOSAL
    do
    {
        printf("\n\n- Entrez [m] pour retourner au MENU PRINCIPAL : ");
        printf("\n- Entrez [q] pour QUITTER : \n");
        printf("Choix : ");
        fflush(stdin);
        scanf("%c", &rep);
        if(rep == 'q')
        {
            return EXIT_SUCCESS;
        }
    }while(rep != 'm');

    menuPrincipal(tab, tab2, nom);
}

void choix(char tab[TAILLEGRILLE][TAILLEGRILLE], char tab2[TAILLEGRILLE][TAILLEGRILLE], int *coups, int *coule)
{
    int compatible1 = 0, compatible2 = 0, i = 0, j = 0;
    char entree;

    //COLUMN ENTRY CHECK
    do
    {
        printf("\nEntrez votre colonne(lettre) : ");
        fflush(stdin);
        scanf("%c", &entree);
        //CHECK WITH ASCII TABLE : A TO J MIN. AND MAJ. ACCEPTED
        if(((entree >= 65) && (entree <= 74)) || ((entree >= 97) && (entree <= 106)))
        {
            compatible1 = 1;
        }
        else
        {
            compatible1 = 0;
        }
    }while(compatible1 == 0);

    i = changement(entree);
    //LINE ENTRY CHECK
    do
    {
        printf("\nEntrez votre ligne(nombre) : ");
        fflush(stdin);
        scanf("%i", &j);

        if(j > 0 && j < 11)
        {
            compatible2 = 1;
        }
        else
        {
            compatible2 = 0;
        }
    }while(compatible2 == 0);
    j -= 1;

    //MATRICE PLAYER CHANGE WITH CHOICE
    if(tab[j][i] != 'X' && tab[j][i] != 'O')
    {
        system("cls");
        switch(tab2[j][i])
            {
            case '1':   tab[j][i] = 'X';
                        tab2[j][i] = 'O';
                        (*coups)++;
                        if(count(1, tab2) == 0)
                        {
                            (*coule)++;
                            grille(tab);
                            printf("\nBRAVO ! Vous venez de COULE un petit navire adverse : Nombre de coups(%i/%i), Navires coules (%i/6)\n\n", *coups, COUPS ,*coule);
                        }
                        else
                        {
                            grille(tab);
                            printf("\nBravo ! Vous venez de touche un navire adverse : Nombre de coups(%i/%i), Navires coules (%i/6)\n\n", *coups, COUPS ,*coule);
                        }
                    break;
            case '2':   tab[j][i] = 'X';
                        tab2[j][i] = 'O';
                        (*coups)++;
                        if(count(2, tab2) == 0)
                        {
                            (*coule)++;
                            grille(tab);
                            printf("\nBRAVO ! Vous venez de COULE un petit navire adverse : Nombre de coups(%i/%i), Navires coules (%i/6)\n\n", *coups, COUPS ,*coule);
                        }
                        else
                        {
                            grille(tab);
                            printf("\nBravo ! Vous venez de touche un navire adverse : Nombre de coups(%i/%i), Navires coules (%i/6)\n\n", *coups, COUPS ,*coule);
                        }
                    break;
            case '3':   tab[j][i] = 'X';
                        tab2[j][i] = 'O';
                        (*coups)++;
                        if(count(3, tab2) == 0)
                        {
                           (*coule)++;
                            grille(tab);
                            printf("\nBRAVO ! Vous venez de COULE un navire moyen adverse : Nombre de coups(%i/%i), Navires coules (%i/6)\n\n", *coups, COUPS ,*coule);
                        }
                        else
                        {
                            grille(tab);
                            printf("\nBravo ! Vous venez de touche un navire adverse : Nombre de coups(%i/%i), Navires coules (%i/6)\n\n", *coups, COUPS ,*coule);
                        }
                    break;
            case '4':   tab[j][i] = 'X';
                        tab2[j][i] = 'O';
                        (*coups)++;
                        if(count(4, tab2) == 0)
                        {
                            (*coule)++;
                            grille(tab);
                            printf("\nBRAVO ! Vous venez de COULE un navire moyen adverse : Nombre de coups(%i/%i), Navires coules (%i/6)\n\n", *coups, COUPS ,*coule);
                        }
                        else
                        {
                            grille(tab);
                            printf("\nBravo ! Vous venez de touche un navire adverse : Nombre de coups(%i/%i), Navires coules (%i/6))\n\n", *coups, COUPS ,*coule);
                        }
                    break;
            case '5':   tab[j][i] = 'X';
                        tab2[j][i] = 'O';
                        (*coups)++;
                        if(count(5, tab2) == 0)
                        {
                            (*coule)++;
                            grille(tab);
                            printf("\nBRAVO ! Vous venez de COULE un grand navire adverse : Nombre de coups(%i/%i), Navires coules (%i/6)\n\n", *coups, COUPS ,*coule);
                        }
                        else
                        {
                            grille(tab);
                            printf("\nBravo ! Vous venez de touche un navire adverse : Nombre de coups(%i/%i), Navires coules (%i/6)\n\n", *coups, COUPS ,*coule);
                        }
                    break;
            case '6':   tab[j][i] = 'X';
                        tab2[j][i] = 'O';
                        (*coups)++;
                        if(count(6, tab2) == 0)
                        {
                            (*coule)++;
                            grille(tab);
                            printf("\nBRAVO ! Vous venez de COULE un navire imperial adverse : Nombre de coups(%i/%i), Navires coules (%i/6)\n\n", *coups, COUPS ,*coule);
                        }
                        else
                        {
                            grille(tab);
                            printf("\nBravo ! Vous venez de touche un navire adverse : Nombre de coups(%i/%i), Navires coules (%i/6)\n\n", *coups, COUPS ,*coule);
                        }
                    break;
            default:    tab[j][i] = 'O';
                        (*coups)++;
                        grille(tab);
                        printf("\nMince, c'est rate ! On fera mieux la prochaine fois mousaillon : Nombre de coups(%i/%i), Navires coules (%i/6)\n\n", *coups, COUPS ,*coule);
                break;
            }
    }
    else
    {
        printf("\nMille sabord ! On a deja tire ici ! Fait plus attention !\n\n");
    }

}

int changement(char choix)
{
    switch(choix)
    {
        case 'a':
        case 'A':   return 0;
                break;

        case 'b':
        case 'B':   return 1;
                break;

        case 'c':
        case 'C':   return 2;
                break;

        case 'd':
        case 'D':   return 3;
                break;

        case 'e':
        case 'E':   return 4;
                break;

        case 'f':
        case 'F':   return 5;
                break;

        case 'g':
        case 'G':   return 6;
                break;

        case 'h':
        case 'H':   return 7;
                break;

        case 'i':
        case 'I':   return 8;
                break;

        default :   return 9;
                break;
    }
}

void resultat(char tab[TAILLEGRILLE][TAILLEGRILLE], char tab2[TAILLEGRILLE][TAILLEGRILLE], char nom[MAX_NOM])
{
    int espacement = 15;
    char i = ' ', choix = ' ', caracSortie = ' ';
    char nomComplet[20] = "";
    FILE *source = NULL;

    //FIND SCORES
    strcat(nomComplet, "player");
    strcat(nomComplet, nom);
    strcat(nomComplet, ".txt");
    source = fopen(nomComplet, "r");

    system("cls");
    //HEADER
    printf("\n\n%*c******\n",espacement,i);
    printf("%*cSCORES\n",espacement,i);
    printf("%*c******\n",espacement,i);
    //DIALOGUE ET CHOICES
    if(source != NULL)
    {
        printf("Voici la liste de tes scores %s !\n\n", nom);
        do
        {
            caracSortie = fgetc(source);
            printf("%c", caracSortie);
        }while(caracSortie != EOF);
    }
    else
    {
        printf("\n\nTU n'as pas encore de score mousaillon ! Va donc en mer pour en avoir !");
    }
    fclose(source);
    printf("\n\nQue souhaites-tu faire ?\n");
    printf("-Entre la lettre [j] pour JOUER\n");
    printf("-Entre la lettre [a] pour le MENU D'AIDE\n");
    printf("-Entre la lettre [m] pour le MENU PRINCIPAL\n");
    printf("-Entre la lettre [q] pour nous QUITTER\n\n");
    printf("Choisis ta lettre mousaillon: ");
    fflush(stdin);
    scanf("%c", &choix);
    //CHOICE VERIFICATION
    while((choix != 'j') && (choix != 'm') && (choix != 'a') && (choix != 'q'))
    {
        printf("\nAurais-tu trop bu mousaillon ?\n\n");
        printf("Que souhaites-tu faire ?\n");
        printf("-Entre la lettre [j] pour JOUER\n");
        printf("-Entre la lettre [a] pour le MENU D'AIDE\n");
        printf("-Entre la lettre [m] pour le MENU PRINCIPAL\n");
        printf("-Entre la lettre [q] pour nous QUITTER\n\n");
        printf("Et choisis une lettre possible s'il te plait: ");
        fflush(stdin);
        scanf("%c", &choix);
    }
    //NAVIGATION MENU
    switch(choix)
    {
    case 'j' : jouer(tab, tab2, nom);
        break;
    case 'a' : menuAide(tab, tab2, nom);
        break;
    case 'm' : menuPrincipal(tab, tab2, nom);
        break;
    default : return EXIT_SUCCESS;
        }
}

int count(int number, char tab[TAILLEGRILLE][TAILLEGRILLE])
{
    int i, j , n, sum = 0;

    for(i = 0; i < TAILLEGRILLE; i++)
    {
        for(j = 0; j < TAILLEGRILLE; j++)
        {
            n = tab[i][j] - 48;
            if(n == number)
            {
                sum++;
            }
        }
    }

    return sum;
}
