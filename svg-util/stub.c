


struct point {
    float x;
    float y;
} point;

struct polygon{
    point * points;
    int numpoints;
    RGB color;
    float min_x;
    float max_x;
    float min_y;
    float max_y;
} polygon;

polygon * polys;
int numpolys;

struct line {
    float x1;
    float x2;
    float y1;
    float y2;
} line;
/* REPLACE ME */

data * 

#define _sort2(a,b)\
    if (a>b) {float __tmp = a;a = b; b = __tmp;}

int draw(){
    int mx = matrix_getx();
    int my = matrix_gety();
    for (int x = 0; x < mx;x++){
        for (int y = 0; y < my;y++){
            for (line l = lines/*TODO:LINES*/){
                float x1 = l.x1;
                float x2 = l.x2;
                float y1 = l.y1;
                float y2 = l.y2;
                _sort2(x1,x2);
                _sort2(y1,y2);
                float x0 = (float) x;
                float y0 = (float) y;
                if ((x1 < x0 && x0 < x2)||(y1 < y0 && y0 < y2)){ // x or y relevant
                    if ((x1 + (y0 - y1) * (x2-x1)/(y2-y1)) > x0) { // line cross above

                    }
                }
            }
        }
    }
}
