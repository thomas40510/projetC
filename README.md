# Projet C : Annuaire et tri de données
> Author : [Thomas PRÉVOST / CSN2024](https://github.com/thomas40510)

## Description
Ce projet, codé dans le cadre du cours de programmation avancée impérative en 2e année à l'ENSTA Bretagne, consiste en la création d'un annuaire trié par ordre alphabétique, depuis un fichier texte.

## Utilisation
Commencer par compiler le programme depuis son dossier : `make`

Appeler ensuite le programme en donnant le fichier à lire en argument :
```bash
./bin/annuaire path_to_file.txt
```

> _NB_: Exécuter `make clean` pour supprimer les fichiers objets et le programme.

> _NB2_: Exécuter `./bin/annuaire path_to_file.txt --display` pour afficher le contenu des listes dans le terminal.

## Implémentation
Le programme est codé en C, et construit l'annuaire à partir du fichier de deux manières : 
- en utilisant une liste chaînée ;
<p align="center">
  <img width=300 src="list.png"/>
</p>
- en utilisant une liste chaînée de listes chaînées.
<p align="center">
  <img width=700 src="llist.png"/>
</p>

Le programme compare alors les temps de traitement par ces deux méthodes.

## Résultat
Le programme affiche dans la console, pour chaque structure, le nombre d'entrées chargées et le temps de traitement.

## Comprendre la console
Lors de l'exécution, plusieurs informations peuvent être affichées dans la console. Pour simplifier la compréhension, elles sont étiquetées :
- `/?/[Log/I]:` : informations sur le programme ;
- `/!!/[Log/E]:` : erreurs lors de l'exécution.
