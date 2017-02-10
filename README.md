# hexpuzz
a puzzle game in C


In english:
for install on linux:
sudo apt-get install freeglut3 freeglut3-dev
make

for run: use ./bin/hextris.exe






In frensh
==================================================================

INSTALLATION
	
	Une fois tous les fichiers et dossiers chargés et entreposés DANS UN MÊME DOSSIER, il faut ouvrir une fenêtre de commande.
	Il faut alors naviguer et se rendre dans le dossier dans lequel se trouve les fichiers et dossiers.
	Une fois dans le bon répertoire, rentrer la commande suivante dans l'interpréteur : 'make'
	Dans le cas où le joueur cmpte user de l'aide fournie en jeu, il doit également entrer la commande 'ulimit -s unlimited'
	
	Le jeu et les tests unitaires sont dès lors installés.
	
==================================================================

LANCER LE PROGRAMME

	Une fois le programme installé, rentrer dans l'interpréteur de commande la commande suivante : './bin/hextris.exe' pour démarrer le jeu.
	
	Pour lancer le jeu de tests unitaires déjà réalisés, rentrer dans l'interpréteur de commande la commande : './bin/testunitaire.exe'
	
	NOTE : ces commandes doivent être effectuées en étant dans le répertoire contenant les fichiers et dossiers. De plus, il est nécessaire de relancer la commande 'ulimit -s unlimited' dans chaque console de commande lançant le jeu, à  condition de vouloir user du solveur.
	
==================================================================

DÉSINSTALLATION

	Pour désinstaller le programme, rentrer la commande 'make uninstall' dans la console au niveau du répertoire. ATTENTION ! Cette action entraînera la suppression de l'intégralité des fichiers, ainsi que du répertoire courant. Pour rejouer au jeu après cela, il faut à nouveau le télécharger et l'installer !
	
==================================================================

TRACE DE VALGRIND

	Le projet est à priori optimisé en mémoire. Lancer la commande './valgrind.sh' pour observer les fuites de mémoires dans la console (noter que le jeu sera lancé mais très grandement ralenti !! )
	
==================================================================

AVANCÉE DU PROJET

	Le projet est actuellement entièrement terminé. Le jeu et le solveur sont opérationnels et optimisés en mémoire.Toutes les fonctions majueres possèdent des tests unitaires.
