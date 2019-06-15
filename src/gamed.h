
const unsigned int omok_startup[];
const unsigned int omok_map[];
const unsigned int black_dol[];
const unsigned int white_dol[];
const unsigned int selector[];

 unsigned int mapa[15][15];

 extern void restoreDols(unsigned int x, unsigned int y);
 extern void putDol(unsigned int x, unsigned int y, unsigned int team, unsigned int animation);
 extern void putSelector(unsigned int x, unsigned int y, unsigned int oldx, unsigned int oldy);


 unsigned int selector_x;
 unsigned int selector_y;


 int enemy_x;
 int enemy_y;

 int tick;

int sendUSBCDC;
int selectedx_s;
int selectedy_s;

int joystick;


