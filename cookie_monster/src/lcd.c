#include "inc/lcd.h"
#include "ev3api.h"

static const int MN_TITLE_W = 10;
static const int MN_PARAM_W = 10;
static const int MN_SPACE = 1;
static const int MN_CURSOL = 1;
static const int RUN_OPTION_NUM =3;
static int font=EV3_FONT_MEDIUM;
static int32_t font_w=0;
static int32_t font_h=0;

void w_mn_title(const Menu);
void w_mn_cursol(const Menu);
void w_mn_param(const Menu);
void w_lcd(const char* str, int x, int y);

void lcd_set_font_size(void){
	ev3_lcd_set_font(font);
	ev3_font_get_size(font, &font_w, &font_h);
  return;
}

void lcd_show_boot_logo(void){
  //TODO more nice logo
  w_lcd("COOKIE MONSTER\nMUSYA MUSYA ",0,0);
  return;
}

void lcd_show_menu(Menu mn){
  ev3_lcd_fill_rect(0,0,EV3_LCD_WIDTH,EV3_LCD_HEIGHT,EV3_LCD_WHITE);
  w_mn_cursol(mn);
  w_mn_title(mn);
  w_mn_param(mn);
  return;
}

void lcd_show_run_st(Status st){
  w_lcd(st.mode, 0, 1);
  for(int i=0; i<RUN_OPTION_NUM; i++){
    w_lcd(st.option[i], 0, i+4);
  }

  ev3_lcd_draw_string("run status test",0,0);
  return;
}

void w_mn_cursol(const Menu mn){
  for(int i=0; i<mn.num; i++){
    w_lcd(" ",MN_SPACE,i);
  }
  w_lcd(">",MN_SPACE,mn.pos);
  return;
}

void w_mn_title(const Menu mn){
  for(int i=0; i<mn.num; i++){
    w_lcd(mn.title[i],MN_SPACE+MN_CURSOL,i);
  }
  return;
}

void w_mn_param(const Menu mn){
  for(int i=0; i<mn.num; i++){
    w_lcd(mn.param[i][mn.param_pos[i]],MN_SPACE+MN_CURSOL+MN_TITLE_W+MN_SPACE, i);
  }
  return;
}

void w_lcd(const char* str, int x, int y){
  ev3_lcd_draw_string(str, x*font_w, y*font_h);
  return;
}

