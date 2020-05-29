## Objectif 2 : Faire tourner la DFT «en réel» et gérer le score des 6 joueurs

### Description

Votre objectif ici est d'écrire un programme en C qui, périodiquement (Timer Systick, période 5 à 20ms) fait l'acquisition du signal, calcule la DFT et affecte le score à chacun des 6 joueurs.

### Guide de l'étudiant

#### Choix du scénario simulé
Modifier la valeur définie par *SCENARIO_SIMULE* :

`#define SCENARIO_SIMULE 0x33` pour le "cas simple"

#### Le point d'arrêt
Placer un point d'arrêt à la ligne 51 (`global.scores[i]++;`) permet de s'arrêter juste avant l'ajout d'un point à un joueur.

#### Observation des scores
Ajouter la variable `global.scores` à une *Watch Window* pour visualiser les scores au fil de l’exécution.

#### Visualisations supplémentaires
Deux bits du *GPIOB* sont utilisés lors de l’exécution. Il est possible de les observer avec le *Logic Analyser* :
* Le `portb.1` qui est à 1 lors de l'exécution de la fonction `sys_callback`
* Le `portb.14` qui est mis brièvement à 1 à chaque modification des scores


### À propos

Dépôt de Damien Molina, Gabin Noblet et Paul Thebault.  
Les parties précédentes sont toujours disponibles dans l'historique du dépôt.