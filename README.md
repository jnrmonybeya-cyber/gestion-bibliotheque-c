# 📚 Système de Gestion de Bibliothèque en C

![Langage](https://img.shields.io/badge/Langage-C-blue?style=flat-square&logo=c)
![IDE](https://img.shields.io/badge/IDE-Code%3A%3ABlocks-orange?style=flat-square)
![Compilateur](https://img.shields.io/badge/Compilateur-GCC-green?style=flat-square)
![Statut](https://img.shields.io/badge/Statut-Terminé-brightgreen?style=flat-square)

> Projet réalisé dans le cadre d'un **travail de groupe** — Cours de Structures de Données en langage C.

---

## 📖 Description

Ce projet est une application console développée en **langage C** qui permet de gérer le catalogue et les emprunts d'une bibliothèque. Il a été conçu comme projet de groupe afin de mettre en pratique les **structures de données fondamentales** : l'arbre binaire de recherche (ABR) et la liste chaînée.

L'application permet à un gestionnaire de bibliothèque d'ajouter des livres, de les rechercher, de gérer les emprunts des étudiants et d'assurer la persistance des données entre chaque session.

---

## ✨ Fonctionnalités

| N° | Fonctionnalité | Description |
|----|----------------|-------------|
| 1  | Ajouter un livre | Enregistre un nouveau livre avec titre, auteur, année et nombre d'exemplaires |
| 2  | Afficher tous les livres | Liste l'ensemble du catalogue par ordre de numéro (parcours infixe ABR) |
| 3  | Rechercher par numéro | Retrouve un livre grâce à son numéro unique |
| 4  | Rechercher par titre | Retrouve un livre grâce à son titre |
| 5  | Emprunter un livre | Enregistre un emprunt au nom d'un étudiant avec une durée définie |
| 6  | Afficher les emprunts | Liste tous les emprunts en cours avec les dates |
| 7  | Retourner un livre | Clôture un emprunt et remet l'exemplaire en stock |
| 0  | Quitter | Sauvegarde automatique et fermeture du programme |

---

## 🏗️ Structures de données utilisées

- **Arbre Binaire de Recherche (ABR)** — pour le stockage et la gestion des livres.  
  Permet une recherche efficace en O(log n) selon le numéro du livre.

- **Liste chaînée simple** — pour la gestion des emprunts en cours.  
  Permet l'ajout et la suppression dynamique des emprunts.

---

## 📁 Structure du projet

```
projet structurebibliotheque/
│
├── main.c                              # Code source principal (unique fichier source)
│
├── livres.txt                          # Base de données des livres (générée automatiquement)
├── emprunts.txt                        # Base de données des emprunts (générée automatiquement)
│
├── projet structurebibliotheque.cbp    # Fichier de projet Code::Blocks
├── doxygen/
│   └── doxyfile                        # Configuration pour la génération de documentation Doxygen
│
├── .gitignore                          # Fichiers et dossiers exclus du dépôt Git
└── README.md                           # Documentation du projet (ce fichier)
```

### Détail des fichiers

| Fichier | Rôle |
|---------|------|
| `main.c` | Contient l'intégralité du code source : structures, fonctions ABR, liste chaînée, sauvegarde/chargement, et menu principal |
| `livres.txt` | Fichier texte de persistance des livres. Généré automatiquement au premier ajout. Format : `numero;titre;auteur;annee;exemplaires` |
| `emprunts.txt` | Fichier texte de persistance des emprunts. Format : `numLivre;numEtudiant;nomEtudiant;dateEmprunt;dateRetour` |
| `projet structurebibliotheque.cbp` | Fichier de configuration du projet pour l'IDE Code::Blocks |
| `doxygen/doxyfile` | Fichier de configuration Doxygen pour générer la documentation technique automatique |
| `.gitignore` | Liste des fichiers ignorés par Git (binaires, fichiers de compilation, etc.) |

---

## ⚙️ Installation et compilation

### Prérequis

- [Code::Blocks](http://www.codeblocks.org/downloads) avec **MinGW/GCC** intégré, **ou**
- GCC installé manuellement (Linux/macOS/Windows avec MinGW)

### Option 1 — Via Code::Blocks (recommandé)

1. Cloner le dépôt :
   ```bash
   git clone https://github.com/jnrmonybeya-cyber/gestion-bibliotheque-c.git
   ```
2. Ouvrir le fichier `projet structurebibliotheque.cbp` avec Code::Blocks.
3. Cliquer sur **Build & Run** (F9) pour compiler et lancer le programme.

### Option 2 — Via la ligne de commande (GCC)

1. Cloner le dépôt :
   ```bash
   git clone https://github.com/jnrmonybeya-cyber/gestion-bibliotheque-c.git
   cd "gestion-bibliotheque-c"
   ```
2. Compiler :
   ```bash
   gcc main.c -o bibliotheque -Wall
   ```
3. Exécuter :
   ```bash
   # Linux / macOS
   ./bibliotheque

   # Windows (PowerShell)
   .\bibliotheque.exe
   ```

---

## 🚀 Utilisation

Au lancement, le programme charge automatiquement les données sauvegardées (`livres.txt` et `emprunts.txt`), puis affiche le menu principal :

```
===== MENU de la bibliotheque =====
1. Ajouter un livre
2. Afficher tous les livres
3. Rechercher livre par numero
4. Rechercher livre par titre
5. Emprunter un livre
6. Afficher emprunts
7. Retourner un livre
0. Quitter
Choix :
```

Saisir le numéro correspondant à l'action souhaitée et suivre les instructions à l'écran. À la fermeture (choix `0`), toutes les données sont automatiquement sauvegardées.

---

## 💾 Persistance des données

Les données sont stockées dans deux fichiers texte au format CSV simplifié :

**`livres.txt`**
```
1;Introduction à l'algorithmique;Cormen;2009;5
2;Le langage C;Kernighan;1988;3
```

**`emprunts.txt`**
```
1;2024;Jean Dupont;1700000000;1700259200
```

Ces fichiers sont créés automatiquement à la première utilisation et mis à jour à chaque opération.

---

## 👥 Équipe

Projet réalisé en groupe dans le cadre du cours de **Structures de Données** — Groupe 11.

---

## 📄 Licence

Ce projet est développé à des fins académiques. Toute réutilisation doit mentionner les auteurs originaux.
