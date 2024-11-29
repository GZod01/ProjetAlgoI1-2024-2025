# Compte Rendu 29/11/2024

Au début le programme appelle la fonction `initial` qui initialise le tableau de jeu.

Le programme appelle ensuite une fonction qui affiche le plateau de jeu. Ensuite à chaque tour il appelle une fonction qui permet au joueur de choisir la case dans laquelle il veut jouer.

Une fois que le joueur a choisit la case dans laquelle il veut jouer, le programme appelle une fonction qui permet de déplacer les graines. Pour le choix de cases et le déplacement des graines nous nous basons sur un système de position, chaque case est numérotée de 1 à 12 (1 à 6 pour les cases de A à F et 7 à 12 pour les cases de a à f).

On a ensuite une fonction `intVersPosition` qui permet de convertir la position en coordonnées.

Pendant le déplacement des graines, la fonction d'affichage est appelée à chaque fois qu'une graine bouge pour que le joueur puisse voir le déplacement, on a également ajouté un affichage de couleurs pour les graines, vert pour la graine choisie au départ et rouge pour la graine qui est déplacée.

## A faire pour la prochaine fois
- [ ] Ajout du système de vol de graines
- [ ] Ajout de la fin de partie
- [ ] Ajout potentiel d'une IA