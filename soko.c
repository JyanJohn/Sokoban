#include <ncurses.h>
#include <stdlib.h>

struct Object
{
    int xPosition;
    int yPosition;
    unsigned char zn;
    chtype ozn;
};

#define N 10
struct Object obj[N] = {};

int wbox = 0;
int lev = 0;

void levList(int *h, int *w, int *array, int y, int x, int n)
{
    if (n == 0)
    {
	*h = 7;
        *w = 6;
	int map0[7][6] = {
	{1,1,1,1,1,1},
        {1,0,2,1,1,1},
        {1,0,0,1,1,1},
        {1,2,5,0,0,1},
        {1,4,0,4,0,1},
        {1,0,0,1,1,1},
        {1,1,1,1,1,1}};
        *array = map0[y][x];
     }
     else if (n == 1)
     {
        *h = 9;
        *w = 10;
        int map1[9][10] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,1,1,1,1,1,1},
        {1,0,1,0,1,0,2,1,1,1},
        {1,0,0,0,0,4,0,1,1,1},
        {1,1,1,0,1,4,2,0,0,1},
        {1,0,0,0,1,5,0,0,0,1},
        {1,0,1,0,1,1,1,1,1,1},
        {1,0,0,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1}};
        *array = map1[y][x];
     }
     else if (n == 2)
     {
        *h = 9;
        *w = 11;
        int map2[9][11] = {
        {0,0,0,0,0,1,1,1,1,1,1},
        {0,0,0,0,0,1,0,0,0,1,1},
        {0,0,0,0,0,1,0,0,0,0,1},
        {0,1,1,1,1,1,1,0,0,0,1},
        {1,1,0,0,0,0,0,1,2,0,1},
        {1,0,4,0,4,0,5,0,0,1,1},
        {1,0,1,1,1,1,1,1,2,1,1},
        {1,0,0,0,0,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,1,1,1,1}};
        *array = map2[y][x];
     }
     //..........and so on..........
}

void palette()
{
    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
}

void Level(int n)
{
    clear();
    mvprintw(1,8, "СОКОБАН! Map -> %d",lev);
    mvprintw(2,1, "Move-WSAD, Restart-R, Map-M, Exit-Q.");
    int x = 0, y = 0, h = 1, w = 1, map;
    wbox = 0;

    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            levList(&h, &w, &map, y, x, n);
            switch(map)
            {
                case 0: mvaddch(y+4,x+10,'-' | COLOR_PAIR(4)); break;
                case 1: mvaddch(y+4,x+10,'#' | COLOR_PAIR(1)); break;
                case 2: mvaddch(y+4,x+10,'x' | COLOR_PAIR(2)); break;
                case 4:
                    mvaddch(y+4,x+10,'-' | COLOR_PAIR(4));
                    wbox += 1;
                    obj[wbox].ozn = mvinch(y+4,x+10);
                    obj[wbox].yPosition = y+4;
                    obj[wbox].xPosition = x+10;
                    obj[wbox].zn = '@';
                    mvaddch(obj[wbox].yPosition,obj[wbox].xPosition,obj[wbox].zn | COLOR_PAIR(5));
                    break;
                case 5:
                    mvaddch(y+4,x+10,'-' | COLOR_PAIR(4));
                    obj[0].ozn = mvinch(y+4,x+10);
                    obj[0].yPosition = y+4;
                    obj[0].xPosition = x+10;
                    obj[0].zn = 'P';
                    mvaddch(obj[0].yPosition,obj[0].xPosition,obj[0].zn | COLOR_PAIR(3));
                    break;
            }
        }
    }
    move(obj[0].yPosition,obj[0].xPosition);
}

void Play(int input)
{
    bool restart = FALSE;

    chtype up, lf, dw, rg, oup, olf, odw, org;
    up = (mvinch(obj[0].yPosition-1,obj[0].xPosition) & A_CHARTEXT);
    lf = (mvinch(obj[0].yPosition,obj[0].xPosition-1) & A_CHARTEXT);
    dw = (mvinch(obj[0].yPosition+1,obj[0].xPosition) & A_CHARTEXT);
    rg = (mvinch(obj[0].yPosition,obj[0].xPosition+1) & A_CHARTEXT);
    oup = (mvinch(obj[0].yPosition-2,obj[0].xPosition) & A_CHARTEXT);
    olf = (mvinch(obj[0].yPosition,obj[0].xPosition-2) & A_CHARTEXT);
    odw = (mvinch(obj[0].yPosition+2,obj[0].xPosition) & A_CHARTEXT);
    org = (mvinch(obj[0].yPosition,obj[0].xPosition+2) & A_CHARTEXT);

    for( int o = 0; o <= wbox; o++) { mvaddch(obj[o].yPosition, obj[o].xPosition, obj[o].ozn);}

    switch(input)
    {
        case 'w':
        case 'W':
            if (up != 35)
            {
                 if (up == 64 && (oup == 45 || oup == 120))
                 {
                     obj[0].yPosition -= 1;
                     for ( int o = 1; o <= wbox; o++)
                     {
                         if ((obj[0].yPosition == obj[o].yPosition) &&  (obj[0].xPosition == obj[o].xPosition))
                             {
                                 obj[o].yPosition -= 1;
                             }
                     }
                 }
                else if (up != 64) obj[0].yPosition -= 1;
            }
            break;
        case 's':
        case 'S':
            if (dw != 35)
            {
                 if (dw == 64 && (odw == 45 || odw == 120))
                 {
                     obj[0].yPosition += 1;
                     for ( int o = 1; o <= wbox; o++)
                     {
                         if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition))
                             {
                                 obj[o].yPosition += 1;
                             }
                     }
                 }
                else if (up != 64) obj[0].yPosition += 1;
            }
            break;
        case 'a':
        case 'A':
            if (lf != 35)
            {
                 if (lf == 64 && (olf == 45 || olf == 120))
                 {
                     obj[0].xPosition -= 1;
                     for ( int o = 1; o <= wbox; o++)
                     {
                         if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition))
                             {
                                 obj[o].xPosition -= 1;
                             }
                     }
                 }
                else if (lf != 64) obj[0].xPosition -= 1;
            }
            break;
        case 'd':
        case 'D':
            if (rg != 35)
            {
                 if (lf == 64 && (org == 45 || org == 120))
                 {
                     obj[0].xPosition += 1;
                     for ( int o = 1; o <= wbox; o++)
                     {
                         if ((obj[0].yPosition == obj[o].yPosition) && (obj[0].xPosition == obj[o].xPosition))
                             {
                                 obj[o].xPosition += 1;
                             }
                     }
                 }
                else if (lf != 64) obj[0].xPosition += 1;
            }
            break;
        case 'm':
        case 'M':
            restart = TRUE;
            if(lev <2) lev += 1;
            else lev = 0;
            Level(lev);
            break;

        case 'r':
        case 'R':
            restart = TRUE;
            Level(lev);
            break;
	default:
            break;
    }
    if (!restart)
    {
        for( int o = 0; o <= wbox; o++)
        {
            obj[o].ozn = mvinch(obj[o].yPosition,obj[o].xPosition);
            mvaddch(obj[o].yPosition,obj[o].xPosition,obj[o].zn | ((o == 0) ? COLOR_PAIR(3) : COLOR_PAIR(5)));
        }
        move(obj[0].yPosition,obj[0].xPosition);
    }
    else restart = FALSE;
}

int main ()
{
     int ch;

     initscr();

     if (!has_colors())
     {
         endwin();
         printf("Error Initializing colors.n");
         exit(1);
     }

     start_color();

     palette();

     Level(lev);

     while ((ch = getch()) != 'q')
     {
         Play(ch);
     }
     endwin();

     return 0;
}
