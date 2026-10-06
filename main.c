#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ===================== STRUCTURES ===================== */

typedef struct Livre {
    int numero;
    char titre[100];
    char auteur[100];
    int annee;
    int exemplaires;
    struct Livre *gauche, *droite;
} Livre;

typedef struct Emprunt {
    int numLivre;
    int numEtudiant;
    char nomEtudiant[100];
    time_t dateEmprunt;
    time_t dateRetour;
    struct Emprunt *suivant;
} Emprunt;

/* ===================== VARIABLES GLOBALES ===================== */
Livre *racine = NULL;
Emprunt *listeEmprunts = NULL;

/* ===================== ABR LIVRES ===================== */

Livre* creerLivre() {
    Livre *l = malloc(sizeof(Livre));
    printf("Numero du livre : ");
    scanf("%d", &l->numero);
    getchar();

    printf("Titre : ");
    gets(l->titre);

    printf("Auteur : ");
    gets(l->auteur);

    printf("Annee d'edition : ");
    scanf("%d", &l->annee);

    printf("Nombre d'exemplaires : ");
    scanf("%d", &l->exemplaires);

    l->gauche = l->droite = NULL;
    return l;
}

Livre* insererLivre(Livre *racine, Livre *l) {
    if (!racine) return l;

    if (l->numero < racine->numero)
        racine->gauche = insererLivre(racine->gauche, l);
    else
        racine->droite = insererLivre(racine->droite, l);

    return racine;
}

void afficherLivres(Livre *racine) {
    if (racine) {
        afficherLivres(racine->gauche);
        printf("📘 %s | Auteur: %s | Année: %d | Exemplaires: %d\n",
               racine->titre,
               racine->auteur,
               racine->annee,
               racine->exemplaires);
        afficherLivres(racine->droite);
    }
}

Livre* rechercherNumero(Livre *racine, int numero) {
    if (racine == NULL) return NULL;
    if (racine->numero == numero) return racine;

    Livre *g = rechercherNumero(racine->gauche, numero);
    if (g != NULL) return g;

    return rechercherNumero(racine->droite, numero);
}

Livre* rechercherTitre(Livre *racine, char *titre) {
    if (!racine) return NULL;
    if (strcmp(racine->titre, titre) == 0) return racine;

    Livre *g = rechercherTitre(racine->gauche, titre);
    if (g) return g;

    return rechercherTitre(racine->droite, titre);
}

/* ===================== LISTE EMPRUNTS ===================== */

Emprunt* emprunterLivre(Emprunt *liste, Livre *racine) {
    int num;
    printf("Numero du livre : ");
    scanf("%d", &num);

    Livre *l = rechercherNumero(racine, num);
    if (!l || l->exemplaires <= 0) {
        printf("❌ Livre indisponible\n");
        return liste;
    }

    Emprunt *e = malloc(sizeof(Emprunt));
    e->numLivre = num;

    printf("Numero etudiant : ");
    scanf("%d", &e->numEtudiant);
    getchar();

    printf("Nom et prenom etudiant : ");
    gets(e->nomEtudiant);

    e->dateEmprunt = time(NULL);

    int jours;
    printf("Duree emprunt (jours) : ");
    scanf("%d", &jours);

    e->dateRetour = e->dateEmprunt + jours * 86400;
    e->suivant = liste;

    l->exemplaires--;

    printf("✅ Livre emprunte avec succes\n");
    return e;
}

void afficherEmprunts(Emprunt *liste) {
    while (liste) {
        printf("📕 Livre %d | Etudiant %s\n", liste->numLivre, liste->nomEtudiant);
        printf("   Emprunté le : %s", ctime(&liste->dateEmprunt));
        printf("   Retour prévu : %s\n", ctime(&liste->dateRetour));
        liste = liste->suivant;
    }
}

Emprunt* retourLivre(Emprunt *liste, Livre *racine) {
    int livre, etu;
    printf("Numero livre : ");
    scanf("%d", &livre);
    printf("Numero etudiant : ");
    scanf("%d", &etu);

    Emprunt *p = liste, *prec = NULL;

    while (p) {
        if (p->numLivre == livre && p->numEtudiant == etu) {
            if (prec)
                prec->suivant = p->suivant;
            else
                liste = p->suivant;

            Livre *l = rechercherNumero(racine, livre);
            if (l) l->exemplaires++;

            free(p);
            printf("✅ Livre retourne\n");
            return liste;
        }
        prec = p;
        p = p->suivant;
    }
    printf("❌ Emprunt introuvable\n");
    return liste;
}

/* ===================== SAUVEGARDE ===================== */

void sauvegarderLivres(Livre *racine, FILE *f) {
    if (racine != NULL) {
        fprintf(f, "%d;%s;%s;%d;%d\n",
                racine->numero,
                racine->titre,
                racine->auteur,
                racine->annee,
                racine->exemplaires);
        sauvegarderLivres(racine->gauche, f);
        sauvegarderLivres(racine->droite, f);
    }
}

void sauvegarderEmprunts(Emprunt *liste) {
    FILE *f = fopen("emprunts.txt", "w");
    if (!f) return;

    while (liste != NULL) {
        fprintf(f, "%d;%d;%s;%ld;%ld\n",
                liste->numLivre,
                liste->numEtudiant,
                liste->nomEtudiant,
                (long)liste->dateEmprunt,
                (long)liste->dateRetour);
        liste = liste->suivant;
    }
    fclose(f);
}

/* ===================== CHARGEMENT ===================== */

Livre* chargerLivres() {
    FILE *f = fopen("livres.txt", "r");
    if (f == NULL) return NULL;

    Livre *racine = NULL;
    int num, annee, exemplaires;
    char titre[100], auteur[100];

    while (fscanf(f, "%d;%99[^;];%99[^;];%d;%d\n",
                  &num, titre, auteur, &annee, &exemplaires) == 5) {
        Livre *l = malloc(sizeof(Livre));
        l->numero = num;
        strcpy(l->titre, titre);
        strcpy(l->auteur, auteur);
        l->annee = annee;
        l->exemplaires = exemplaires;
        l->gauche = l->droite = NULL;

        racine = insererLivre(racine, l);
    }

    fclose(f);
    return racine;
}

Emprunt* chargerEmprunts() {
    FILE *f = fopen("emprunts.txt", "r");
    if (f == NULL) return NULL;

    Emprunt *liste = NULL;
    int numLivre, numEtudiant;
    char nomEtudiant[100];
    long dateE, dateR;

    while (fscanf(f, "%d;%d;%99[^;];%ld;%ld\n",
                  &numLivre, &numEtudiant, nomEtudiant, &dateE, &dateR) == 5) {
        Emprunt *e = malloc(sizeof(Emprunt));
        e->numLivre = numLivre;
        e->numEtudiant = numEtudiant;
        strcpy(e->nomEtudiant, nomEtudiant);
        e->dateEmprunt = (time_t)dateE;
        e->dateRetour = (time_t)dateR;
        e->suivant = liste;
        liste = e;
    }

    fclose(f);
    return liste;
}

/* ===================== MENU ===================== */

void menu() {
    printf("\n===== MENU de la bibliotheque =====\n");
    printf("1. Ajouter un livre\n");
    printf("2. Afficher tous les livres\n");
    printf("3. Rechercher livre par numero\n");
    printf("4. Rechercher livre par titre\n");
    printf("5. Emprunter un livre\n");
    printf("6. Afficher emprunts\n");
    printf("7. Retourner un livre\n");
    printf("0. Quitter\n");
}


/* ===================== MAIN ===================== */

int main() {
    // Chargement des données sauvegardées
    racine = chargerLivres();
    listeEmprunts = chargerEmprunts();

    int choix;
    do {
        menu();
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                Livre *nouveau = creerLivre();
                racine = insererLivre(racine, nouveau);
                FILE *f = fopen("livres.txt", "w");
                if (f) {
                    sauvegarderLivres(racine, f);
                    fclose(f);
                }
                break;
            }

            case 2:
                afficherLivres(racine);
                break;

            case 3: {
                int n;
                printf("Numero : ");
                scanf("%d", &n);
                Livre *l = rechercherNumero(racine, n);
                if (l)
                    printf("📘 %s - %s (%d) | Exemplaires: %d\n",
                           l->titre, l->auteur, l->annee, l->exemplaires);
                else
                    printf("❌ Livre non trouve\n");
                break;
            }

            case 4: {
                char t[100];
                getchar();
                printf("Titre : ");
                gets(t);
                Livre *l = rechercherTitre(racine, t);
                if (l)
                    printf("📘 %s - %s (%d) | Exemplaires: %d\n",
                           l->titre, l->auteur, l->annee, l->exemplaires);
                else
                    printf("❌ Livre non trouve\n");
                break;
            }

            case 5:
                listeEmprunts = emprunterLivre(listeEmprunts, racine);
                sauvegarderEmprunts(listeEmprunts);
                {
                    FILE *f = fopen("livres.txt", "w");
                    if (f) {
                        sauvegarderLivres(racine, f);
                        fclose(f);
                    }
                }
                break;

            case 6:
                afficherEmprunts(listeEmprunts);
                break;

            case 7:
                listeEmprunts = retourLivre(listeEmprunts, racine);
                sauvegarderEmprunts(listeEmprunts);
                {
                    FILE *f = fopen("livres.txt", "w");
                    if (f) {
                        sauvegarderLivres(racine, f);
                        fclose(f);
                    }
                }
                break;
        }
    } while (choix != 0);

    // Sauvegarde finale avant de quitter
    FILE *f = fopen("livres.txt", "w");
    if (f) {
        sauvegarderLivres(racine, f);
        fclose(f);
    }
    sauvegarderEmprunts(listeEmprunts);

    printf("📂 Données sauvegardées. Au revoir !\n");
    return 0;
}
