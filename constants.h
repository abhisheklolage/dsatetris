 
#ifndef COMMON_CONST_H
#define COMMON_CONST_H

#define HEIGHT             50              
#define WIDTH              80              
#define PULSE         5000000              
#define DELAY_DOWN         3              
#define DELAY_BOTTOM       5            
#define CH_LEV             20              

#define WBOARD_HEIGHT      30              
#define WBOARD_WIDTH       50              
#define WBOARD_X           20              
#define WBOARD_Y            3              

#define WPREV_HEIGHT        6              
#define WPREV_WIDTH        12              
#define WPREV_X            38              
#define WPREV_Y             3              

#define WSCORE_HEIGHT      13              
#define WSCORE_WIDTH       12              
#define WSCORE_X           38              
#define WSCORE_Y           10              

#define POINTS               10              

#define BOARD_HEIGHT ( WBOARD_HEIGHT - 2 )  
#define BOARD_WIDTH  ( WBOARD_WIDTH  - 2 ) 


enum { MOVE, LEFT, RIGHT, DOWN, BOTTOM, ROTATE_L, ROTATE_R };

enum CK {  BB = 1, BR, BG, BY, BX, BM, BC, BW,              
               RB, RR, RG, RY, RX, RM, RC, RW,              
               GB, GR, GG, GY, GX, GM, GC, GW,              
               YB, YR, YG, YY, YX, YM, YC, YW,              
               XB, XR, XG, XY, XX, XM, XC, XW,              
               MB, MR, MG, MY, MX, MM, MC, MW,              
               CB, CR, CG, CY, CX, CM, CC, CW,              
               WB, WR, WG, WY, WX, WM, WC, WW, CKMAX };     


#endif  // CONSTANTS_H