#ifndef MODE_CHECKER_COOKIE_MONSTER
#define MODE_CHECKER_COOKIE_MONSTER

typedef enum Mode {
  START,
  FLAT,
  BRIDGE,
  DISPLAY,
  TONNEL,
  BALL,
  END
}Mode;

void  mc_cyc(intptr_t exinf);
Mode mc_get_mode(void);
void mc_update_mode(void);

#endif // MODE_CHECKER_COOKIE_MONSTER
