# Projet IN204 - Pax Britannica

Dans le cadre du cours d'IN204 à l'ENSTA Paris, ce projet vise à produire un jeu s'inspirant de [Pax Britannica](https://github.com/henkboom/pax-britannica/).
Notre projet est un jeu de tir jouable à 1 ou 2 joueurs.

## Table des Matières

    - Installation 
    - Démarrage
    - Comment jouer

## Installation

Le projet requiert les librairies suivantes : 
    
    - [wxWidgets](https://www.wxwidgets.org/) (v3.2.2)
    - [Libao](https://xiph.org/ao/) (v1.2.2+20180113-1.1ubuntu3)
    - Libmpg123 ( (v1.29.3-1build1)
Ainsi que le compilateur [Clang](https://clang.llvm.org/) (v1:14.0-55~exp2)

Pour jouer sous Windows, utilisez `wsl`.

Vous pouvez obtenir les dépendances en utilisant les commandes suivantes dans un terminal:
```
sudo apt-get install libmpg123-dev
sudo apt-get install libao-dev
sudo apt install clang
sudo apt-get install libwxgtk3.0-gtk3-dev
```

Sous Windows, renommez WSL_Makefile en Makefile dans \Pax_Brittanica (supprimez le Makefile par défaut).

## Démarrage

Pour pouvoir jouer, rendez-vous dans /Pax_Brittanica et dans un terminal utilisez `make` puis `make run`.
Sur la page d'accueil, sélectionnez le nombre de joueurs au centre puis lancez la partie en cliquant sur le bouton à gauche.

## Comment jouer

Déplacez le vaisseau rouge avec **WASD** et le vaisseau bleu avec les **touches fléchées**.
Restez appuyé sur **espace** et **entrée** pour tirer.

Éliminez les ennemis pour gagner des points, et évitez les collisions !
