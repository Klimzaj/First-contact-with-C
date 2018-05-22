#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

 
 
 
 
/* Funkcja czyszcąca planszę */
void wyczysc (char plansza[3][3])
{
    int i,j;
    for (i=0;i<3;i++)
        for (j=0;j<3;j++)
            plansza[i][j]=' ';
 
}
 
 
/* Funkcja rysująca planszę na ekranie */
void wypisz (char plansza[3][3])
{
    system("cls"); // czyśc ekran. Są szybsze sposoby czyszczenia, ale ten jest w miare uniwersalny
 
    printf("[%c][%c][%c]\n",plansza[0][0], plansza[0][1], plansza[0][2]);
    //printf("\n");
    printf("[%c][%c][%c]\n",plansza[1][0], plansza[1][1], plansza[1][2]);
   //printf("\n");
    printf("[%c][%c][%c]\n",plansza[2][0], plansza[2][1], plansza[2][2]);
}
 
int pelna(char plansza[3][3])
{
int i, j;
    for (i=0;i<3;i++)
        for (j=0;j<3;j++)
            if (plansza[i][j] == ' ')
                return 0;
    return 1;
 
}
/*Funkcja ruch_gracza wykona nastepujace czynnosci:
wyswietli plansze,
wczyta ruch gracza,
jezeli gracza wybierze niepoprawne współrzedne pola
lub współrzedne zajetego pola,
funkcja wczyta nowy ruch gracza.*/
void ruch_gracza(char plansza[3][3])
{
    unsigned int i=3, j;
    wypisz(plansza);
    printf("Podaj wiersz i kolumne w ktorej chcesz wstawic krzyzyk\n");
    while ((i>2)||(j>2) || (plansza[i][j]!=' '))
        scanf("%u %u", &i, &j);
    plansza[i][j]='x';
}
/*Funkcja sprawdz sprawdzi:
czy na planszy nie ma trzech takich samych znaków lezacych
w jednej linii (wtedy którys z graczy wygrał),
czy plansza jest juz pełna (wtedy jest remis)*/
char sprawdz(char plansza[3][3])
{
int i;
for (i=0;i<3;i++)
{
    if ( (plansza[i][0]!=' ')
        && (plansza[i][0]==plansza[i][1])
        && (plansza[i][0]==plansza[i][2]))
        return plansza[i][0];
    if ( (plansza[0][i]!=' ')
        &&(plansza[0][i]==plansza[1][i])
        &&(plansza[0][i]==plansza[2][i]) )
return plansza [0][i];
 
} // for
 
if ((plansza[0][0]!=' ')
    && (plansza[0][0]==plansza[1][1])
    && (plansza[0][0]==plansza[2][2]))
    return plansza[0][0];
 
if ((plansza[2][0]!=' ')
&&(plansza[2][0]==plansza[1][1])
&&(plansza[2][0]==plansza[0][2]))
return plansza[2][0];
 
 
if (pelna(plansza)==1)
    return 1;
return 0;
 
} //sprawdz
 
int uzupelnij (char plansza[3][3], char c)
{
int i, j;
for (i=0;i<3;i++)
{
    for (j=0;j<3;j++)
    {
        if ((plansza[i][j]==c) && (plansza[i][(j+1)%3]==c)
            && (plansza[i][(j+2)]%3==' '))
            {
                plansza[i][(j+2)%3]='o';
                return 1;
            } // if
        if ((plansza[j][i]==c)&&(plansza[(j+1)%3][i]==c)
            &&(plansza[(j+2)%3][i]==' '))
            {
                plansza[(j+2)%3][i]='o';
                return 1;
            } //if
    }// for
        if ((plansza[i][2-i]==c)
        &&(plansza[(i+1)%3][2-(i+1)%3]==c)
        &&(plansza[(i+2)%3][2-(i+2)%3]==' ')){
        plansza[(i+2)%3][2-(i+2)%3]='o';
        return 1;
        }//if
        }//for
 
 
 
    return 0;
}
/* Najprostsza wersja tej funkcji to taka, która losuje pole na
którym komputer postawi kółko.
Do losowania uzyjemy funkcji rand.
Jezeli wylosujemy zajete pole, to ponowimy losowanie.
Aby komputer nie losował za kazdym razem tych samych
wartosci nalezy na poczatku funkcji main zainicjowac
generator liczb pseudolosowych poleceniem:
srand(time(NULL));
Do programu nalezy dołaczyc pliki nagłówkowe:
#include <stdlib.h>
#include <time.h>*/
 
/*Chcemy, zeby w sytuacji, gdy w jednej linii stoja dwa kółka,
komputer, o ile tylko sie da, dostawiał trzecie kółko.
Podobnie chcemy, zeby komputer blokował kółkami pary
krzyzyków znajdujacych sie w jednej linii.
Pierwszenstwo ma oczywiscie uzupełnianie par kółek.
Do uzupełniania par bedzie słuzyła funkcja uzupełnij,
która bedzie zwracała wartosc rózna od zera wtedy i tylko
wtedy, gdy uda sie jej uzupełnic jakas pare.
Funkcja uzupełnij bedzie miała dwa argumenty:
plansze,
znak, którego pary maja byc uzupełniane kółkami.*/
void ruch_komputera(char plansza[3][3])
{
unsigned int i, j, k;
if (uzupelnij(plansza,'o'))
return;
if (uzupelnij(plansza,'x'))
return;
 
/*
Okazuje sie, ze niezła strategia jest gdy komputer w pierwszej
kolejnosci próbuje ruszac sie w naroznikach.*/
 
    for (k=0;k<4;i++)
    {
        i = rand()%2;
        j=rand()%2;
        if (plansza[2*i][2*j]==' ')
        {
            plansza[2*i][2*j]='o';
            return;
        }
    }
 
    do
    {
        i=rand()%3;
        j=rand()%3;
    }
        while(plansza[i][j]!=' ');
            plansza[i][j]='o';
 do{
    i=rand()%3;
    j=rand()%3;
    } while (plansza[i][j]!=' ');
 
plansza[i][j]='o';
 
}
 
 
 
/*
 
Główna czesc programu bedzie stanowiła petla wykonujaca sie
tak długo jak długo bedzie toczyła sie gra.
Kolejne obroty petli beda odpowiadały kolejnym ruchom
graczy.
Gracze ruszaja sie na zmiane.
Dopóki gra jest nierozstrzygnieta zmienna wynik bedzie miała
wartosc 0.
Stan gry bedzie oceniac funkcja sprawdz.
Zmienna wynik bedzie miała wartosc:
0 – gdy gra jest niezakonczona,
1 – gdy gra zakonczyła sie remisem,
’x’ – gdy wygrały krzyzyki,
’o’ – gdy wygrały kółka
Dla uproszczenia przyjmujemy, ze człowiek zawsze gra
krzyzykami a komputer kółkami.
Funkcja wypisz bedzie wypisywac stan planszy
 */
int main(int argc, char *argv[])
{
int ruch = 1;
char wynik = 0;
char plansza [3][3];
printf("********************************************************************************\n");
printf("-============================== KOLKO I KRZYZYK ================================\n");
srand(time(NULL));
wyczysc(plansza);
    while (wynik==0)
    {
        if (ruch==0)
            ruch_gracza(plansza);
        else
            ruch_komputera(plansza);
        ruch=1-ruch;
        wynik=sprawdz(plansza);
    }
    wypisz(plansza);
    if (wynik==1)
        printf("Remis\n");
    else
        if (wynik=='x')
        {
            printf("Wygrales!!! :-) \n");
            printf("Nacisnij ENTER aby kontynowac\n");
            getchar();
            getchar();
        }
    else
    {
        printf("Przegrales :( \n");
        printf("Nacisnij ENTER aby kontynowac\n");
        getchar();
        getchar();
    }
 // for
 
return 0;
}
