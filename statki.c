#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define N 11
void menu_2(char tab[N][N],char tab2[N][N], char tab_p[N][N], char tab2_p[N][N],int *licznik, int *licznik2);
void menu(char tab[N][N],char tab2[N][N], char tab_p[N][N], char tab2_p[N][N],int *licznik, int *licznik2);
void morze(char tab[N][N])
{	
	int i,j;
	printf("\x1b[2J");
	printf("\x1b[0;0H");
	for (i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
			printf("%c",tab[i][j]);
		printf("\n");    
	}        
	printf("\n");
	
}
void zerowanie (char tab[N][N])
{
		int i = 1;
		int j = 1;
	for (i=1; i<N; i++)
	{
		for(j=1; j<N; j++)
			if (tab[i][j] != '.') tab[i][j] = '.';
	}
}
void morze2(char tab[N][N],char tab_p[N][N])
{	
	int i,j;
	
	printf("\x1b[2J");
	printf("\x1b[0;0H");
	for (i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			if(tab[i][j] == 'o')
				printf("\x1b[34;1m%c\033[0m",tab[i][j]);
			else if(tab[i][j] == 'x')
				printf("\x1b[31;1m%c\033[0m",tab[i][j]);
			else	
				printf("%c",tab[i][j]);
		}
		printf("\n");    
	}        
	printf("\n");
	
	for (i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			if(tab_p[i][j] == 'o')
				printf("\x1b[34;1m%c\033[0m",tab_p[i][j]);
			else if(tab_p[i][j] == 'x')
				printf("\x1b[31;1m%c\033[0m",tab_p[i][j]);
			else
				printf("%c",tab_p[i][j]);
		}
		printf("\n");    
	}        
	printf("\n");
}

int abc(char litera)
{
	return (int)(litera) - 96;

}

void ogranicza(char tab[N][N])
{
	int i,j;
	for (i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
			if (tab[i][j] == '#')
			{
				if (tab[i-1][j] == '.') tab[i-1][j] = ' ';	
				if (tab[i-1][j+1] == '.') tab[i-1][j+1] = ' ';	
				if (tab[i-1][j-1] == '.') tab[i-1][j-1] = ' ';	
				if (tab[i][j-1] == '.') tab[i][j-1] = ' ';	
				if (tab[i][j+1] == '.') tab[i][j+1] = ' ';	
				if (tab[i+1][j-1] == '.') tab[i+1][j-1] = ' ';	
				if (tab[i+1][j] == '.') tab[i+1][j] = ' ';	
				if (tab[i+1][j+1] == '.') tab[i+1][j+1] = ' ';	
			}	
	}
}

void czysc_znaki(char tab[N][N])
{
	int i,j;
	for (i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
			if (tab[i][j] == '.') tab[i][j] = ' ';
	}
}
void statki_gracza(char tab[N][N])
{
	morze(tab);
	int y,p;
	char x;
	int i_j = 4,i_d=3,i_t = 2,i_c = 1;
	while(1)
	{
		while(i_j>0)
		{
			printf("Wybierz pozycje dla %d jednomasztowców!(np.a5)\n",i_j);
			scanf ("%c%d",&x,&y);
			
			if (tab[abc(x)][y] == '.')
			{	
				tab[abc(x)][y] = '#';
				i_j = i_j - 1;
			}
			ogranicza(tab);
			morze(tab);
		}
		
		while(i_d>0)
		{
			printf("Wybierz pozycje dla %d dwumasztowców!(np.a5)\n",i_d);
			scanf ("%c%d",&x,&y);
			if (tab[abc(x)][y] == '.')
			{	
				tab[abc(x)][y] = '#';
				morze(tab);
				printf("Poziomo(0)/Pionowo(1)?\n");
				scanf("%d",&p);
				if(p == 0)
				{
					if(tab[abc(x)][y+1]	== '.')
					{
						tab[abc(x)][y+1] = '#';
						i_d = i_d - 1;
					}	
					else 
 					{
						printf("Pole było zajęte!\n");
						tab[abc(x)][y] = '.';
						usleep(2000000);								
					}		
				}
				else if(p == 1)
				{
					if(tab[abc(x)+1][y]	== '.')
					{
						tab[abc(x)+1][y] = '#';
						i_d = i_d - 1;
					}	
					else
					{
						printf("Pole było zajęte!\n");
						tab[abc(x)][y] = '.';
						usleep(2000000);
					}
				}
				ogranicza(tab);
				morze(tab);
			}
		}
		
		while(i_t>0)
		{
			printf("Wybierz pozycje dla %d trójmasztowców!(np.a5)\n",i_t);
			scanf ("%c%d",&x,&y);
			if (tab[abc(x)][y] == '.')
			{	
				tab[abc(x)][y] = '#';
				morze(tab);
				printf("Poziomo(0)/Pionowo(1)?\n");
				scanf("%d",&p);
				if(p == 0)
				{
					if(tab[abc(x)][y+1]	== '.' && tab[abc(x)][y+2] == '.')
					{
						tab[abc(x)][y+1]	= '#';
						tab[abc(x)][y+2] = '#';
						i_t = i_t - 1;
					}	
					else
					{
						printf("Pole było zajęte!\n");
						tab[abc(x)][y] = '.';
						usleep(2000000);
					}		
				}
				else if(p == 1)
				{
					if(tab[abc(x)+1][y]	== '.' && tab[abc(x)+2][y] == '.')
					{
						tab[abc(x)+1][y] = '#';
						tab[abc(x)+2][y] = '#';
						i_t = i_t - 1;
					}	
					else	
					{
						printf("Pole było zajęte!\n");
						tab[abc(x)][y] = '.';
						usleep(2000000);
					}
				}
				ogranicza(tab);
				morze(tab);
			}
		}
		
		while(i_c>0)
		{
			printf("Wybierz pozycje dla %d czteromasztowca!(np.a5)\n",i_c);
			scanf ("%c%d",&x,&y);
			if (tab[abc(x)][y] == '.')
			{	
				tab[abc(x)][y] = '#';
				morze(tab);
				printf("Poziomo(0)/Pionowo(1)?\n");
				scanf("%d",&p);
				if(p == 0)
				{
					if(tab[abc(x)][y+1]	== '.' && tab[abc(x)][y+2] == '.' && tab[abc(x)][y+3])
					{
						tab[abc(x)][y+1]	= '#';
						tab[abc(x)][y+2] = '#';
						tab[abc(x)][y+3] = '#';
						i_c = i_c - 1;
					}	
					else
					{
						printf("Pole było zajęte!\n");
						tab[abc(x)][y] = '.';
						usleep(2000000);
					}		
				}
				else if(p == 1)
				{
					if(tab[abc(x)+1][y]	== '.' && tab[abc(x)+2][y] == '.' && tab[abc(x)+3][y] == '.')
					{
						tab[abc(x)+1][y] = '#';
						tab[abc(x)+2][y] = '#';
						tab[abc(x)+3][y] = '#';
						i_c = i_c - 1;
					}	
					else	
					{
						printf("Pole było zajęte!\n");
						tab[abc(x)][y] = '.';
						usleep(2000000);							
					}
				}
				ogranicza(tab);
				morze(tab);
			}
		}
		czysc_znaki(tab);
		morze(tab);
		break;
	}
	
}
void statki_kom(char tab[N][N])
{
	int x,y,p;
	int i_j = 4,i_d=3,i_t = 2,i_c = 1;
	srand(time(0));
	while(1)
	{
		while(i_j>0)
		{
			x = rand() % 10 + 1;
			y = rand() % 10 + 1;
			if (tab[x][y] == '.')
			{	
				tab[x][y] = '#';
				i_j = i_j - 1;
			}
			ogranicza(tab);
		}
		
		while(i_d>0)
		{
			x = rand() % 10 + 1;
			y = rand() % 10 + 1;
			if (tab[x][y] == '.')
			{	
				p = rand() % 2;
				if(p == 0)
				{
					if(tab[x][y+1]	== '.')
					{
						tab[x][y] = '#';
						tab[x][y+1] = '#';
						i_d = i_d - 1;
					}	
				}
				else if(p == 1)
				{
					if(tab[x+1][y]	== '.')
					{
						tab[x+1][y] = '#';
						tab[x][y] = '#';
						i_d = i_d - 1;
					}
				}
			}
			ogranicza(tab);
		}
		
		while(i_t>0)
		{
			x = rand() % 10 + 1;
			y = rand() % 10 + 1;
			if (tab[x][y] == '.')
			{	
				p = rand() % 2;
				if(p == 0)
				{
					if(tab[x][y+1]	== '.' && tab[x][y+2] == '.')
					{
						tab[x][y] = '#';
						tab[x][y+1]	= '#';
						tab[x][y+2] = '#';
						i_t = i_t - 1;
					}		
				}
				else if(p == 1)
				{
					if(tab[x+1][y]	== '.' && tab[x+2][y] == '.')
					{
						tab[x][y] = '#';
						tab[x+1][y] = '#';
						tab[x+2][y] = '#';
						i_t = i_t - 1;
					}	
				}
			}
			ogranicza(tab);
		}
		
		while(i_c>0)
		{
			x = rand() % 10 + 1;
			y = rand() % 10 + 1;
			if (tab[x][y] == '.')
			{	
				p = rand() % 2;
				if(p == 0)
				{
					if(tab[x][y+1]	== '.' && tab[x][y+2] == '.' && tab[x][y+3] == '.')
					{
						tab[x][y] = '#';
						tab[x][y+1]	= '#';
						tab[x][y+2] = '#';
						tab[x][y+3] = '#';
						i_c = i_c - 1;
					}	
				}
				else if(p == 1)
				{
					if(tab[x+1][y]	== '.' && tab[x+2][y] == '.' && tab[x+3][y] == '.')
					{
						tab[x][y] = '#';
						tab[x+1][y] = '#';
						tab[x+2][y] = '#';
						tab[x+3][y] = '#';
						i_c = i_c - 1;
					}	
				}
			}
			ogranicza(tab);
		}
		czysc_znaki(tab);
		break;
	}
	
}

void zapis(char tab[N][N],char tab2[N][N], char tab_p[N][N], char tab2_p[N][N], int *licznik, int *licznik2)
{
	FILE *gra;
	gra = fopen("statki.txt","w");
		int i,j;	
		for (i=0; i<N; i++)
		{
			for(j=0; j<N; j++)
				fprintf(gra,"%c",tab[i][j]);    //tablica gracza
		}
		
		for (i=0; i<N; i++)
		{
			for(j=0; j<N; j++)
				fprintf(gra,"%c",tab2[i][j]);    //tablica komputera
		}       
		
		for (i=0; i<N; i++)
		{
			for(j=0; j<N; j++)
				fprintf(gra,"%c",tab_p[i][j]);    //tablica pomocnicza gracza
		}
		
		for (i=0; i<N; i++)
		{
			for(j=0; j<N; j++)
				fprintf(gra,"%c",tab2_p[i][j]);    //tablica pomocnicza komputera
		}
		
		fprintf(gra,"%d\n",*licznik);
		fprintf(gra,"%d",*licznik2);
	fclose(gra);
}

void odczyt(char tab[N][N], char tab2[N][N], char tab_p[N][N], char tab2_p[N][N],int *licznik, int *licznik2)
{
	FILE *gra;
	gra = fopen("statki.txt","r");
	int i,j;
	for (i=0; i<N; i++)
		{
			for(j=0; j<N; j++)
				fscanf(gra,"%c",&tab[i][j]);
		}
	for (i=0; i<N; i++)
		{
			for(j=0; j<N; j++)
				fscanf(gra,"%c",&tab2[i][j]);
		}
	for (i=0; i<N; i++)
		{
			for(j=0; j<N; j++)
				fscanf(gra,"%c",&tab_p[i][j]);
		}
	for (i=0; i<N; i++)
		{
			for(j=0; j<N; j++)
				fscanf(gra,"%c",&tab2_p[i][j]);
		}
	fscanf(gra,"%d",licznik);
	fscanf(gra,"%d",licznik2);
	fclose(gra);
}
void atak_g(char tab[N][N],char tab2[N][N], char tab_p[N][N], char tab2_p[N][N],int *licznik, int *licznik2)
{
	morze2(tab,tab_p);
	int y;
	char x;
	printf("Zostało do zniszczenia %d pól, które pole atakujemy?...",*licznik);
	printf("\n");
	scanf("%c%d",&x,&y);
	if (x == 'm' && y == 1)
		menu_2(tab,tab2,tab_p,tab2_p,licznik,licznik2);
	else if (tab_p[abc(x)][y] == '.')
	{
		
		if (tab2[abc(x)][y] == '#')
		{
			*licznik -= 1;
			tab_p[abc(x)][y] = 'x';
			tab2[abc(x)][y] = 'x';
			morze2(tab,tab_p);
			printf("Brawo Trafiłeś, pozostało %d pól do zestrzelenia!\n",*licznik);
			usleep(1500000);
			
		}
		else
		{
			
			tab_p[abc(x)][y] = 'o';
			tab2[abc(x)][y] = 'o';
			morze2(tab,tab_p);
			printf("Niestety nie trafiłeś!\n");
			usleep(1500000);
		}
	}	
	else
	{	
		atak_g(tab,tab2,tab_p,tab2_p,licznik,licznik2);
	}
}
void atak_k(char tab[N][N],char tab2[N][N],char tab_p[N][N], char tab2_p[N][N], int * licznik2)
{
	int xk,y;
	morze2(tab,tab_p);
	printf("Czas na atak rywala!\n");
	usleep(1000000);
	srand(time(NULL));
	xk = rand() % 10 + 1;
	y = rand() % 10 + 1;
	if(tab2_p[xk][y] == '.')
	{
		if(tab[xk][y] == '#')
		{
			*licznik2 -= 1;
			printf("\n");
			tab[xk][y] = 'x';
			tab2_p[xk][y] = 'x';
			morze2(tab,tab_p);
			printf("Dostałeś! Pozostało Ci %d żyć!\n",*licznik2);
			usleep(2000000);
			}
		else
		{
			tab[xk][y] = 'o';
			tab2_p[xk][y] = 'o';
			printf("\n");
			morze2(tab,tab_p);
			printf("Udało się, nie oberwałeś!\n");
			usleep(2000000);
		}
	}
	else
		atak_k(tab,tab2,tab_p,tab2_p,licznik2);
}
void jeszcze_raz(char tab[N][N],char tab2[N][N], char tab_p[N][N], char tab2_p[N][N],int *licznik, int *licznik2)
{
	int jeszcze;
	printf("Chesz zagrać jeszcze raz?(0/1)\n");
	scanf("%d",&jeszcze);
	if (jeszcze == 1)
	{
		zerowanie(tab);
		zerowanie(tab2);
		zerowanie(tab_p);
		zerowanie(tab2_p);
		menu(tab,tab2,tab_p,tab2_p,licznik,licznik2);
	}
	else
		system("exit");
}




void _gra(char tab[N][N],char tab2[N][N], char tab_p[N][N], char tab2_p[N][N],int *licznik, int *licznik2)
{
	while(1)
	{
		atak_g(tab,tab2,tab_p,tab2_p,licznik,licznik2);
		if (*licznik == 0)
		{
			printf("\x1b[2J");
			printf("\x1b[0;0H");
			printf("----------------\n");
			printf("\033[1;31mBRAWO WYGRAŁEŚ!!\033[0m\n");
			printf("----------------\n");
			jeszcze_raz(tab,tab2,tab_p,tab2_p,licznik,licznik2);
			break;
		}
		atak_k(tab,tab2,tab_p,tab2_p,licznik2);
		if(*licznik2 == 0)
		{
			printf("\x1b[2J");
			printf("\x1b[0;0H");
			printf("--------------------\n");
			printf("\033[1;31mNIESTETY PRZEGRAŁEŚ!!\033[0m\n");
			printf("--------------------\n");
			jeszcze_raz(tab,tab2,tab_p,tab2_p,licznik,licznik2);
			break;
		}
	}
}
void menu_2(char tab[N][N],char tab2[N][N],char tab_p[N][N], char tab2_p[N][N],int *licznik, int*licznik2)
{
	printf("\x1b[2J");
	printf("\x1b[0;0H");
	printf("----------------------\n");
	printf("--------MENU:---------\n");
	printf("1.Wznawiamy gre\n");
	printf("2.Zapisz gre\n");
	printf("3.Odczytujemy gre\n");
	printf("----------------------\n");
	printf("----------------------\n");
	int b;
	scanf("%d",&b);
	switch(b)
	{
		case 1:
			_gra(tab,tab2,tab_p,tab2_p,licznik,licznik2);
		break;
		case 2:
			zapis(tab,tab2,tab_p,tab2_p,licznik,licznik2);
			printf("Gra została zapisana!!\n");
			usleep(1000000);
			printf("\x1b[2J");
			menu_2(tab,tab2,tab_p,tab2_p,licznik,licznik2);
		break;
		case 3:
			odczyt(tab,tab2,tab_p,tab2_p,licznik,licznik2);
			printf("Gra została odczytana!!\n");
			usleep(1000000);
			printf("\x1b[2J");
			menu_2(tab,tab2,tab_p,tab2_p,licznik,licznik2);
		break;
	}	
}
void menu(char tab[N][N],char tab2[N][N], char tab_p[N][N], char tab2_p[N][N],int *licznik, int *licznik2)
{
	printf("\x1b[2J");
	printf("\x1b[0;0H");
	printf("----------------------\n");
	printf("ZACZYNAMY GRE W STATKI\n");
	printf("----------------------\n\n");
	printf("--------MENU:---------\n");
	printf("1.Rozpoczynamy gre\n");
	printf("2.Odczytujemy gre\n");
	printf("3.Koniec gry\n");
	printf("----------------------\n");	
	printf("Podczas swojej tury\nwpisz\"m1\"aby wrócić\n     do menu.\n");
	printf("----------------------\n");	
	int a;
	scanf("%d",&a);
	switch(a)
	{
		case 1:
			statki_kom(tab2);
			statki_gracza(tab);
			_gra(tab,tab2,tab_p,tab2_p,licznik,licznik2);
		break;
		case 2:
			odczyt(tab,tab2,tab_p,tab2_p,licznik,licznik2);
			printf("Gra została odczytana!!\n");
			usleep(1000000);
			printf("\x1b[2J");
			while(1)
			{
				atak_g(tab,tab2,tab_p,tab2_p,licznik,licznik2);
				if (*licznik == 0)
				{
					printf("\x1b[2J");
					printf("\x1b[0;0H");
					printf("----------------\n");
					printf("\033[1;31mBRAWO WYGRAŁEŚ!!\033[0m\n");
					printf("----------------\n");
					jeszcze_raz(tab,tab2,tab_p,tab2_p,licznik,licznik2);
					break;
				}
				atak_k(tab,tab2,tab_p,tab2_p,licznik2);
				if(*licznik2 == 0)
				{
					printf("\x1b[2J");
					printf("\x1b[0;0H");
					printf("--------------------\n");
					printf("\033[1;31mNIESTETY PRZEGRAŁEŚ!!\033[0m\n");
					printf("--------------------\n");
					jeszcze_raz(tab,tab2,tab_p,tab2_p,licznik,licznik2);
					break;
				}
			}
		break;
		case 3:
			system("exit");
		break;
	}
}

int main()
{ 
	int licznik = 20, licznik2 = 20;
	char tab[N][N]={
							{' ','1','2','3','4','5','6','7','8','9','0'},
							{'A','.','.','.','.','.','.','.','.','.','.'},
							{'B','.','.','.','.','.','.','.','.','.','.'},
							{'C','.','.','.','.','.','.','.','.','.','.'},
							{'D','.','.','.','.','.','.','.','.','.','.'},
							{'E','.','.','.','.','.','.','.','.','.','.'},
							{'F','.','.','.','.','.','.','.','.','.','.'},
							{'G','.','.','.','.','.','.','.','.','.','.'},
							{'H','.','.','.','.','.','.','.','.','.','.'},
							{'I','.','.','.','.','.','.','.','.','.','.'},
							{'J','.','.','.','.','.','.','.','.','.','.'}
						};
	char tab2[N][N]={
							{' ','1','2','3','4','5','6','7','8','9','0'},
							{'A','.','.','.','.','.','.','.','.','.','.'},
							{'B','.','.','.','.','.','.','.','.','.','.'},
							{'C','.','.','.','.','.','.','.','.','.','.'},
							{'D','.','.','.','.','.','.','.','.','.','.'},
							{'E','.','.','.','.','.','.','.','.','.','.'},
							{'F','.','.','.','.','.','.','.','.','.','.'},
							{'G','.','.','.','.','.','.','.','.','.','.'},
							{'H','.','.','.','.','.','.','.','.','.','.'},
							{'I','.','.','.','.','.','.','.','.','.','.'},
							{'J','.','.','.','.','.','.','.','.','.','.'}
						};
	char tab_p[N][N]={
							{' ','1','2','3','4','5','6','7','8','9','0'},
							{'A','.','.','.','.','.','.','.','.','.','.'},
							{'B','.','.','.','.','.','.','.','.','.','.'},
							{'C','.','.','.','.','.','.','.','.','.','.'},
							{'D','.','.','.','.','.','.','.','.','.','.'},
							{'E','.','.','.','.','.','.','.','.','.','.'},
							{'F','.','.','.','.','.','.','.','.','.','.'},
							{'G','.','.','.','.','.','.','.','.','.','.'},
							{'H','.','.','.','.','.','.','.','.','.','.'},
							{'I','.','.','.','.','.','.','.','.','.','.'},
							{'J','.','.','.','.','.','.','.','.','.','.'}
						};	
	char tab2_p[N][N]={
							{' ','1','2','3','4','5','6','7','8','9','0'},
							{'A','.','.','.','.','.','.','.','.','.','.'},
							{'B','.','.','.','.','.','.','.','.','.','.'},
							{'C','.','.','.','.','.','.','.','.','.','.'},
							{'D','.','.','.','.','.','.','.','.','.','.'},
							{'E','.','.','.','.','.','.','.','.','.','.'},
							{'F','.','.','.','.','.','.','.','.','.','.'},
							{'G','.','.','.','.','.','.','.','.','.','.'},
							{'H','.','.','.','.','.','.','.','.','.','.'},
							{'I','.','.','.','.','.','.','.','.','.','.'},
							{'J','.','.','.','.','.','.','.','.','.','.'}
						};	
	menu(tab,tab2,tab_p,tab2_p,&licznik,&licznik2);

	return  0;
}
