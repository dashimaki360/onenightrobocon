#ifndef LIB_LCD_COOKIE_MONSTER
#define LIB_LCD_COOKIE_MONSTER

#define LCD_MENU_NUM 4
typedef struct{
  int pos;
  int num;
  int param_pos[LCD_MENU_NUM];
  int param_num[LCD_MENU_NUM];
  char title[LCD_MENU_NUM][16];
  char param[LCD_MENU_NUM][16][16];
}Menu;

typedef struct{
  char mode[16];
  char option[3][16];
}Status;

void lcd_show_boot_logo(void);
void lcd_show_menu(Menu menu_st);
void lcd_show_run_st(Status st);
void lcd_set_font_size(void);


#endif //LIB_LCD_COOKIE_MONSTER
