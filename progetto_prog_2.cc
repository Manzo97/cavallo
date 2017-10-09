//X FEDE:
/* ti passo anche il pdf nel caso i coomenti non bastino. i valori li ho modificati ioper cercare di capure perchè lo sfondo non
full screen. Dacci un occhio. Scrivimi se hai bisogno
*/


#include <allegro.h> /*inclusione della libreria allegro per l'utilizzo delle sue funzionalità*/
#include <iostream>  /*inclusione della libreria iostream per l'utilizzo dello stdin e dello stdout */
using namespace std; /*direttiva propria del c++ per dichiarare l'uso dello spazio dei nomi della libreria standard */
BITMAP *buf, *sprite, *sfondo, *scrolling, *nemico; /*variabili BITMAP */
PALETTE gradocolori; /*variabile che indica al computer che profondità di colori utilizzare */
int x, y;/*variabili che indicano la posizione del giocatore */
int moltiplica; 
int xscroll;
int xn, yn;
int xmovnemico, ymovnemico;
int morto;

void doppiobuffering() /*funzione per aggiornamento dello schermo*/
{
vsync(); /* serve per la sincronizzare l'aggiornamento dello schermo*/
blit(buf, screen, 0, 0, 0, 0, 1800, 2000);/* blit prende il contenuto disegnato nel buf visualizzandolo sullo screen partendo dall'angolo (0,0) fino all'angolo (320,200)*/
clear(buf); /*pulisce il buf per permettere l'inserimento di nuove scene(senza vi è una sovrapposizione di immagini) */
}

void giocatore() /*funzione per visualizzazione del giocatore */
{
	 if (morto == 1) /*se non c'è stata una collisione(morto = 0) visualizza lo sprite(giocatore) */
	 draw_sprite(screen, sprite, x, y);/* visualizza l'immagine sullo schermo(screen) contenuta in sprite alle coordinate x e y  */	
}

void aggiungisfondo()
{
xscroll = xscroll +1;
blit(scrolling, buf, xscroll, 0, 0, 0, 1200, 800);
if (xscroll > 319)
	{
	xscroll = 0;
	}
}

void movimento()
	{
	if (key[KEY_LEFT]) x = x - 1; 
		if (x <= 0) x = 0;
	if (key[KEY_RIGHT]) x = x + 1; 
		if (x >= 5000) x = 300;
	if (key[KEY_UP]) y = y -1; 
		if (y <= 0) y = 0;
	if (key[KEY_DOWN]) y = y + 1; 
		if (y >= 5000) y = 180;
	}

void enemy()
{
draw_sprite(buf, nemico, xn, yn);
}

void movimentoenemy()
{
if (ymovnemico == 1)
	{
	yn -= 1;
	if (yn <= 10)
		ymovnemico= 2;
	}
if (ymovnemico == 2)
	{
	yn += 1;
	if (yn >= 150)
		ymovnemico=3;
	}
if (ymovnemico == 3)
	{
	xn -= 1;
	xmovnemico +=1;
	if (xmovnemico >= 40)
		{
		xmovnemico =0;
		ymovnemico =1;
		}
	}
if (xn <=-50)
	{
	xn = 360;
	yn = 10;
	ymovnemico = 3;
	}
} 

void collisione()
{
if (((x+30) >= xn) && (x <= (xn +40)))
	{
	if (((y+20) >= yn) && (y <= (yn +31)))
	morto =0; /*collisione avvenuta, è morto*/
	}
}

int main() /*da inizio alla videogioco */
{
allegro_init(); /*indica che viene utilizzata la libreria allegro.h e che devono essere attivate le sue funzioni*/
install_keyboard(); /*serve ad indicare al programma che verrà utilizzata la tastiera */
set_color_depth(32); /*definisce la profondità delle immagini(32 bit) */
set_palette(gradocolori); /* definisce la variabile gradocolori */
set_gfx_mode(GFX_SAFE, 1200, 800, 0, 0);/* indica al computer quale modalità grafica utilizzare, con autodetect scegli "la più appropiata" automaticamente*/
buf= create_bitmap(1200, 800);/* definice la dimensione del bitmap di buf(buffer) in una matrice di pixel (320,200) */
clear(buf); /*pulisce il buffer creato nella riga precedente*/
sprite = load_bmp("jeytor.bmp", gradocolori); /*carico dentro sprite(GIOCATORE) l'immagine jeytor.bmp(STESSA DIRECTORY) */
sfondo = load_bmp("okko.bmp", gradocolori);/*uso come sfondol'immagine okko.bmp */
nemico = load_bmp("ciao.bmp", gradocolori); /*carico dentro nemico l'immagine ciao.bmp */
scrolling = create_bitmap(1200, 800);
clear(scrolling);
for(moltiplica = 0; moltiplica <= 5000; moltiplica += 320)
	{
	blit(sfondo, scrolling, 0, 0, moltiplica, 0, 1200, 800);
	}
morto=1;

x= 10;
y= 30;

xn= 250;
yn= 100;

xmovnemico = 3;
ymovnemico = 1;

while (!key[KEY_ESC]) /* ciclo infinito per la visualizzazzione del gioco(brekka se si preme ESC)*/
	{
	doppiobuffering(); /*vado a richaimare doppiobuffering per la visualizzazione schermo */
	aggiungisfondo();
	giocatore();	
	movimento();
	enemy();
	movimentoenemy();
	collisione();
	}
destroy_bitmap(buf); /* distrugge il bitmap della variabile per evitare problemi di memoria */
destroy_bitmap(sprite);/* distrugge il bitmap della variabile per evitare problemi di memoria */
destroy_bitmap(sfondo);/* distrugge il bitmap della variabile per evitare problemi di memoria */
destroy_bitmap(nemico);/* distrugge il bitmap della variabile per evitare problemi di memoria */
destroy_bitmap(scrolling);/* distrugge il bitmap della variabile per evitare problemi di memoria */
}
END_OF_MAIN(); /* comando per la chiusura dei programmi di window senza intoppi*/



