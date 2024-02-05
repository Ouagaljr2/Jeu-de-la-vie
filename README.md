Description

Ce projet est un jeu de la vie (Game of Life) réalisé en utilisant le langage de programmation C. Le jeu de la vie est une automaton cellulaire inventée par John Conway dans les années 1970. Le projet utilise la bibliothèque Cairo pour générer des représentations graphiques du jeu.
Structure du Projet

Le projet est organisé de la manière suivante :

    bin: Le répertoire qui contiendra l'exécutable principal (main).
    doc: Le répertoire qui contiendra la documentation générée par Doxygen.
    include: Le répertoire qui contient les fichiers d'en-tête (headers).
    lib: Le répertoire qui contiendra la bibliothèque statique libjeu.a.
    obj: Le répertoire qui contiendra les fichiers objet générés lors de la compilation.
    src: Le répertoire qui contient les fichiers source du projet.
    Makefile: Le fichier Makefile qui décrit les règles de compilation et de construction du projet.

Dépendances

Le projet dépend de la bibliothèque Cairo, ainsi que des bibliothèques standard comme math et X11.
Compilation

Pour compiler le projet, utilisez la commande make dans le répertoire principal du projet. Cela générera l'exécutable main dans le répertoire bin. Vous pouvez spécifier le mode de compilation en modifiant la variable MODE dans le Makefile.

make

Nettoyage

Pour nettoyer les fichiers générés lors de la compilation, utilisez la commande make clean.

make clean

Documentation

La documentation du projet peut être générée en utilisant la commande make docs. Les fichiers générés seront placés dans le répertoire doc.

make docs

Distribution

Pour créer une archive distribuable du projet, utilisez la commande make dist. Cela créera une archive tar.xz avec le nom "MahamatOuagal-GoL-v5.4.tar.xz" contenant les fichiers nécessaires.

make dist

Auteur

Ce projet a été développé par Mahamat Ouagal    
