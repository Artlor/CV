#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>

using namespace std;

int x;
int y;

bool czy_pokazywac_pierwszego = true;
bool czy_pokazywac_drugiego = true;

const int bok_pierwszy = 8;
const int bok_drugi = 16;   
							
static int poprzedni_ruch;
static int czy_mozna_strzelic = true;

static int stary_ostateczny;
static int stary_ostateczny1; 

void wstawienie_potworka1(char mapa[bok_pierwszy][bok_drugi], int granica_losowania);
void wstawienie_potworka(char mapa[bok_pierwszy][bok_drugi], int granica_losowania);
int obliczanie_pola_do_manewru();

void tworzenie_mapy(char mapa[bok_pierwszy][bok_drugi])
{
	for (int i = 0; i<bok_pierwszy; i++)
	{
		if (i>0 && i < (bok_pierwszy - 1))		
		{
			for (i; i<(bok_pierwszy - 1); i++)
			{
				for (int j = 1; j<bok_drugi - 1; j++)
				{
					mapa[i][j] = ' ';	 		
				}
				mapa[i][0] = '#';
				mapa[i][bok_drugi - 2] = '#';		
			}
		}
		if (i == 0 || i == (bok_pierwszy - 1))				
			for (int j = 0; j<bok_drugi; j++)
			{
				mapa[i][j] = '#';				
			}
	}
	for (int a = 0; a < bok_pierwszy; a++)
		mapa[a][bok_drugi - 1] = '\n';
}

void wyswietlanie_mapy_koncowej(char mapa[bok_pierwszy][bok_drugi], HANDLE zmienna, const int opoznienie)
{
	int x = (poprzedni_ruch + bok_drugi + 1) / bok_drugi;
	int y = (poprzedni_ruch + bok_drugi + 1) - (x*bok_drugi);
	Sleep(opoznienie);
	system("cls");
	cout << "> - PLAYER\nM - MONSTER\n\nL SHIFT + STRZALKA - TWORZENIE SCIANY\nL CTRL + STRZALKA - OBRACANIE SIE\nSPACJA - STRZAL\n\n";
	for (int a = 0; a < bok_pierwszy; a++)
	{
		for (int b = 0; b < bok_drugi; b++)
		{
			if (a == x && b == y)
			{
				SetConsoleTextAttribute(zmienna, FOREGROUND_GREEN);
				cout << mapa[a][b];
				SetConsoleTextAttribute(zmienna, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
				continue;
			}
			cout << mapa[a][b];
		}
	}
	cout << "\n\nDorwal Cie Monster! Przegrales! Sproboj jeszcze raz. (nacisnij przycisk by zakonczyc program)";
	getchar();
}

void wyswietlanie_mapy(const char mapa[bok_pierwszy][bok_drugi], const int opoznienie)
{
	Sleep(opoznienie);
	system("cls");
	cout << "> - PLAYER\nM - MONSTER\n\nL SHIFT + STRZALKA - TWORZENIE SCIANY\nL CTRL + STRZALKA - OBRACANIE SIE\nSPACJA - STRZAL\n\n";
	for (int a = 0; a<bok_pierwszy; a++)
	{
		for (int b = 0; b<bok_drugi; b++)
		{
			cout << mapa[a][b];
		}
	}
}

void smierc_potworka(char mapa[bok_pierwszy][bok_drugi], HANDLE zmienna, const int opoznienie, int ktory_potwor)
{
	x = (ktory_potwor + bok_drugi + 1) / bok_drugi;
	y = (ktory_potwor + bok_drugi + 1) - (x*bok_drugi); 
	Sleep(opoznienie);
	system("cls");
	cout << "> - PLAYER\nM - MONSTER\n\nL SHIFT + STRZALKA - TWORZENIE SCIANY\nL CTRL + STRZALKA - OBRACANIE SIE\nSPACJA - STRZAL\n\n";
	for (int a = 0; a < bok_pierwszy; a++) 
	{
		for (int b = 0; b < bok_drugi; b++)
		{
			if (a == x && b == y)
			{
				SetConsoleTextAttribute(zmienna, FOREGROUND_RED);
				cout << mapa[a][b];
				SetConsoleTextAttribute(zmienna, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
				continue;
			}
			cout << mapa[a][b];
		}
	}
	cout << "\n\nZabiles potworka! Gratulacje! 2 SEKUNDY PRZERWY NA ZLAPANIE ODDECHU!";
	mapa[x][y] = ' ';
	Sleep(2000);
}

void wyswietlanie_wygranej(char mapa[bok_pierwszy][bok_drugi], HANDLE zmienna, const int opoznienie)
{
	x = (poprzedni_ruch + bok_drugi + 1) / bok_drugi;
	y = (poprzedni_ruch + bok_drugi + 1) - (x*bok_drugi);
	Sleep(opoznienie);
	system("cls");
	cout << "> - PLAYER\nM - MONSTER\n\nL SHIFT + STRZALKA - TWORZENIE SCIANY\nL CTRL + STRZALKA - OBRACANIE SIE\nSPACJA - STRZAL\n\n";
	for (int a = 0; a < bok_pierwszy; a++)
	{
		for (int b = 0; b < bok_drugi; b++)
		{
			if (a == x && b == y)
			{
				SetConsoleTextAttribute(zmienna, FOREGROUND_GREEN);
				cout << mapa[a][b];
				SetConsoleTextAttribute(zmienna, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
				continue;
			}
			cout << mapa[a][b];
		}
	}
	cout << "\n\nWYGRALES GRE! GRATULACJE!";
	getchar();
}

void wstawienie_gracza(char mapa[bok_pierwszy][bok_drugi])
{
	char *wsk = &mapa[0][0];
	int static terazniejszy_ruch;
	static bool omin_pierwszy_raz = false;
	static char znak = '>';

	if (omin_pierwszy_raz)
		znak = *(wsk + (bok_drugi + 1) + poprzedni_ruch);

	if (omin_pierwszy_raz)
		*(wsk + (bok_drugi + 1) + poprzedni_ruch) = ' ';

	omin_pierwszy_raz = true;

	if (GetKeyState(VK_LEFT) < 0)
	{
		if (GetKeyState(VK_LSHIFT) < 0)
			*((wsk + (bok_drugi + 1)) + terazniejszy_ruch) = 'X';

		if (*((wsk + (bok_drugi + 1)) + terazniejszy_ruch - 1) == ' ' || *((wsk + (bok_drugi + 1)) + terazniejszy_ruch - 1) == 'X')
		{
			if (GetKeyState(VK_LCONTROL) < 0)
			{
				*((wsk + (bok_drugi + 1)) + terazniejszy_ruch) = '<';
			}
			else
				terazniejszy_ruch--;
			poprzedni_ruch = terazniejszy_ruch;
			*((wsk + (bok_drugi + 1)) + terazniejszy_ruch) = '<';
		}
		else
		{
			*(wsk + (bok_drugi + 1) + terazniejszy_ruch) = '<';
		}
	}
	else if (GetKeyState(VK_RIGHT) < 0)
	{
		if (GetKeyState(VK_LSHIFT) < 0)
			*((wsk + (bok_drugi + 1)) + terazniejszy_ruch) = 'X';

		if (*((wsk + (bok_drugi + 1)) + terazniejszy_ruch + 1) == ' ' || *((wsk + (bok_drugi + 1)) + terazniejszy_ruch + 1) == 'X')
		{
			if (GetKeyState(VK_LCONTROL) < 0)
			{
				*((wsk + (bok_drugi + 1)) + terazniejszy_ruch) = '>';
			}
			else
				terazniejszy_ruch++;
			poprzedni_ruch = terazniejszy_ruch;
			*((wsk + (bok_drugi + 1)) + terazniejszy_ruch) = '>';
		}
		else
		{
			*(wsk + (bok_drugi + 1) + terazniejszy_ruch) = '>';
		}
	}
	else if (GetKeyState(VK_UP) < 0)
	{
		if (GetKeyState(VK_LSHIFT) < 0)
			*((wsk + (bok_drugi + 1)) + terazniejszy_ruch) = 'X'; 

		if (*((wsk + (bok_drugi + 1)) + (terazniejszy_ruch - bok_drugi)) == ' ' || *((wsk + (bok_drugi + 1)) + terazniejszy_ruch - bok_drugi) == 'X')
		{
			if (GetKeyState(VK_LCONTROL) < 0)
			{
				*((wsk + (bok_drugi + 1)) + terazniejszy_ruch) = '^';
			}
			else
				terazniejszy_ruch -= bok_drugi;
			poprzedni_ruch = terazniejszy_ruch;
			*((wsk + (bok_drugi + 1)) + terazniejszy_ruch) = '^';
		}
		else
		{
			*(wsk + (bok_drugi + 1) + terazniejszy_ruch) = '^';
		}
	}
	else if (GetKeyState(VK_DOWN) < 0)
	{
		if (GetKeyState(VK_LSHIFT) < 0)
			*((wsk + (bok_drugi + 1)) + terazniejszy_ruch) = 'X'; 

		if (*((wsk + (bok_drugi + 1)) + (terazniejszy_ruch + bok_drugi)) == ' ' || *((wsk + (bok_drugi + 1)) + terazniejszy_ruch + bok_drugi) == 'X')
		{
			if (GetKeyState(VK_LCONTROL) < 0)
			{
				*((wsk + (bok_drugi + 1)) + terazniejszy_ruch) = 'v';
			}
			else
				terazniejszy_ruch += bok_drugi;
			poprzedni_ruch = terazniejszy_ruch;
			*((wsk + (bok_drugi + 1)) + terazniejszy_ruch) = 'v';
		}
		else
		{
			*(wsk + (bok_drugi + 1) + terazniejszy_ruch) = 'v';
		}
	}
	else
		*(wsk + (bok_drugi + 1) + poprzedni_ruch) = znak;

	if (czy_mozna_strzelic)
	{
		if (GetKeyState(VK_SPACE) < 0)
		{
			czy_mozna_strzelic = false;
		}
	}
}

int oddaj_strzal(char mapa[bok_pierwszy][bok_drugi], int poprzedni_ruch, int stary_ostateczny, int stary_ostateczny1)
{
	char *wsk = &mapa[0][0];
	static int ruch_kulki;
	static int i = 1;
	static int poprzedni_ruch_kulki;
	static bool omin_pierwszy_raz = false; 
	static bool sprawdz_tylko_raz = true; 
	static bool ustaw_ruch_kulki = true; 

	static bool w_lewo = false; 
	static bool w_prawo = false;
	static bool w_gore = false; 
	static bool w_dol = false; 

	static bool usun_kulke_prawa = false;
	static bool usun_kulke_lewa = false;
	static bool usun_kulke_gorna = false;
	static bool usun_kulke_dolna = false;

	static bool poprzednie_i;

	if (usun_kulke_prawa)
	{
		if (*((wsk + (bok_drugi + 1)) + (ruch_kulki + i)) == 'o')
			*((wsk + (bok_drugi + 1)) + (ruch_kulki + i)) = ' ';

		usun_kulke_prawa = false;
	}

	if (ustaw_ruch_kulki)
	{
		ruch_kulki = poprzedni_ruch;
		ustaw_ruch_kulki = false;
	}

	if (sprawdz_tylko_raz)
	{
		if (*((wsk + (bok_drugi + 1)) + ruch_kulki) == '>')
			w_prawo = true;
		else if
			(*((wsk + (bok_drugi + 1)) + ruch_kulki) == '<')
			w_lewo = true;
		else if
			(*((wsk + (bok_drugi + 1)) + ruch_kulki) == '^')
			w_gore = true;
		else if
			(*((wsk + (bok_drugi + 1)) + ruch_kulki) == 'v')
			w_dol = true;
	}
	sprawdz_tylko_raz = false;

	if (w_prawo)																															
	{
		if (*((wsk + (bok_drugi + 1)) + ruch_kulki + i) == '#' || *((wsk + (bok_drugi + 1)) + ruch_kulki + i) == 'X') 
		{
			if (*((wsk + (bok_drugi + 1)) + (ruch_kulki + i) - 1) == 'o')
				*((wsk + (bok_drugi + 1)) + (ruch_kulki + i) - 1) = ' ';
			omin_pierwszy_raz = false;
			czy_mozna_strzelic = true;
			ustaw_ruch_kulki = true;
			sprawdz_tylko_raz = true;
			w_prawo = false;
			i = 1;
			return -999;
		}
		else if ((*((wsk + (bok_drugi + 1)) + (ruch_kulki + i - 1)) == 'o' || *((wsk + (bok_drugi + 1)) + (ruch_kulki + i - 1)) == '>') && (i + ruch_kulki) == stary_ostateczny  && czy_pokazywac_pierwszego) 
		{
			if (*((wsk + (bok_drugi + 1)) + (ruch_kulki + i - 1)) != '>')
			{
				*((wsk + (bok_drugi + 1)) + (ruch_kulki + i - 1)) = ' ';
				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny;
			}
			else
			{
				usun_kulke_prawa = true;
				poprzednie_i = i;
				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny;
			}
		}
		else if ((*((wsk + (bok_drugi + 1)) + (ruch_kulki + i - 1)) == 'o' || *((wsk + (bok_drugi + 1)) + (ruch_kulki + i - 1)) == '>') && (i + ruch_kulki) == stary_ostateczny1 && czy_pokazywac_drugiego)
		{
			if (*((wsk + (bok_drugi + 1)) + (ruch_kulki + i - 1)) != '>')
			{
				*((wsk + (bok_drugi + 1)) + (ruch_kulki + i - 1)) = ' ';
				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny1;
			}
			else
			{
				usun_kulke_prawa = true;
				poprzednie_i = i;
				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny1;
			}
		}
		else if (*((wsk + (bok_drugi + 1)) + ruch_kulki + i) == ' ') 
		{
			poprzedni_ruch_kulki = ruch_kulki + i - 1;
			*((wsk + (bok_drugi + 1)) + ruch_kulki + i) = 'o';
		}
		i++;
	}
	else if (w_lewo)																														
	{
		if (*((wsk + (bok_drugi + 1)) + ruch_kulki - i) == '#' || *((wsk + (bok_drugi + 1)) + ruch_kulki - i) == 'X') 
		{
			if (*((wsk + (bok_drugi + 1)) + (ruch_kulki - i) + 1) == 'o')
				*((wsk + (bok_drugi + 1)) + (ruch_kulki - i) + 1) = ' ';
			omin_pierwszy_raz = false;
			czy_mozna_strzelic = true;
			ustaw_ruch_kulki = true;
			sprawdz_tylko_raz = true;
			w_lewo = false;
			i = 1;
			return -999;
		}
		else if ((*((wsk + (bok_drugi + 1)) + (ruch_kulki - i + 1)) == 'o' || *((wsk + (bok_drugi + 1)) + (ruch_kulki - i + 1)) == '>') && (ruch_kulki - i) == stary_ostateczny && czy_pokazywac_pierwszego) 
		{
			if (*((wsk + (bok_drugi + 1)) + (ruch_kulki - i + 1)) != '<')
			{
				*((wsk + (bok_drugi + 1)) + (ruch_kulki - i + 1)) = ' ';
				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny;
			}
			else
			{
				usun_kulke_prawa = true;
				poprzednie_i = i;
				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny;
			}
		}
		else if ((*((wsk + (bok_drugi + 1)) + (ruch_kulki - i + 1)) == 'o' || *((wsk + (bok_drugi + 1)) + (ruch_kulki - i + 1)) == '>') && (ruch_kulki - i) == stary_ostateczny1 && czy_pokazywac_drugiego) 
		{
			if (*((wsk + (bok_drugi + 1)) + (ruch_kulki - i + 1)) != '<')
			{
				*((wsk + (bok_drugi + 1)) + (ruch_kulki - i + 1)) = ' ';
				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny1;
			}
			else
			{
				usun_kulke_prawa = true;
				poprzednie_i = i;
				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny1;
			}
		}
		else if (*((wsk + (bok_drugi + 1)) + ruch_kulki - i) == ' ')
		{
			poprzedni_ruch_kulki = ruch_kulki - i + 1;
			*((wsk + (bok_drugi + 1)) + ruch_kulki - i) = 'o';
		}
		i++;
	}
	else if (w_gore)																																	
	{
		if (*((wsk + (bok_drugi + 1)) + ruch_kulki - (i*bok_drugi)) == '#' || *((wsk + (bok_drugi + 1)) + ruch_kulki - (i*bok_drugi)) == 'X')
		{
			if (*((wsk + (bok_drugi + 1)) + (ruch_kulki - (i*bok_drugi)) + bok_drugi) == 'o')
				*((wsk + (bok_drugi + 1)) + (ruch_kulki - (i*bok_drugi)) + bok_drugi) = ' ';
			omin_pierwszy_raz = false;
			czy_mozna_strzelic = true;
			ustaw_ruch_kulki = true;
			sprawdz_tylko_raz = true;
			w_gore = false;
			i = 1;
			return -999;
		}
		else if ((*((wsk + (bok_drugi + 1)) + (ruch_kulki - (i*bok_drugi) + bok_drugi)) == 'o' || *((wsk + (bok_drugi + 1)) + (ruch_kulki - (i*bok_drugi) + bok_drugi)) == '>') && (ruch_kulki - (i*bok_drugi)) == stary_ostateczny && czy_pokazywac_pierwszego)
		{
			if ((*((wsk + (bok_drugi + 1)) + (ruch_kulki - (i*bok_drugi) + bok_drugi)) != '^'))
			{
				*((wsk + (bok_drugi + 1)) + (ruch_kulki - (i*bok_drugi) + bok_drugi)) = ' ';
				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny;
			}
			else
			{
				usun_kulke_prawa = true;
				poprzednie_i = i;
				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny;
			}
		}
		else if ((*((wsk + (bok_drugi + 1)) + (ruch_kulki - (i*bok_drugi) + bok_drugi)) == 'o' || *((wsk + (bok_drugi + 1)) + (ruch_kulki - (i*bok_drugi) + bok_drugi)) == '>') && (ruch_kulki - (i*bok_drugi)) == stary_ostateczny1 && czy_pokazywac_drugiego) 
		{
			if ((*((wsk + (bok_drugi + 1)) + (ruch_kulki - (i*bok_drugi) + bok_drugi)) != '^'))
			{
				*((wsk + (bok_drugi + 1)) + (ruch_kulki - (i*bok_drugi) + bok_drugi)) = ' ';
				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny1;
			}
			else
			{
				usun_kulke_prawa = true;
				poprzednie_i = i;
				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny1;
			}
		}
		else if (*((wsk + (bok_drugi + 1)) + ruch_kulki - (i*bok_drugi)) == ' ')
		{
			poprzedni_ruch_kulki = ruch_kulki - (i*bok_drugi) + bok_drugi;
			*((wsk + (bok_drugi + 1)) + ruch_kulki - (i*bok_drugi)) = 'o';
		}
		i++;
	}
	else if (w_dol)																																		
	{
		if (*((wsk + (bok_drugi + 1)) + ruch_kulki + (i*bok_drugi)) == '#' || *((wsk + (bok_drugi + 1)) + ruch_kulki + (i*bok_drugi)) == 'X') 
		{
			if (*((wsk + (bok_drugi + 1)) + (ruch_kulki + (i*bok_drugi)) - bok_drugi) != 'v')
				*((wsk + (bok_drugi + 1)) + (ruch_kulki + (i*bok_drugi)) - bok_drugi) = ' ';
			omin_pierwszy_raz = false;
			czy_mozna_strzelic = true;
			ustaw_ruch_kulki = true;
			sprawdz_tylko_raz = true;
			w_dol = false;
			i = 1;
			return -999;
		}
		else if ((*((wsk + (bok_drugi + 1)) + (ruch_kulki + (i*bok_drugi) - bok_drugi)) == 'o' || *((wsk + (bok_drugi + 1)) + (ruch_kulki + (i*bok_drugi) - bok_drugi)) == '>') && (ruch_kulki + (i*bok_drugi)) == stary_ostateczny && czy_pokazywac_pierwszego)
		{
			if ((*((wsk + (bok_drugi + 1)) + (ruch_kulki + (i*bok_drugi) - bok_drugi)) != '^'))
			{
				*((wsk + (bok_drugi + 1)) + (ruch_kulki + (i*bok_drugi) - bok_drugi)) = ' ';

				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny;
			}
			else
			{
				usun_kulke_prawa = true;
				poprzednie_i = i;

				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny;
			}
		}
		else if ((*((wsk + (bok_drugi + 1)) + (ruch_kulki + (i*bok_drugi) - bok_drugi)) == 'o' || *((wsk + (bok_drugi + 1)) + (ruch_kulki + (i*bok_drugi) - bok_drugi)) == '>') && (ruch_kulki + (i*bok_drugi)) == stary_ostateczny1 && czy_pokazywac_drugiego) 
		{
			if ((*((wsk + (bok_drugi + 1)) + (ruch_kulki + (i*bok_drugi) - bok_drugi)) != '^'))
			{
				*((wsk + (bok_drugi + 1)) + (ruch_kulki + (i*bok_drugi) - bok_drugi)) = ' ';

				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny1;
			}
			else
			{
				usun_kulke_prawa = true;
				poprzednie_i = i;

				i = 1;
				omin_pierwszy_raz = false;
				czy_mozna_strzelic = true;
				ustaw_ruch_kulki = true;
				sprawdz_tylko_raz = true;
				w_prawo = false;
				return stary_ostateczny1;
			}
		}
		else if (*((wsk + (bok_drugi + 1)) + ruch_kulki + (i*bok_drugi)) == ' ')
		{
			poprzedni_ruch_kulki = ruch_kulki + (i*bok_drugi) - bok_drugi;
			*((wsk + (bok_drugi + 1)) + ruch_kulki + (i*bok_drugi)) = 'o';
		}
		i++;
	}

	if (omin_pierwszy_raz)
	{
		*((wsk + (bok_drugi + 1)) + poprzedni_ruch_kulki) = ' ';
	}
	omin_pierwszy_raz = true;
	return -998;

}

bool sprawdzenie_trafienia_gracza(char mapa[bok_pierwszy][bok_drugi], const int poprzedni_ruch_gracza, const int poprzedni_ruch_potworka)
{
	char *wsk = &mapa[0][0];
	if (poprzedni_ruch_gracza == poprzedni_ruch_potworka)
	{
		*(wsk + (bok_drugi + 1) + poprzedni_ruch_potworka) = 'M';
		return true;
	}
	else
		return false;
}

int main()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));

	char mapa[bok_pierwszy][bok_drugi];
	tworzenie_mapy(mapa);

	const int granica_losowania = obliczanie_pola_do_manewru();
	int licznik = 1;
	bool czy_zakonczyc = false;
	int smierc_potwora = -997;
	char *wsk = &mapa[0][0];

	if (true)
	{
		do
		{
			wstawienie_potworka(mapa, granica_losowania);
			wstawienie_potworka1(mapa, granica_losowania);
		} while (stary_ostateczny == stary_ostateczny1 || stary_ostateczny == 0 || stary_ostateczny1 == 0);

		wstawienie_gracza(mapa);

		if (czy_zakonczyc = sprawdzenie_trafienia_gracza(mapa, poprzedni_ruch, stary_ostateczny))
		{
			wyswietlanie_mapy_koncowej(mapa, hOut, 70);
			exit(0);
		}

		if (czy_zakonczyc = sprawdzenie_trafienia_gracza(mapa, poprzedni_ruch, stary_ostateczny1))
		{
			wyswietlanie_mapy_koncowej(mapa, hOut, 70);
			exit(0);
		}

		wyswietlanie_mapy(mapa, 70);
	}

	while (true)
	{
		if (licznik >6)
			licznik = 1;

		switch (licznik)
		{
			case 1:
				if (czy_pokazywac_pierwszego)
				{
					wstawienie_potworka(mapa, granica_losowania);
					if (czy_zakonczyc = sprawdzenie_trafienia_gracza(mapa, poprzedni_ruch, stary_ostateczny))
					{
						break;
					}
				}
				if (czy_pokazywac_drugiego)
				{
					wstawienie_potworka1(mapa, granica_losowania);
					if (czy_zakonczyc = sprawdzenie_trafienia_gracza(mapa, poprzedni_ruch, stary_ostateczny1))
					{
						break;
					}
				}
				if (!czy_mozna_strzelic)
				{
					smierc_potwora = oddaj_strzal(mapa, poprzedni_ruch, stary_ostateczny, stary_ostateczny1); 
				}
				break;

			case 2:if (!czy_mozna_strzelic)
			{
				smierc_potwora = oddaj_strzal(mapa, poprzedni_ruch, stary_ostateczny, stary_ostateczny1); 
			}
				   break;

			case 3:
				wstawienie_gracza(mapa);
				if (czy_pokazywac_pierwszego)
				{
					wstawienie_potworka(mapa, granica_losowania);

					if (czy_zakonczyc = sprawdzenie_trafienia_gracza(mapa, poprzedni_ruch, stary_ostateczny))
					{
						break;
					}
				}
				if (czy_pokazywac_drugiego)
				{

					wstawienie_potworka1(mapa, granica_losowania);
					if (czy_zakonczyc = sprawdzenie_trafienia_gracza(mapa, poprzedni_ruch, stary_ostateczny1))
					{
						break;
					}
				}
				if (!czy_mozna_strzelic)
				{
					smierc_potwora = oddaj_strzal(mapa, poprzedni_ruch, stary_ostateczny, stary_ostateczny1); 
				}
				break;

			case 4:
				if (!czy_mozna_strzelic)
				{
					smierc_potwora = oddaj_strzal(mapa, poprzedni_ruch, stary_ostateczny, stary_ostateczny1);
				}
				break;

			case 5:
				if (czy_pokazywac_pierwszego)
				{
					wstawienie_potworka(mapa, granica_losowania);
					if (czy_zakonczyc = sprawdzenie_trafienia_gracza(mapa, poprzedni_ruch, stary_ostateczny))
					{
						break;
					}
				}
				if (czy_pokazywac_drugiego)
				{
					wstawienie_potworka1(mapa, granica_losowania);
					if (czy_zakonczyc = sprawdzenie_trafienia_gracza(mapa, poprzedni_ruch, stary_ostateczny1))
					{
						break;
					}
				}
				if (!czy_mozna_strzelic)
				{
					smierc_potwora = oddaj_strzal(mapa, poprzedni_ruch, stary_ostateczny, stary_ostateczny1); 
				}

				break;

			case 6:  wstawienie_gracza(mapa);
				if (!czy_mozna_strzelic)
				{
					smierc_potwora = oddaj_strzal(mapa, poprzedni_ruch, stary_ostateczny, stary_ostateczny1);
				}
				break;
		}
		licznik++;
		if (smierc_potwora == stary_ostateczny && czy_pokazywac_pierwszego == true)
		{
			smierc_potwora = -1;
			czy_pokazywac_pierwszego = false;
			smierc_potworka(mapa, hOut, 70, stary_ostateczny);
			continue;
		}
		else if (smierc_potwora == stary_ostateczny1 && czy_pokazywac_drugiego == true)
		{
			smierc_potwora = -1;
			czy_pokazywac_drugiego = false;
			smierc_potworka(mapa, hOut, 70, stary_ostateczny1);
			continue;
		}
		if (czy_pokazywac_pierwszego == false && czy_pokazywac_drugiego == false) 
		{
			wyswietlanie_wygranej(mapa, hOut, 70);
			break;
		}
		if (czy_zakonczyc)												
		{
			if (poprzedni_ruch == stary_ostateczny || poprzedni_ruch == stary_ostateczny1)
			{
				wyswietlanie_mapy_koncowej(mapa, hOut, 70);
				break;
				getchar();
			}
			else
				break;																			
		}
		wyswietlanie_mapy(mapa, 30);
	}
	return 0;
}

void wstawienie_potworka(char mapa[bok_pierwszy][bok_drugi], int granica_losowania)
{
	char *wsk = &mapa[0][0];

	static int nowy_ostateczny;
	static bool omin_pierwsze_przejscie = false;
	static bool zrob_tylko_raz = true;
	if (omin_pierwsze_przejscie)
	{
		*(wsk + (bok_drugi + 1) + stary_ostateczny) = ' ';
	}
	omin_pierwsze_przejscie = true;

	if (zrob_tylko_raz)
	{
		int respawn_potworka = rand() % (granica_losowania);
		int j = bok_drugi - 1;
		int liczba = bok_drugi - 3;
		int iloraz = respawn_potworka / liczba;
		nowy_ostateczny = respawn_potworka + (iloraz * 3);
		*(wsk + (bok_drugi + 1) + nowy_ostateczny) = 'M';
		stary_ostateczny = nowy_ostateczny;
		zrob_tylko_raz = false;
	}
	else
	{
		nowy_ostateczny = rand() % 5;
		switch (nowy_ostateczny) 
		{
		case 0: if (*(wsk + (bok_drugi + 1) + (stary_ostateczny - 1)) != '#' && *(wsk + (bok_drugi + 1) + (stary_ostateczny - 1)) != 'X' && *(wsk + (bok_drugi + 1) + (stary_ostateczny - 1)) != 'o' && *(wsk + (bok_drugi + 1) + (stary_ostateczny - 1)) != 'M')
		{
			*(wsk + (bok_drugi + 1) + (stary_ostateczny - 1)) = 'M';
			stary_ostateczny = stary_ostateczny - 1;
			break;
		}
				else											
					*(wsk + (bok_drugi + 1) + stary_ostateczny) = 'M';
			break;

		case 1: if (*(wsk + (bok_drugi + 1) + (stary_ostateczny + 1)) != '#' && *(wsk + (bok_drugi + 1) + (stary_ostateczny + 1)) != 'X' && *(wsk + (bok_drugi + 1) + (stary_ostateczny + 1)) != 'o' && *(wsk + (bok_drugi + 1) + (stary_ostateczny + 1)) != 'M')
		{
			*(wsk + (bok_drugi + 1) + (stary_ostateczny + 1)) = 'M';
			stary_ostateczny = stary_ostateczny + 1;
			break;
		}
				else
					*(wsk + (bok_drugi + 1) + stary_ostateczny) = 'M';
			break;

		case 2: if (*(wsk + (bok_drugi + 1) + (stary_ostateczny + bok_drugi)) != '#' && *(wsk + (bok_drugi + 1) + (stary_ostateczny + bok_drugi)) != 'X' && *(wsk + (bok_drugi + 1) + (stary_ostateczny + bok_drugi)) != 'o' && *(wsk + (bok_drugi + 1) + (stary_ostateczny + bok_drugi)) != 'M')
		{
			*(wsk + (bok_drugi + 1) + (stary_ostateczny + bok_drugi)) = 'M';
			stary_ostateczny = stary_ostateczny + bok_drugi;
			break;
		}
				else
					*(wsk + (bok_drugi + 1) + stary_ostateczny) = 'M';
			break;

		case 3: if (*((wsk + (bok_drugi + 1) + stary_ostateczny) - bok_drugi) != '#' && *(wsk + (bok_drugi + 1) + (stary_ostateczny - bok_drugi)) != 'X' && *(wsk + (bok_drugi + 1) + (stary_ostateczny - bok_drugi)) != 'o' && *(wsk + (bok_drugi + 1) + (stary_ostateczny - bok_drugi)) != 'M')
		{
			*((wsk + (bok_drugi + 1) + stary_ostateczny) - bok_drugi) = 'M';
			stary_ostateczny = stary_ostateczny - bok_drugi;
			break;
		}
				else
					*(wsk + (bok_drugi + 1) + stary_ostateczny) = 'M';
			break;
		case 4: *(wsk + (bok_drugi + 1) + stary_ostateczny) = 'M'; break;
		}
	}
}

void wstawienie_potworka1(char mapa[bok_pierwszy][bok_drugi], int granica_losowania)
{
	char *wsk = &mapa[0][0];
	static int nowy_ostateczny;
	static bool omin_pierwsze_przejscie = false;
	static bool zrob_tylko_raz = true;
	if (omin_pierwsze_przejscie)
	{
		*(wsk + (bok_drugi + 1) + stary_ostateczny1) = ' ';
	}
	omin_pierwsze_przejscie = true;

	if (zrob_tylko_raz)
	{
		int respawn_potworka = rand() % (granica_losowania);
		int j = bok_drugi - 1;
		int liczba = bok_drugi - 3;
		int iloraz = respawn_potworka / liczba;
		nowy_ostateczny = respawn_potworka + (iloraz * 3);
		*(wsk + (bok_drugi + 1) + nowy_ostateczny) = 'M';
		stary_ostateczny1 = nowy_ostateczny;
		zrob_tylko_raz = false;
	}
	else
	{
		nowy_ostateczny = rand() % 5;
		switch (nowy_ostateczny) 
		{
		case 0: if (*(wsk + (bok_drugi + 1) + (stary_ostateczny1 - 1)) != '#' && *(wsk + (bok_drugi + 1) + (stary_ostateczny1 - 1)) != 'X' && *(wsk + (bok_drugi + 1) + (stary_ostateczny1 - 1)) != 'o' && *(wsk + (bok_drugi + 1) + (stary_ostateczny1 - 1)) != 'M')
		{
			*(wsk + (bok_drugi + 1) + (stary_ostateczny1 - 1)) = 'M';
			stary_ostateczny1 = stary_ostateczny1 - 1;
			break;
		}
				else
					*(wsk + (bok_drugi + 1) + stary_ostateczny1) = 'M';
			break;

		case 1: if (*(wsk + (bok_drugi + 1) + (stary_ostateczny1 + 1)) != '#' && *(wsk + (bok_drugi + 1) + (stary_ostateczny1 + 1)) != 'X' && *(wsk + (bok_drugi + 1) + (stary_ostateczny1 + 1)) != 'o' && *(wsk + (bok_drugi + 1) + (stary_ostateczny1 + 1)) != 'M')
		{
			*(wsk + (bok_drugi + 1) + (stary_ostateczny1 + 1)) = 'M';
			stary_ostateczny1 = stary_ostateczny1 + 1;
			break;
		}
				else
					*(wsk + (bok_drugi + 1) + stary_ostateczny1) = 'M';
			break;

		case 2: if (*(wsk + (bok_drugi + 1) + (stary_ostateczny1 + bok_drugi)) != '#' && *(wsk + (bok_drugi + 1) + (stary_ostateczny1 + bok_drugi)) != 'X' && *(wsk + (bok_drugi + 1) + (stary_ostateczny1 + bok_drugi)) != 'o' && *(wsk + (bok_drugi + 1) + (stary_ostateczny1 + bok_drugi)) != 'M')
		{
			*(wsk + (bok_drugi + 1) + (stary_ostateczny1 + bok_drugi)) = 'M';
			stary_ostateczny1 = stary_ostateczny1 + bok_drugi;
			break;
		}
				else
					*(wsk + (bok_drugi + 1) + stary_ostateczny1) = 'M';
			break;

		case 3: if (*((wsk + (bok_drugi + 1) + stary_ostateczny1) - bok_drugi) != '#' && *(wsk + (bok_drugi + 1) + (stary_ostateczny1 - bok_drugi)) != 'X' && *(wsk + (bok_drugi + 1) + (stary_ostateczny1 - bok_drugi)) != 'o' && *(wsk + (bok_drugi + 1) + (stary_ostateczny1 - bok_drugi)) != 'M')
		{
			*((wsk + (bok_drugi + 1) + stary_ostateczny1) - bok_drugi) = 'M';
			stary_ostateczny1 = stary_ostateczny1 - bok_drugi;
			break;
		}
				else
					*(wsk + (bok_drugi + 1) + stary_ostateczny1) = 'M';
			break;
		case 4: *(wsk + (bok_drugi + 1) + stary_ostateczny1) = 'M'; break;
		}
	}

}

int obliczanie_pola_do_manewru()
{
	int podstawa = 3;
	int minimalne_pole_wolne = 1; 
	int pole_ostateczne;
	int roznica_miedzy_najmniejszym_a_wielkoscia_boku;
	int reszta_pomocnicza;
	int podstawa_liczbowa;
	int bok_pierwszy_do_obliczen;

	bok_pierwszy_do_obliczen = bok_pierwszy;
	reszta_pomocnicza = bok_pierwszy_do_obliczen - podstawa;
	podstawa_liczbowa = minimalne_pole_wolne + reszta_pomocnicza;
	pole_ostateczne = ((bok_drugi - podstawa)*podstawa_liczbowa);
	return pole_ostateczne;
}
