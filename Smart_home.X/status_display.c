
#include "tft_master.h"
#include "tft_gfx.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "adc_intf.h"
#define BUTTON_WIDTH 60
#define BUTTON_HEIGHT 60

static char buffer[128];
//variable stores the length of the input number
static int length=0;
int pressed;
void screen_init()
{
    //set the screen as black
    SYSTEMConfigPerformance(PBCLK);
    //initialize screen
    tft_init_hw();
    tft_begin();
    tft_setRotation(1); 
    tft_fillScreen(ILI9341_CYAN);  
    
}
//create button structure variable contains the x,y coordinates, width,height and
//color of the button
void printState(int state) {
     switch (state) {
        case 0:
            sprintf(buffer, "%s", "STATE: IDLE");
            break;
        case 1:
            sprintf(buffer, "%s", "STATE: CMD");
            break;
        case 2:
            sprintf(buffer, "%s", "STATE: LIGHT");
            break;
        case 3:
            sprintf(buffer, "%s", "STATE: COOLING");
            break;
        case 4:
            sprintf(buffer, "%s", "STATE: WINDOW");
            break;
    }
    tft_setCursor(45, 50);
    tft_setTextSize(3);
    tft_setTextColor(ILI9341_BLACK);
    tft_writeString(buffer);
    
    sprintf(buffer, "%s", "ROBJACK Inc. 2018");
    tft_setCursor(65, 200);
    tft_setTextSize(2);
    tft_setTextColor(ILI9341_BLACK);
    tft_writeString(buffer);
    
    

    
}
struct button
{
    uint16_t x, y, w, h;
    uint16_t color;
    int current_state;
    int last_state;
    unsigned char name;
    int value;
};
//create 6 color buttons and one clear button
struct button NumBtn[10],btnC,btnEqual,btnAdd,btnSub,btnMul,btnDiv;

int i;



//create all the buttons and specify the parameters of the button's x,y coordinate,
//width, height and color.
void button_init()
{
    NumBtn[0].x = 60;
    NumBtn[1].x = 0;
    NumBtn[2].x = 60;
    NumBtn[3].x = 120;
    NumBtn[4].x = 0;
    NumBtn[5].x = 60;
    NumBtn[6].x = 120;
    NumBtn[7].x = 0;
    NumBtn[8].x = 60;
    NumBtn[9].x = 120;
    btnC.x = 0;
    btnEqual.x = 120;
    btnAdd.x = 180;
    btnSub.x = 180;
    btnMul.x = 180;
    btnDiv.x = 180;
            
    NumBtn[0].y = 260;
    NumBtn[1].y = 200;
    NumBtn[2].y = 200;
    NumBtn[3].y = 200;
    NumBtn[4].y = 140;
    NumBtn[5].y = 140;
    NumBtn[6].y = 140;
    NumBtn[7].y = 80;
    NumBtn[8].y = 80;
    NumBtn[9].y = 80;
    btnC.y = 260;
    btnEqual.y = 260;
    btnAdd.y = 260;
    btnSub.y = 200;
    btnMul.y = 140;
    btnDiv.y = 80;
    
    for(i=0;i<10;i++)
    {
        NumBtn[i].w = BUTTON_WIDTH;
    }
    btnC.w = BUTTON_WIDTH;
    btnEqual.w = BUTTON_WIDTH;
    btnAdd.w = BUTTON_WIDTH;
    btnSub.w = BUTTON_WIDTH;
    btnMul.w = BUTTON_WIDTH;
    btnDiv.w = BUTTON_WIDTH;
    
    for(i=0;i<10;i++)
    {
        NumBtn[i].h = BUTTON_HEIGHT;
    }
    btnC.h = 60;
    btnEqual.h = 60;
    btnAdd.h = 60;
    btnSub.h = 60;
    btnMul.h = 60;
    btnDiv.h = 60;
    
    for(i=0;i<10;i++)
    {
        NumBtn[i].color = ILI9341_BLACK;
    }
    btnC.color = ILI9341_RED;
    btnEqual.color = ILI9341_GREEN;
    btnAdd.color = ILI9341_BLUE;
    btnSub.color = ILI9341_BLUE;
    btnMul.color = ILI9341_BLUE;
    btnDiv.color = ILI9341_BLUE;
    
    for(i=0;i<10;i++)
    {
        NumBtn[i].value = i;
    }
    
    NumBtn[0].name = '0';
    NumBtn[1].name = '1';
    NumBtn[2].name = '2';
    NumBtn[3].name = '3';
    NumBtn[4].name = '4';
    NumBtn[5].name = '5';
    NumBtn[6].name = '6';
    NumBtn[7].name ='7';
    NumBtn[8].name ='8';
    NumBtn[9].name = '9';
    btnC.name = 'C';
    btnEqual.name = '=';
    btnAdd.name = '+';
    btnSub.name = '-';
    btnMul.name = '*';
    btnDiv.name = '/';
    
    for(i=0;i<10;i++)
    {
        NumBtn[i].current_state = 0;
    }
    btnC.current_state = 0;
    btnEqual.current_state = 0;
    btnAdd.current_state = 0;
    btnSub.current_state = 0;
    btnMul.current_state = 0;
    btnDiv.current_state = 0;
    
    for(i=0;i<10;i++)
    {
        NumBtn[i].last_state = 0;
    }
    btnC.last_state = 0;
    btnEqual.last_state = 0;
    btnAdd.last_state = 0;
    btnSub.last_state = 0;
    btnMul.last_state = 0;
    btnDiv.last_state = 0;
}
//functions that draw the given button outline with its color
void draw_button(struct button *btn)
{
tft_drawRect(btn->x,  btn->y,  btn->w,  btn->h,  ILI9341_WHITE);
}
//functions that fills the given button with its color
void fill_button(struct button *btn)
{
    tft_fillRect(btn->x,  btn->y,  btn->w,  btn->h,  btn->color);
}
//functions that add button name on the button 
void addButtonName(struct button *btn)
{
    tft_drawChar((btn->x)+20,  (btn->y)+20,btn->name,ILI9341_WHITE,btn->color,4);
}
//function that draws the outline of all buttons in specified position
void draw_buttons()
{
    for (i=0;i<10;i++)
    {
        fill_button(&NumBtn[i]);
    }
    fill_button(&btnC);
    fill_button(&btnEqual);
    fill_button(&btnAdd);
    fill_button(&btnSub);
    fill_button(&btnMul);
    fill_button(&btnDiv);
    
    for  (i=0;i<10;i++)
    {
        draw_button(&NumBtn[i]);
    }
    
    draw_button(&btnC);
    draw_button(&btnEqual);
    draw_button(&btnAdd);
    draw_button(&btnSub);
    draw_button(&btnMul);
    draw_button(&btnDiv);
    
    for  (i=0;i<10;i++)
    {
        addButtonName(&NumBtn[i]);
    }
    
    addButtonName(&btnC);
    addButtonName(&btnEqual);
    addButtonName(&btnAdd);
    addButtonName(&btnSub);
    addButtonName(&btnMul);
    addButtonName(&btnDiv);
}








