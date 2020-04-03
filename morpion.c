#include "game.h" 

#define N 3

int	val(int n)
{
	return(rand() % n);
}


void	init(char plateau[N][N])
{
	int i;
	int j;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			plateau[i][j] = '_';
}
void	pretty_start()
{
	printf("\033[0;31m");		
	printf("L");
	printf("\033[1;31m");		
	printf("e");
	printf("\033[1;32m");		
	printf("t'");
	printf("\033[0;33m");		
	printf("s ");
	printf("\033[01;33m");		
	printf("s");
	printf("\033[0;34m");		
	printf("t");
	printf("\033[1;34m");		
	printf("a");
	printf("\033[0;35m");		
	printf("r");
	printf("\033[1;35m");		
	printf("t ");
	printf("\033[1;36m");		
	printf("!\n\n");
}

void	affiche(char plateau[N][N])
{
	int i;
	int j;

	printf("\033[0m");		
	printf(" -----------------------------------------------\n|");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (plateau[i][j] == 'X')
				printf("\033[1;36m");
			if (plateau[i][j] == 'O')
				printf("\033[1;31m");
			printf("\t%c\t", plateau[i][j]);
			printf("\033[0m");		
			printf("|");
		}
		printf("\n");
		printf("\033[0m");		
		printf(" -----------------------------------------------\n|");
	}
}

int	choisir_menu12q()
{
	int ret = 0;
	printf("\033[1;36m");
	printf("Choisis un mode zeubi: \n");
	printf("\033[1;31m");
	printf("\t1. guerre entre potos \n");
	printf("\033[1;34m");
	printf("\t2. Solo a faire la moula \n");
	printf("\033[0;33m");
	printf("\t3.Jme tire\n");
	scanf("%d", &ret);
	if (ret > 3 || ret < 0)
	{
		printf("\033[0;35mun peu de serieux zeubi\n encore une fois :\033[0m\n");
		ret = choisir_menu12q();
	}
	return (ret);
}

int	not_full(char plateau[N][N])
{
	int i;
	int j;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			if (plateau[i][j] == '_')
				return (1);
	return (0);
}

void	jouer_ordinateur(char plateau[N][N])
{
	int line = val(N);
	int colone = val(N);

	if (plateau[colone][line] != '_')
		jouer_ordinateur(plateau);
	else
		plateau[colone][line] = 'O';
}


void	jouer(char plateau[N][N], int joueur)
{
	int colone, ligne;

	printf("\033[01;33mtu veux jouer ou? \033[0m\n");
	printf("ligne : ");
	scanf("%d", &colone);
	(colone > 0 && colone <= N) ? printf("\033[1;32mok\033[0m\n") : printf("\033[1;31mpas valide\033[0m\n");
	while (!(colone > 0 && colone <= N))
	{
		scanf("%d", &colone);
	(colone > 0 && colone <= N) ? printf("\033[1;32mok\033[0m\n") : printf("\033[1;31mtoujours pas valide\033[0m\n");
	}	
	printf("\ncolone : ");
	scanf("%d", &ligne);
	(ligne > 0 && ligne <= N) ? printf("\033[1;32mok\033[0m\n") : printf("\033[1;31mpas valide\033[0m\n");
	while (!(ligne > 0 && ligne <= N))
	{
		scanf("%d", &ligne);
	(ligne > 0 && ligne <= N) ? printf("\033[1;32mok\033[0m\n") : printf("\033[1;31mtoujours pas valide\033[0m\n");
	}
	if (plateau[colone - 1][ligne - 1] != '_')
	{
		printf("\033[0;33mdeja pleine try again\033[0m\n");
		jouer(plateau, joueur);	
	}
	else	
		plateau[colone - 1][ligne - 1] = ((joueur == 0) ? 'X' : 'O');
}

int	check_line(char plateau[N][N])
{
	int c, l;
	for (l = 0; l < N ; l++)
	{	
		c = 0;
		while(plateau[l][0] != '_' && plateau[l][0] == plateau[l][c] && c < N)
			c++;
		if (c == N)
			return (plateau[l][c - 1]);
	}
	return (0);
}

int	check_colone(char plateau[N][N])
{
	int c, l;
	for (c = 0; c < N ; c++)
	{	
		l = 0;
		while (plateau[0][c] != '_' && plateau[0][c] == plateau[l][c] && l < N)
			l++;
		if (l == N)
			return (plateau[l - 1][c]);
	}
	return (0);
}

int	check_diagonal(char plateau[N][N])
{
	int i = 0;

	while (plateau[0][0] != '_' && plateau[0][0] == plateau[i][i] && i < N)
		i++;
	if (i == N)
		return (plateau[0][0]);
	i = 0;
	while (plateau[0][N - 1] != '_' && plateau[0][N - 1] == plateau[i][N - 1 - i] && i < N)
		i++;
	if (i == N)
		return (plateau[0][N - 1]);
	return (0);
}

int	partie_gagnee_bool(char plateau[N][N])
{
	return ((check_line(plateau)) || (check_colone(plateau)) ||(check_diagonal(plateau)));
}

int	partie_gagnee(char plateau[N][N])
{
	if (check_line(plateau))
		return (check_line(plateau) == 'X' ? 0 : 1);
	else if (check_colone(plateau))
		return (check_colone(plateau) == 'X' ? 0 : 1);
	else if (check_diagonal(plateau))
		return (check_diagonal(plateau) == 'X' ? 0 : 1);
	else
		return (-1);
}

void	jouer_a(char plateau[N][N], int nb_joueur)
{
	int tour = 0;

	while (partie_gagnee(plateau) == -1 && not_full(plateau))
	{
		if (tour % 2 == 0)
			jouer(plateau, 0);
		else if(nb_joueur == 2)
			jouer(plateau, 1);
		else
			jouer_ordinateur(plateau);
		affiche(plateau);
		tour++;
	}
	if (not_full(plateau) && partie_gagnee(plateau) != -1)
	{
	printf("\033[1;35m");
		if (nb_joueur == 2)
			partie_gagnee(plateau) == 0 ? printf("\nJoueur 1 gagne! \n") : printf("\nJoueur 2 gagne! \n");
		else if (nb_joueur == 1)
			partie_gagnee(plateau) == 0 ? printf("\nJoueur  gagne! \n") : printf("\nl'ordinateur gagne! \n t'es eclate au sol un peu\n");
	}
	else
		printf("plateau plein, c'est un match nul !");
}



int	main()
{
	srand(time(NULL));
	char plateau[N][N];
	int nb_joueur, choix_menu;

	init(plateau);
	choix_menu = choisir_menu12q();
	if (choix_menu == 3)
	{
		printf("\033[01;33m");
		printf("A la prochaine !\n");
		return (0);
	}

	pretty_start();

	affiche(plateau);
	jouer_a(plateau, choix_menu == 1 ? 2 : 1);
	return (0);
}
