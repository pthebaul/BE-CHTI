## Objectif 4 : Projet Final

### Description

Votre dernier objectif  sera de réunir tout votre travail en un seul projet qui devra tout traiter: sur une séquence de tir LASER de votre choix, votre logiciel devra scorer comme prévu, et lancer le son associé.


### Guide de l'étudiant

#### Le point d'arrêt
Placer un point d'arrêt à la ligne 87 (`etat.position = 0;`) permet de s'arrêter juste après l'ajout d'un point à un joueur.

#### Observation des scores
Ajouter la variable `global.scores` à une *Watch Window* pour visualiser les scores au fil de l’exécution.

#### Afficher le son dans le débugueur :

1. Ouvrir le Logic Analyzer
2. Cliquer sur Setup
3. Ajouter un nouveau signal *TIM3_CCR3* en mode analogique.
4. Lancer l'exécution.

Et si le son n'est pas entièrement visible :

5. Dans *Zoom*, cliquer sur *All*
6. Dans *Min/Max*, cliquer sur *Auto*

#### Visualisations optionnelles
Deux bits du *GPIOB* sont utilisés lors de l’exécution. Il est possible de les observer avec le *Logic Analyser* :
* Le `portb.1` qui est à 1 lors de l'exécution de la fonction `sys_callback`
* Le `portb.14` qui est mis brièvement à 1 à chaque modification des scores

### À propos

Dépôt de Damien Molina, Gabin Noblet et Paul Thebault.  
Les parties précédentes sont toujours disponibles dans l'historique du dépôt.
