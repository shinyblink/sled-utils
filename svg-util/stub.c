
// MOCKUP STUFF BEGIN
int matrix_getx(){return 0;}
int matrix_gety(){return 0;}

typedef int RGB;
// MOCKUP STUFF END


// DATA STUFF BEGIN
struct point {
    float x;
    float y;
} point;

#define FIX_THIS 3
struct polygon{
    struct point points[3];
    int numpoints;
    RGB color;
    float min_x;
    float max_x;
    float min_y;
    float max_y;
} polygon;

struct line {
    float x1;
    float x2;
    float y1;
    float y2;
} line;
// DATA STUFF END

// manually written triangle.
int numpolys = 1;
struct polygon polys[1] = {{
								 .numpoints = 3,
								 .points = {
														{0.5f, 0.3f},
														{0.8f, 0.8f},
														{0.3f, 0.8f},
								 },
	}};

// STUB STUFF

#define _sort2(a,b)\
    if (a>b) {float __tmp = a;a = b; b = __tmp;}

int draw(){
    int mx = matrix_getx();
    int my = matrix_gety();
    for (int x = 0; x < mx;x++){
        for (int y = 0; y < my;y++){
            for (struct polygon poly = polys[0];;){
                for (struct point * pt = poly.points;;){
                    float x1 = pt->x;
                    float x2 = pt->x;
                    float y1 = pt->y;
                    float y2 = pt->y;
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
}
