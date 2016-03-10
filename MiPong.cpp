#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>

ALLEGRO_DISPLAY *ventana;

int main(int argc, char **argv)
{
	
	ALLEGRO_KEYBOARD_STATE estadoTeclado;
	
	bool inicio_allegro = al_init();
	bool teclado = al_install_keyboard();
	al_init_primitives_addon();
	al_init_ttf_addon();
	if(!inicio_allegro) 
	{
		fprintf(stderr, "Error: Allegro no pudo iniciar.\n");
		return -1;
	}
	
	if(!teclado) 
	{
		fprintf(stderr, "Error: El teclado no se detecto.\n");
		return -1;
	}	
	const int Mx = 600;
	const int My = 600;
	al_create_display(Mx,My);
	
	int circuloX=Mx/2;
	int circuloY=My/2;
	const int cirtuloTam=5;
	int velocidadX=5;
	int velocidadY=5;
	
	const int velocidadBarra=5;
	
	int rec1X=Mx/2;
	const int rec1Y=500;
	
	int rec2X=Mx/2;
	const int rec2Y=100;
	
	const int rectTam=30;
	
	ALLEGRO_FONT *FuentePuntuacion;
	FuentePuntuacion = al_load_ttf_font("Grundschrift-Bold.otf", 12,0);
	
	ALLEGRO_FONT *FuenteMenu;
	FuenteMenu = al_load_ttf_font("Grundschrift-Bold.otf", 20,0);

	int puntosJ1=0;
	char jugador1[40];
	int puntosJ2=0;
	char jugador2[40];
	char puntos [3];
	
	bool menu=true;
	while(1)
	{
		//printf("*********circulo: x=%d y=%d barraV: x=%d y=%d barraA: x=%d y=%d*********\r",circuloX,circuloY,rec1X,rec1Y,rec2X,rec2Y);
		al_get_keyboard_state(&estadoTeclado);
		if (al_key_down(&estadoTeclado, ALLEGRO_KEY_ESCAPE)) 
		{
			break;
		}
		if(menu==false)
		{
			if(puntosJ1<10 && puntosJ2<10)
			{
				al_draw_line(0,Mx/2,My,Mx/2,al_map_rgb(0,0,0),2);
				if (al_key_down(&estadoTeclado, ALLEGRO_KEY_M)) 
				{
					menu=true;
				}
				if (al_key_down(&estadoTeclado, ALLEGRO_KEY_RIGHT) && rec1X<Mx-(rectTam*2)) 
				{
					rec1X+=velocidadBarra;
				}
				if(al_key_down(&estadoTeclado, ALLEGRO_KEY_LEFT) && rec1X>0) 
				{
					rec1X-=velocidadBarra;
				}
				
				
				if(al_key_down(&estadoTeclado, ALLEGRO_KEY_A) && rec2X>0) 
				{
					rec2X-=velocidadBarra;
				}
				
				if (al_key_down(&estadoTeclado, ALLEGRO_KEY_D) && rec2X<Mx-(rectTam*2)) 
				{
					rec2X+=velocidadBarra;
				}
				sprintf(puntos,"%d",puntosJ1);
				//itoa (puntosJ1,puntos,10);
				strcpy (jugador1,"Jugador Azul: ");
				strcat (jugador1,puntos);
				strcat (jugador1," puntos");
				al_draw_text(FuentePuntuacion,al_map_rgb(0,0,0), 50, 50,ALLEGRO_ALIGN_LEFT,jugador1);
				
				sprintf(puntos, "%d",puntosJ2);
				//itoa (puntosJ2,puntos,10);
				strcpy (jugador2,"Jugador Verde: ");
				strcat (jugador2,puntos);
				strcat (jugador2," puntos");
				al_draw_text(FuentePuntuacion,al_map_rgb(0,0,0), Mx-200, My-50,ALLEGRO_ALIGN_LEFT,jugador2);
				
				al_draw_filled_circle(circuloX,circuloY,cirtuloTam,al_map_rgb(200,0,0));
				al_draw_filled_rectangle(rec1X,rec1Y,rec1X+(2*rectTam),rec1Y+(rectTam/3),al_map_rgb(0,100,0));
				al_draw_filled_rectangle(rec2X,rec2Y,rec2X+(2*rectTam),rec2Y+(rectTam/3),al_map_rgb(0,0,100));
					
				if(circuloX==0 || circuloX==Mx)
				{
					velocidadX=velocidadX*-1;
				}
				if( circuloY==0 || circuloY==My )
				{
					velocidadY=velocidadY*-1;
				}
				if(( circuloY>=rec1Y && circuloY<=rec1Y+((rectTam/3)/2) && circuloX>=rec1X && circuloX<=rec1X+(2*rectTam)) )
				{
					velocidadY=-5;
				}
				if(( circuloY>=rec1Y+((rectTam/3)/2) && circuloY<=rec1Y+(rectTam/3) && circuloX>=rec1X && circuloX<=rec1X+(2*rectTam)) )
				{
					velocidadY=5;
				}
				if((circuloY>=rec2Y && circuloY<=rec2Y+((rectTam/3)/2) && circuloX>=rec2X && circuloX<=rec2X+(2*rectTam)) )
				{
					velocidadY=-5;
				}
				if((circuloY>=rec2Y+((rectTam/3)/2) && circuloY<=rec2Y+(rectTam/3) && circuloX>=rec2X && circuloX<=rec2X+(2*rectTam)) )
				{
					velocidadY=5;
				}
				if(circuloY==My)
				{
					puntosJ1++;
				}
				if(circuloY==0)
				{
					puntosJ2++;
				}
				circuloX+=velocidadX;
				circuloY+=velocidadY;
			}
			else
			{
				if(puntosJ1==10)
				{
					al_draw_text(FuenteMenu,al_map_rgb(0,0,0), Mx/2, My/2,ALLEGRO_ALIGN_CENTRE,"Jugador Azul gana");

				}
				else
				{
					al_draw_text(FuenteMenu,al_map_rgb(0,0,0), Mx/2, My/2,ALLEGRO_ALIGN_CENTRE,"Jugador Verde gana");
				}
				al_draw_text(FuenteMenu,al_map_rgb(0,0,0), Mx/2, My/2+50,ALLEGRO_ALIGN_CENTRE,"Presiona Esc para salir");
				al_draw_text(FuenteMenu,al_map_rgb(0,0,0), Mx/2, My/2+75,ALLEGRO_ALIGN_CENTRE,"o M para seguir jugando");
				if (al_key_down(&estadoTeclado, ALLEGRO_KEY_M)) 
				{
					menu=true;
					puntosJ1=0;
					puntosJ2=0;
					circuloX=Mx/2;
					circuloY=My/2;
				}
			}
		}
		else
		{
			al_draw_text(FuenteMenu,al_map_rgb(0,0,0), 50, 50,ALLEGRO_ALIGN_LEFT,"Instrucciones:");
			al_draw_text(FuenteMenu,al_map_rgb(0,0,0), 50, 75,ALLEGRO_ALIGN_LEFT,"Golpea la pelota para evitar que tu oponente gane puntos.");
			
			al_draw_text(FuenteMenu,al_map_rgb(0,0,0), 50, 125,ALLEGRO_ALIGN_LEFT,"Controles:");
			al_draw_text(FuenteMenu,al_map_rgb(0,0,0), 50, 150,ALLEGRO_ALIGN_LEFT,"*Esc           Salir del juego");
			al_draw_text(FuenteMenu,al_map_rgb(0,0,0), 50, 175,ALLEGRO_ALIGN_LEFT,"*Flacha Izquierda  Mover a izquierda (jugador verde)");
			al_draw_text(FuenteMenu,al_map_rgb(0,0,0), 50, 200,ALLEGRO_ALIGN_LEFT,"*Flacha Derecha   Mover a Derecha (jugador verde)");
			al_draw_text(FuenteMenu,al_map_rgb(0,0,0), 50, 225,ALLEGRO_ALIGN_LEFT,"*A             Mover a izquierda (jugador azul)");
			al_draw_text(FuenteMenu,al_map_rgb(0,0,0), 50, 250,ALLEGRO_ALIGN_LEFT,"*D             Mover a Derecha (jugador azul)");
			al_draw_text(FuenteMenu,al_map_rgb(0,0,0), 50, 275,ALLEGRO_ALIGN_LEFT,"*M             Volver al menu");
			al_draw_text(FuenteMenu,al_map_rgb(0,0,0), 50, 300,ALLEGRO_ALIGN_LEFT,"*Espacio         Comenzar a jugar");
			al_draw_text(FuenteMenu,al_map_rgb(0,0,0), Mx/2, 400,ALLEGRO_ALIGN_CENTRE,"Este es software libre y se distribuye bajo la licencia GLP");
			al_draw_text(FuenteMenu,al_map_rgb(0,0,0), Mx/2, 425,ALLEGRO_ALIGN_CENTRE,"Charles Fernando Velazquez Dodge 2014");
			if (al_key_down(&estadoTeclado, ALLEGRO_KEY_SPACE)) 
			{
				menu=false;
			}
		}
		al_flip_display();
		al_rest(0.02);
		al_clear_to_color(al_map_rgb(255,255,255));
	}
	al_destroy_display(ventana);
	return 0;
} 
