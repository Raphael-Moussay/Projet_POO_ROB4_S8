# Projet PinoCPP : Simulateur de Bras Robotique Articulé

MOUSSAY Raphaël et ORIEUX Jean

Lien du repo git : [https://github.com/Raphael-Moussay/Projet_POO_ROB4_S8](https://github.com/Raphael-Moussay/Projet_POO_ROB4_S8)

# Utilisation et compilation du code

## Pré-requis

- Un compilateur C++ compatible C++17 (ex: `g++`).
- Outils : `ibeigen3-dev` • `pinocchio (pip install pin)` • `libgtest-dev `• `valgrind`
- `make`.
- Installer pinocchio en suivant les étapes suivantes : [https://stack-of-tasks.github.io/pinocchio/download.html](https://stack-of-tasks.github.io/pinocchio/download.html)

## Compilation et exécution

Ce TP est structuré avec :

- Les headers dans `inc/`
- Les sources dans `src/`
- Les objets dans `build/`
- Le binaire dans `bin/`

Depuis le dossier parent :

### Nécessaire :

```bash
make #Compiler
./bin/run #Executer
```

### Utile :

```bash
make clean #nettoyer les objets
make aclean #Nettoyer + supprimer l'executable
make rebuild #Rebuild complet
```

## Utilisation :

A l'exécution le programme affiche

```bash
Choisissez ce que vous souhaitez faire :
        0 - Exécuter tous les tests
        1 - Tests joints
        2 - Tests bras
        3 - Tests cvecteur
        4 - Exo 4
        q - Quitter
```

Il suffit de rentrer la valeur de votre choix parmi celles proposées : 0, 1, 2, 3, 4 ou q

# Graphique UML

## Télécharger hpp2plantuml:

```bash
pip install hpp2plantuml
```

## Génération du fichier .puml

```
hpp2plantuml -i "inc/*.h" -o projet.puml
```

## **Visualisation**

Installer l'extension Plan UML sur vscode pour visualiser le fichier `projet.puml` ou utiliser un autre outil.

# Doxygen

## Génerer les fichiers nécessaires :

Dans le terminal :

```bash
doxygen
```

## Visualiser :

Ouvrir le fichier `html/index.html` sur un navigateur pour voir la documentation dynamique
