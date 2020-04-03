#include "game.h"

#define PIERRE 1
#define FEUILLE  PIERRE + 1
#define CISEAUX  FEUILLE + 1
#define NBESSAIS 3
#define POINTSGAGNANTS 3


void	affichage_objet(int obj)
{
	if (obj == PIERRE)
		printf("\033[1;31mPIERRE\033[0m");
	else if (obj == FEUILLE)
		printf("\033[1;31mFEUILLE\033[0m");
	else
		printf("\033[1;31mCISEAUX\033[0m");
	printf("\n");
}

int	valeur_aleatoire(int min, int max)
{
	return  rand() % (max - min + 1) + min - 1;
}

int	choix_ordinateur()
{
	return (valeur_aleatoire(1,3));
}


int	choix_joueur()
{
	int jeu = 0;
	int essai = NBESSAIS;

	while (essai > 0 && !(jeu >= 1 && jeu <= 3))
	{
		printf("\nchoisir un entier entre 1 et 3 : ");
		scanf("%d", &jeu);
		essai--;
		if (jeu > 3 || jeu < 1)
			printf("\033[1;31mvaleur saisie incorrecte\n nombre d'essai restant :\t\033[1;34m%d\n\033[0m", essai);
	}
	if (jeu > 3 || jeu < 1)
	{
		printf("\033[0;32mla valeur a ete choisie aleatoirement\n\033[0m");
		return (valeur_aleatoire(1,3));
	}
	else
		return (jeu);
}

void	score(int cpu, int joueur, int *Scpu, int *Sjoueur)
{
	if (cpu == joueur)
		return;
	else if (joueur == cpu + 1 || joueur == cpu - 2)
			*Sjoueur += 1;
	else 
		*Scpu += 1;
}
void	affichage_partie(int tour, int cpu, int joueur, int Scpu, int Sjoueur)
{
		printf("\n\n\033[1;34mTour : %d \033[0m\n", tour);
		printf("\tl'ordinateur a joue : ");
		affichage_objet(cpu);	
		printf("\n");
		printf("\tle joueur a joue : ");
		affichage_objet(joueur);
		printf("\n");
		printf("\033[1;34mle score est de : \n");
		printf("\tcpu = \033[1;31m%d\t\t-\t", Scpu);
		printf("\033[1;34mjoueur =\033[1;32m %d \n\033[0m", Sjoueur);
}

void	jeu()
{
	int Scpu = 0;
	int Sjoueur = 0;
	int cpu,player;
	int tour = 0;
	int play;

	pretty_start();	
	while (Scpu < POINTSGAGNANTS && Sjoueur < POINTSGAGNANTS)
	{
		cpu = choix_ordinateur();
		player = choix_joueur();
		score(cpu, player, &Scpu, &Sjoueur);
		affichage_partie(++tour, cpu, player, Scpu,Sjoueur);
		printf("\n");
	}
	printf("le gagnant est :    %s", Scpu > Sjoueur ? "\033[1;31mOrdinateur" : "\033[1;32mJoueur");
	printf("\n\n\033[1;35mPlay again?\n \t\033[1;32m1. Yes\n\033[1;31m\t2. No\n");
	scanf("%d", &play);
	
	play == 1 ? jeu() : printf("\n\033[1;35mSee you again!"); 
}

int main()
{
	srand(time(NULL));
	jeu();
	return (0);
}
