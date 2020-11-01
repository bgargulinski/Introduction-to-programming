#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define ROZMIAR 8
void poczatek(int plansza[][ROZMIAR]) // robi ustawienie poczatkowe
{
    int i,j;
    for(i=0;i<ROZMIAR;i++) //wypalnia tablice '-'
        for(j=0;j<ROZMIAR;j++)
            plansza[i][j]='-';
    plansza[(ROZMIAR-1)/2][(ROZMIAR-1)/2]='B'; // ustawia srodkowe pionki we wlasciwych miejscach
    plansza[ROZMIAR/2][ROZMIAR/2]='B';
    plansza[(ROZMIAR-1)/2][ROZMIAR/2]='C';
    plansza[ROZMIAR/2][(ROZMIAR-1)/2]='C';
}
void rysuj(int plansza[][ROZMIAR]) //rysuje plansze
{
    int i,j;
    for(i=0;i<ROZMIAR;i++)
    {
        for(j=0;j<ROZMIAR;j++)
        {
            putchar(plansza[j][i]);
            if(j==ROZMIAR-1)printf("%d",i+1);//dodaje numery wierszy
        }
        if(i==ROZMIAR-1)printf("\nabcdefgh"); // dodaje literry kolumn pod plansza
        printf("\n");
    }
}

int badanie(int plansza[][ROZMIAR], int x, int y, int a, int b,int tak,int czyj) //zlicza ile pionkow zmieni kolor w danym ruchu po linii lub przekatnej w okreslonym kierunku,czyj okreola czyj jest ruch oraz jesli int tak=1 zamienia te pionki
{   
    int wartosc,wspx,wspy,stop,licznik;
	stop=1; // potrzebne do zatrzymania petli w przypadku natrafienia na puste pole lub z wlasnym pionem
	wspx=x;// zmienne x i y beda mi potrzebne na koncu petli, wiec wprowadzam zmienne pomocnicze na ktorych bedee operowal
	wspy=y;
	licznik=0; //zlicza ile pionow sie obroci w razie ruchu hipotetycznego lub nie w zaleznosci od tego czy tak=1 czy 0
    if(plansza[x][y]=='-') // w przypadku gdy ten warunek nie jest spelniony to na danym polu stoi juz pion czyli nie mozna tam juz stawiac
    {
        if (czyj=='C')
            wartosc='B'; //wartosc oznacza kolor piona przeciwnika
        else
            wartosc='C';
        while((wspx+a>-1&& wspx+a<ROZMIAR && wspy+b<ROZMIAR && wspy+b>-1) && stop==1) // a i b to wspolczynniki kierunkowe- w zaleznosci od nich petla bedzie wykonana po linii lub przekatnej w danym kierunku
        {
			wspx += a;
			wspy += b;

			if(plansza[wspx][wspy]!=wartosc) // do tego wlasnie byl mi potrzebny stop
            {
                stop=0;
            }
        }
        if (plansza[wspx][wspy]==czyj) // sprawdza czy poprzednia petla zatrzymala sie gdyz natrafila na swojego piona, jesli tak to zlicza (i w zaleznosci od int tak zmienia lub nie) pionki ktore zmienilyby kolor
            while(wspx!=x || wspy!=y)
            {

				wspx -= a; // poniewaz wspolczynniki te zatrzymaly sie w ostatniej petli polozeniu koncowym to teraz beda wracac az do punktu rozpoczecia funkcji zliczajac i ewentualnie zmieniajac po drodze pionki przeciwnika
				wspy -= b;
				if(plansza[wspx][wspy]==wartosc)
                {
                    if(tak==1)
                        plansza[wspx][wspy]=czyj; // tak=1 aktywuje zmiane pionkow tak=0 oznacza tylko zliczenie ich bez ingerencji w plansze
                    licznik++;
                }
            }
    }
    return licznik; // funkcja zwraca liczbe zmienionych(lub nie w zaleznosci od int tak) pionkow
}
int zmiany(int plansza[][ROZMIAR], int x, int y, int tak,int czyj)//wykonuje funkcje badanie po wszystkich liniach i kierunkach, zlicza ile pionkow zamieni dany ruch oraz jesli int tak=1 wykonuje ten ruch
{
	int licznik=0;
	licznik+=badanie(plansza,x,y,1,1,tak,czyj);
	licznik+=badanie(plansza,x,y,-1,-1,tak,czyj);
	licznik+=badanie(plansza,x,y,1,0,tak,czyj);
	licznik+=badanie(plansza,x,y,0,1,tak,czyj);
	licznik+=badanie(plansza,x,y,-1,0,tak,czyj);
	licznik+=badanie(plansza,x,y,0,-1,tak,czyj);
	licznik+=badanie(plansza,x,y,1,-1,tak,czyj);
	licznik+=badanie(plansza,x,y,-1,1,tak,czyj);
	return licznik; // zwraca ile pionkow sie zmieni na wszystkich kierunkach po danym ruchu x,y
}
int przewaga(int plansza[][ROZMIAR]) // funkcja ta ocenia przewage czarnych nad bialymi
{
    int i,j,roznica;
    roznica=0;
    for(i=0;i<ROZMIAR;i++)
        for(j=0;j<ROZMIAR;j++)
        {
            if(plansza[i][j]=='C')roznica++;
            else if(plansza[i][j]=='B')roznica--;
        }
    return roznica; // zwraca wartosc tej przewagi z punktu widzenia czarnych
}
int ruchgr(int plansza[][ROZMIAR]) //zczytuje ruch gracza, sprawdza czy jest legalny, wykonuje go
{
    int x,y,z,koniec,test;
    test=0; // sprawdza czy ruch jest poprawny- jesli test =0 po wykonaniu petli to funkcja drukuje stan planszy z funkcji rysuj, pisze przewage czarnych i wykonuje sie jeszcze raz
    while(test==0)
    {
        z=getchar();
        if(z!='='&&z!='\n'&&z!=EOF)y=getchar(); // sprawdza czy pierwszy znak byl koncem linii lub pliku lub = jesli nie to zbiera kolejne
            if(y!='\n'&&y!=EOF&&z!='\n'&&z!=EOF) //jw
            {
                koniec=getchar();
                while(koniec!='\n'&& koniec!=EOF) // ta petla zabezpiecza program przed dluzszymi slowami
                koniec=getchar();
            }
	x=z-'a'; // zamienia litere a-h na liczbe odpowiadajacej kolumnie tablicy planszy
	y=y-'1'; // podobnie, tylko z liczba
    if(z==EOF||y==EOF||koniec==EOF)
        return 0; // jesli mamy do czynienia z koncem pliku to funkcja zwraca 0- jest to wykorzystane w mainie do zakonczenia programu
    else if(z!='=') // sprawdza czy x,y sa ok, jesli tak to sprawdza czy ruch jest legalny jesli tak, to drukuje wspolrzedne ruchu, lub = jesli pas, jesli ruch jest zly to test=0 i petla sie powtarza
    {

        if(z<='h'&&z>='a'&&(y<=ROZMIAR)&&(y>-1))
        {
            if(zmiany(plansza,x,y,1,'C')>0)
            {
                plansza[x][y]='C';
                putchar(z);
                putchar(y+'1');
                test=1;
            }
            else test=0;
        }
        else test=0;
    }
    else
    {
        printf("=");
        test=1;
    }
    if(test==0)// jesli test=0 to pisze ? , liczy przewage i rysuje plansze
    {
        printf("? %d\n",przewaga(plansza));
        rysuj(plansza);
    }
    }
    return 1; // jesli nie ma EOF to funkcja zwroci 1- wykorzystuje to w mainie
}
void ruchkom(int plansza[][ROZMIAR]) // ruch bialych
{
    int i,j,ri,rj,rekord,zmian;
    rekord=0; // tutaj przechowywana bedzie liczba zmienionych pionow w przypadku najlepszego mozliwego ruchu w pozycji
    ri=-1; // zmienne pomocnicze do zapamietania wspolrzednych rekordu
    rj=-1;
    for(j=0;j<ROZMIAR;j++)// petla oceniajaca jaki ruch jest najlepszy w pozycji
        for(i=0;i<ROZMIAR;i++)
        {
            zmian=zmiany(plansza,i,j,0,'B');
            if(rekord<zmian)
            {
                rekord=zmian;
                ri=i;
                rj=j;
            }
        }
    if(ri!=-1) // wykonuje najlepszy mozliwy ruch w pozycji jesli taki istnieje, wypisuje go
    {
        zmiany(plansza,ri,rj,1,'B');
        plansza[ri][rj]='B';
        printf(" ");
        putchar(ri+'a');
        putchar(rj+'1');
    }
    else
        printf(" ="); // oznacza to ze nie bylo legalnego ruchu dla bialych wiec pasuja one i pisza =
    printf(" %d\n", przewaga(plansza)); // pisze przewage z punktu widzenia czarnych
}

int main()
{
    int plansza[ROZMIAR][ROZMIAR]; // tu bedzie plansza
    poczatek(plansza); // ustawia plansze na poczatkowe ustawienie
    rysuj(plansza); // rysuje plansze
    int test=1;
        while(test!=0) // jesli gracz w swoim ruchu wpisze EOF to funkcja ruchu gracza zwroci 0 i gra sie zakonczy, w innym przypadku gra bedzie toczyla sie dalej
        {
            test=ruchgr(plansza);
            if(test!=0)
            {
                ruchkom(plansza);
                rysuj(plansza);
            }
        }
    return 0;
}

