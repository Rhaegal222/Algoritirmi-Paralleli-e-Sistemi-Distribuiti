// disegnare una stringa sul display con allegro

/* g++ prova2.cpp -o prova2 -lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf */

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
int main()
{
    al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();

	ALLEGRO_DISPLAY *display;
	ALLEGRO_FONT * font = al_load_ttf_font("YARDSALE.ttf", 30, 0);
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_EVENT event;

    al_init();	
    display = al_create_display(600, 400);
	al_flip_display();

    queue = al_create_event_queue(); 
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(102, 204, 255)); // colore sfondo	

    while (true) {

        al_peek_next_event(queue, &event);
        if((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;
        
        al_clear_to_color(al_map_rgb(143, 180, 240)); // colore sfondo
        al_draw_text(font, al_map_rgb(213, 255, 179), 0, 0,ALLEGRO_ALIGN_LEFT, "Hello World"); //font, colore font coord x coord y, allineamento  , 'testo'    
        al_flip_display();
    }
}