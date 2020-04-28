## Objectif 1 : Programmer la DFT en simulation sur un tableau de données imposés

### Description

Le programme *main* appelle une fonction `M2dft()` écrite en assemleur qui renvoie le module mis au carré de la DFT de rang *k*. Le paramètre *k* (de 0 à 63) est fourni à la fonction ainsi que l'adresse du tableau de données imposé.


### Guide de l'étudiant

#### Choix du jeu de test

Quatre tableaux sont importés dans `principal.c` : un tableau généré, et les trois tableaux qui sont les *jeux de test officiels*. Il est possible de choisir de les utiliser, en changeant le premier argument envoyé à `M2dft()` (`principal.c`, ligne 19).

#### Validation des tests

Pour vérifier les valeurs intermédiaires calculées, il est possible de mettre un point d'arrêt dans `dft.s` sur la ligne 44. Les registres R4 et R0 contiendront alors respectivement les parties réelles et imaginaires. Les modules au carrés sont stockés dans un tableau d'entiers `tab`, dans `principal.c`.


### À propos

Dépôt de Damien Molina, Gabin Noblet et Paul Thebault.  
Les parties précédentes sont toujours disponibles dans l'historique du dépôt.