#!/bin/bash

read -p "Cher utilisateur, quel est ton nom ?" nom
echo -e "Ravi de te connaître, \033[0;34;1m$nom\033[0;0;0m"
read -p "Veux-tu lancer le jeu ? Tape o si oui, autre chose sinon." lancer_jeu; if [ $lancer_jeu = 'o' ];then './executable'; fi
