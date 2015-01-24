#!/bin/bash

read -p "Lancez le jeu ? Tapez o si oui, autre chose sinon." lancer_jeu; if [ $lancer_jeu = 'o' ];then './executable'; fi

#@echo "Executable crée ! Lancez donc le jeu avec la commande ./executable, bon jeu !"
#@./lancer_jeu.sh
