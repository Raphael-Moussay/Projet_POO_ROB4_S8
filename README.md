# Projet PinoCPP : Simulateur de Bras Robotique Articulé

MOUSSAY Raphaël et ORIEUX Jean

# Utilisation et compilation du code

## Pré-requis

- Un compilateur C++ compatible C++17 (ex: `g++`).
- Outils : `ibeigen3-dev` • `pinocchio (pip install pin)` • `libgtest-dev `• `valgrind`
- `make`.

Ce TP est structuré avec :

- Les headers dans `inc/`
- Les sources dans `src/`
- Les objets dans `build/`
- Le binaire dans `bin/`

## Compilation et exécution

Depuis le dossier ???????????:

### Nécessaire :

```bash
make #Compiler
./bin/run #Executer
export PKG_CONFIG_PATH="$CONDA_PREFIX/lib/pkgconfig:$PKG_CONFIG_PATH" #Pour Pinnochio
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
Quel exercice voulez-vous tester ? (1, 2 ou q pour quitter) : 
```

Il suffit de rentrer la valeur de votre choix parmi celles proposées : 1, 2 ou q

# Compte rendu

## Exercice 1 : Conception UML et hiérarchie de joints
