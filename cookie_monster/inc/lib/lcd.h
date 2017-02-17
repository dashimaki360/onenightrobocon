#ifndef LIB_LCD_COOKIE_MONSTER
#define LIB_LCD_COOKIE_MONSTER

void lcd_show_boot_logo(void);
void lcd_show_init_menu(Menu menu_st);
void lcd_show_run_st(Status st);
void lcd_set_font_size(void);

typedef struct{
  int pos;
  int num;
  char title[10][64];
  char param;
}Menu;

typedef struct{
  char menu[64];
  char option[3][64];
}Status;


#endif //LIB_LCD_COOKIE_MONSTER
