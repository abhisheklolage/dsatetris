 
#ifndef CONSTANTS_H
#define CONSTANTS_H

#define HEIGHT             25
#define WIDTH              80
#define PULSE         2000000 
#define DELAY_DOWN         10
#define DELAY_BOTTOM       20
#define CH_LEV              1
/* Windows dimensions */
#define WBOARD_HEIGHT      30
#define WBOARD_WIDTH       32
#define WBOARD_X            3 + 32
#define WBOARD_Y            3

#define WPREV_HEIGHT       10
#define WPREV_WIDTH        12
#define WPREV_X            38 + 32
#define WPREV_Y             3

#define WSCORE_HEIGHT      20
#define WSCORE_WIDTH       12
#define WSCORE_X           38 + 32
#define WSCORE_Y           3 + 10

#define WINSTR_HEIGHT      15
#define WINSTR_WIDTH       25 + 5
#define WINSTR_X           50 + 32
#define WINSTR_Y           3
#define WGENINSTR_HEIGHT      15
#define WGENINSTR_WIDTH       25 + 5
#define WGENINSTR_X           50 + 32
#define WGENINSTR_Y           3 + 15


#define POINTS               10

#define BOARD_HEIGHT ( WBOARD_HEIGHT - 2 )
#define BOARD_WIDTH  ( WBOARD_WIDTH  - 2 )

enum { MOVE, LEFT, RIGHT, DOWN, BOTTOM, ROTATE_L, ROTATE_R, SHADOW };
enum CK {  BB = 1, BR, BG, BY, BX, BM, BC, BW,              
               RB, RR, RG, RY, RX, RM, RC, RW,              
               GB, GR, GG, GY, GX, GM, GC, GW,              
               YB, YR, YG, YY, YX, YM, YC, YW,              
               XB, XR, XG, XY, XX, XM, XC, XW,              
               MB, MR, MG, MY, MX, MM, MC, MW,              
               CB, CR, CG, CY, CX, CM, CC, CW,              
               WB, WR, WG, WY, WX, WM, WC, WW, CKMAX };     

/* enum CK {  BB = 1, BR, BG, BY, BX, BM, BC, BW,              
               RB, RR, RG, RY, RX, RM, RC, RW,              
               GB, GR, GG, GY, GX, GM, GC, GW,              
               YB, YR, YG, YY, YX, YM, YC, YW,              
               XB, XR, XG, XY, XX, XM, XC, XW,              
               MB, MR, MG, MY, MX, MM, MC, MW,              
               CB, CR, CG, CY, CX, CM, CC, CW,              
               WB, WR, WG, WY, WX, WM, WC, WW, CKMAX };*/
#endif  // CONSTANTS_H
