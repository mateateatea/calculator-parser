#include <allegro5/allegro.h>
#include <stdbool.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
#include "parser.h"
#include <string.h>

int start_gui(){
    al_init();
    char expression[100] = "";
    al_install_mouse();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_DISPLAY *display = al_create_display(430, 784);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_FONT *font = al_load_ttf_font("Inter-VariableFont_opsz,wght.ttf", 32, 0);
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue,al_get_display_event_source(display));
    bool running = true;
    while (running){
        al_clear_to_color(al_map_rgb(12,12,12));
        al_draw_text(font, al_map_rgb(255, 255, 255), 250, 50, ALLEGRO_ALIGN_CENTER, "Witaj w Kalkulatorze!");
        int startX = 25;
        int startY = 275;
        int buttonSize = 80;
        int spacing = 20;

        const char *labels[5][4] = {
            {"AC", "+/-", "%", "/"},
            {"7", "8", "9", "*"},
            {"4", "5", "6", "-"},
            {"1", "2", "3", "+"},
            {"C", "0", ".", "="} 
        };
// To narysuje to, co aktualnie jest w pamięci kalkulatora
// 390 to prawa krawędź (wyrównanie do prawej), 150 to wysokość
al_draw_text(font, al_map_rgb(255, 255, 255), 390, 150, ALLEGRO_ALIGN_RIGHT, expression);
       
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 4; col++) {
                if ((row == 4 && col == 0) || (row == 4 && col == 1) || (row == 4 && col == 3)) continue;

                int x1 = startX + col * (buttonSize + spacing);
                int y1 = startY + row * (buttonSize + spacing);
                int x2 = x1 + buttonSize;
                int y2 = y1 + buttonSize;

                
                al_draw_filled_rounded_rectangle(x1, y1, x2, y2, 15, 15, al_map_rgb(60, 60, 60));

                
                ALLEGRO_COLOR textColor = al_map_rgb(255, 255, 255);
                if (row == 0 || col == 3) {
                    textColor = al_map_rgb(0, 229, 255); 
                }

            
                int textX = x1 + buttonSize / 2;
                int textY = y1 + buttonSize / 2 - 16;
                al_draw_text(font, textColor, textX, textY, ALLEGRO_ALIGN_CENTER, labels[row][col]);
            }
        }
    
        int z0_x1 = startX;
        int z0_y1 = startY + 4 * (buttonSize + spacing);
        int z0_x2 = z0_x1 + 2 * buttonSize + spacing;
        int z0_y2 = z0_y1 + buttonSize;


        al_draw_filled_rounded_rectangle(z0_x1, z0_y1, z0_x2, z0_y2, 15, 15, al_map_rgb(60, 60, 60));


        int z0_textX = z0_x1 + (2 * buttonSize + spacing) / 2;
        int z0_textY = z0_y1 + buttonSize / 2 - 16;
        al_draw_text(font, al_map_rgb(255, 255, 255), z0_textX, z0_textY, ALLEGRO_ALIGN_CENTER, "0");
    
        int eq_x1 = startX + 3 * (buttonSize + spacing);
        int eq_y1 = startY + 4 * (buttonSize + spacing);
        int eq_x2 = eq_x1 + buttonSize;
        int eq_y2 = eq_y1 + buttonSize;

       
        al_draw_filled_rounded_rectangle(eq_x1, eq_y1, eq_x2, eq_y2, 15, 15, al_map_rgb(0, 229, 255));

        int eq_textX = eq_x1 + buttonSize / 2;
        int eq_textY = eq_y1 + buttonSize / 2 - 16;
        al_draw_text(font, al_map_rgb(20, 20, 20), eq_textX, eq_textY, ALLEGRO_ALIGN_CENTER, "=");
        al_flip_display();
        ALLEGRO_EVENT event;
        al_wait_for_event(queue,&event);
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = false;
        }
if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
    int mX = event.mouse.x;
    int mY = event.mouse.y;

    // 1. Sprawdzamy standardową siatkę (w pętli)
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 4; col++) {
            // Pomijamy puste miejsca po zerze
            if (row == 4 && (col == 0 || col == 1)) continue;

            int x1 = startX + col * (buttonSize + spacing);
            int y1 = startY + row * (buttonSize + spacing);
            int x2 = x1 + buttonSize;
            int y2 = y1 + buttonSize;

            // JEŚLI TRAFILIŚMY MYSZKĄ W TEN KONKRETNY GUZIK
            if (mX >= x1 && mX <= x2 && mY >= y1 && mY <= y2) {
                
                if (strcmp(labels[row][col], "=") == 0) {
                    // LOGIKA PARSERA
                    const char *pos = expression;
                    float result = parser_additive(&pos);
                    
                    if (isnan(result)) strcpy(expression, "Error");
                    else if (result == INFINITY) strcpy(expression, "Div by 0");
                    else snprintf(expression, sizeof(expression), "%.2f", result);
                } 
                else if (strcmp(labels[row][col], "AC") == 0) {
                    // CZYŚCIMY WYŚWIETLACZ
                    expression[0] = '\0';
                } 
                else {
                    // DOPISUJEMY CYFRĘ/ZNAK DO WYŚWIETLACZA
                    // (Tylko jeśli mamy jeszcze miejsce w tablicy)
                    if (strlen(expression) < sizeof(expression) - 2) {
                        strcat(expression, labels[row][col]);
                    }
                }
            }
        }
    }

    // 2. Osobno sprawdzamy szerokie '0'
    if (mX >= z0_x1 && mX <= z0_x2 && mY >= z0_y1 && mY <= z0_y2) {
        if (strlen(expression) < sizeof(expression) - 2) {
            strcat(expression, "0");
        }
    }
}
    }
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    return 0;
}
    