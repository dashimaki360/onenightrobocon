#ifndef MODE_CHECKER_COOKIE_MONSTER
#define MODE_CHECKER_COOKIE_MONSTER

typedef enum Mode {
  START,
  FLAT1,
  BRIDGE,
  FLAT2,
  DISPLAY,
  FLAT3,
  TONNEL,
  FLAT4,
  BALL,
  END
}Mode;

void  mc_cyc(intptr_t exinf);
Mode mc_get_mode(void);
void mc_update_mode(void);
void mc_set_init_mode(Mode);
void mc_set_mode_fix(void);
void mc_release_mode_fix(void);
#endif // MODE_CHECKER_COOKIE_MONSTER
