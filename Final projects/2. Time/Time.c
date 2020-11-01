#include <stdio.h>
#include <stdlib.h>

#define ROZMIAR 10000

void zapamietaj(char pamiec[]) // opis w main
{
    int k = 0;
    pamiec[0] = getchar();
    while (pamiec[k] != EOF && pamiec[k] != '&') {
        k++;
        pamiec[k] = getchar();
        if ((pamiec[k - 1] == ' ' || pamiec[k - 1] == '\n' || pamiec[k - 1] == '|') &&
            (pamiec[k] == ' ' || pamiec[k] == '\n' ||
             pamiec[k] == '|')) // ten warunek zapewnia to ze nie ma dwoch znakow odzielenia obok siebie
            k--;
    }
    k = 0;
}

void uklada(int tab[]) // opis w main
{
    int k;
    for (k = 0; k < ROZMIAR; k++)
        tab[k] = (ROZMIAR / 2) - 1 - k;
}

int tlumacz(int x) // tlumaczy adresy z jezyka czas na adresy w moim programie
{
    x = x + ROZMIAR / 2;
    return x;
}

int adresik(char pamiec[], int *i) // zczytuje adres z programu w jezyku czas i oddaje jego wartosc w postaci inta
{
    int znak = 1;
    int adres1 = 0;
    if (pamiec[*i] == '-') {
        znak = -1;
        *i = *i + 1;
    } else if (pamiec[*i] == '+')
        *i = *i + 1;
    while (pamiec[*i] >= '0' && pamiec[*i] <= '9') {
        adres1 = adres1 * 10 + (pamiec[*i] - '0');
        *i = *i + 1;
    }
    adres1 = znak * adres1;
    return adres1;
}

void odejmowanie(int adres1, int adres2, int tab[]) // wykonuje funkcje odejmowania na 2 adresach
{
    tab[tlumacz(tab[tlumacz(adres1)])] = tab[tlumacz(tab[tlumacz(adres1)])] - tab[tlumacz(tab[tlumacz(adres2)])];
}

void pisz(int adres1, int tab[]) // wypisuje na wyjscie znak o kodzie ascii z tablicy o danym adresie
{
    putchar(tab[tlumacz(tab[tlumacz(adres1)])]);
}

void zapisz(char pamiec[], int *i,
            char etykieta[]) // zapisuje w tablicy etykieta[] nezwe etykiety do ktorej definicji bedzie skok, nazwa ta jest zakonczona znakiem NULL
{
    int k = 0;
    while (pamiec[*i] != ' ' && pamiec[*i] != '\n' && pamiec[*i] != '|' && pamiec[*i] != ';') {
        while (pamiec[*i] == ' ' || pamiec[*i] == '\n' || pamiec[*i] == '|')
            i++;
        etykieta[k] = pamiec[*i];
        *i = *i + 1;
        k++;
    }
    etykieta[k] = '\0';
}

void stosuj(char pamiec[], int *i, char etykieta[], int *l, int stos[],
            int tak) //jesli tak=1 wrzuca na stos adres pamieci po zakonczeniu etykiety, nastepnie niezaleznie od tak szuka definicji etykiety o nazwie zapisanej w tablicy etykieta[] i skacze(zmienia indeks pamieci) do niej
{
    if (tak == 1) // zapisuje na stosie odpowiedni indeks
    {
        stos[*l] = *i;
        *l = *l + 1;
    }
    int k = 0;
    int j;
    int test = 1;
    while (test == 1) {
        if (pamiec[k] ==
            ':')// szuka ':' w pamieci, nastepnie sprawdza czy to ta definicja etykiety o ktora chodzi, jesli nie, to znowu szuka : itd
        {
            j = 0;
            k++;
            while (pamiec[k] == ' ' || pamiec[k] == '\n' || pamiec[k] == '|')
                k++;
            while (pamiec[k] == etykieta[j] && etykieta[j] != '\0') {
                j++;
                k++;
            }
            if (etykieta[j] == '\0' && (pamiec[k] == ' ' || pamiec[k] == '\n' || pamiec[k] == '|' || pamiec[k] ==
                                                                                                     ';')) // jesli trafi na odpowiednia definicjie etykiety to zmienia test na 0 co przerywa petle
                test = 0;
            else
                k++;
        } else
            k++;
    }
    *i = k; // skok do miejsca za definicja etykiety
}

int funkcja(char pamiec[], int *i, int tab[], int stos[], int *l) {
    while (pamiec[*i] == ' ' || pamiec[*i] == '|' ||
           pamiec[*i] == '\n') // przeskakuje przez wszystkie znaki oddzielenia
        *i = *i + 1;
    if ((pamiec[*i] <= '9' && pamiec[*i] >= '0') || pamiec[*i] == '+' ||
        pamiec[*i] == '-') // jesli trafi na adres to jest kilka opcji
    {
        int adres1, adres2;
        adres1 = adresik(pamiec, i); // zapisuje pierwszy adres
        while (pamiec[*i] == ' ' || pamiec[*i] == '|' || pamiec[*i] == '\n') // przeskakuje zbedne znaki oddzielenia
            *i = *i + 1;
        if ((pamiec[*i] <= '9' && pamiec[*i] >= '0') || pamiec[*i] == '+' ||
            pamiec[*i] == '-') // jesli trafi na kolejny adres to wykona odejmowanie
        {
            adres2 = adresik(pamiec, i); // zapisuje drugi adres
            odejmowanie(adres1, adres2, tab); // **adres1=**adres1-**adres2
        } else if (pamiec[*i] == '^') // pisze znak o kodzie ascii **adres1
        {
            pisz(adres1, tab);
            *i = *i + 1;
        } else if (pamiec[*i] != EOF && pamiec[*i] != '&') // trafia na etykiete
        {
            if (tab[tlumacz(tab[tlumacz(adres1)])] > 0) // jesli **adres1>0 to skacze do definicji etykiety
            {
                char etykieta[2001];
                zapisz(pamiec, i, etykieta); // zapisuje etykiete
                stosuj(pamiec, i, etykieta, l, stos, 0); // szuka jej definicji nastepnie do niej skacze
            } else // **adres1<=0 wiec pomija etykiete i konczy
            {
                while (pamiec[*i] != ' ' && pamiec[*i] != '|' && pamiec[*i] != '\n' && pamiec[*i] != ';')
                    *i = *i + 1;
            }
        }
    } else if (pamiec[*i] ==
               ';') //jesli na stosie nic nie ma(czyli l==0) to konczy program, w innym przypadku zdejmuje adres ze stosu i skacze do niego (stos jest zpaelniany w funkcji stosuj)
    {
        if (*l == 0)
            return 0;
        else {
            *l = *l - 1;
            *i = stos[*l];
            stos[*l] = 0;
        }
    } else if (pamiec[*i] == ':') // trafia na definicje, pomija ja
    {
        while (pamiec[*i] != ' ' && pamiec[*i] != '|' && pamiec[*i] != '\n')
            *i = *i + 1;
    } else if (pamiec[*i] ==
               '^') // zapisuje w komorce **adres kod znaku ascii wziety z getchara lub -1 jesli getchar to EOF
    {
        *i = *i + 1;
        if (pamiec[*i] == ' ' || pamiec[*i] == '|' || pamiec[*i] == '\n') // idzie az do adresu
            *i = *i + 1;
        int adres;
        adres = adresik(pamiec, i); // zapisuje adres
        int z;
        z = getchar(); // zbiera chara z pamieci
        if (z == EOF)
            tab[tlumacz(tab[tlumacz(adres)])] = -1;
        else
            tab[tlumacz(tab[tlumacz(adres)])] = z;
    } else if (pamiec[*i] != EOF && pamiec[*i] != '&') // trafia na etykiete
    {
        char etykieta[2001];
        zapisz(pamiec, i, etykieta); // zapisuje etykiete
        stosuj(pamiec, i, etykieta, l, stos,
               1); // zapisuje miejsce po etykiecie na stosie, szuka definicji etykiety, skacze do niej
    }

    if (pamiec[*i] == EOF || pamiec[*i] == '&') // jesli trafi na EOF lub & to konczy program
        return 0;
    else return 1;
}

int main() {
    int i = 0; // licznik pamieci
    int test = 1; // sprawdza czy program sie skonczyl
    int l = 0; // licznik sotsu
    char pamiec[100000]; // zapamietane tu sa dane
    int tab[ROZMIAR]; // pamiec maszyny czas
    int stos[4000]; // stos powrotu
    zapamietaj(
            pamiec); //zczytuje program az do '&' lub EOF, przy czym nie pobiera wiecej niz 2 znaki oddzielajace obok siebie
    uklada(tab); // ustawia pamiec masazyny czas na wlasciwa( z przesunieciem o 5k w prawo, co jest pozniej uwzgledniane
    while (test == 1) // tutaj wykonywany jest porgram
    {
        test = funkcja(pamiec, &i, tab, stos,
                       &l); // funkcja przyjmuje wartosc 0 jesli program dobiegl konca w innym przypadku przyjmuje wartosc 1
    }
    return 0;
}
