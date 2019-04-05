
// MOCKUP STUFF BEGIN
int matrix_getx(){return 0;}
int matrix_gety(){return 0;}

//void matrix_set(int x, int y, RGB color) {};
// MOCKUP STUFF END

// DATA STUFF BEGIN
#define FIX_THIS 3
struct polygon{
    int numpoints;
    int startpoint;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} polygon;

// DATA STUFF END

// STUB STUFF BEGIN
// manually written triangles.
#define NUMPOINTS 6
float pointcloud[NUMPOINTS*2] = {
    // x, y
    0.5f, 0.3f,
    0.8f, 0.8f,
	0.3f, 0.8f,
    0.11f, 0.3f,
    0.8f, 0.8f,
	0.3f, 0.8f
};
#define NUMPOLYS 2
struct polygon polys[NUMPOLYS] = {{
	.numpoints = 3,
    .startpoint = 0,
    .red = 255,
    .green = 0,
    .blue = 0,
	},{
	.numpoints = 3,
    .startpoint = 3,
    .red = 0,
    .green = 0,
    .blue = 255,
    }};
// REPLACE ME
// STUB STUFF END

#define _sort2(a,b)\
    if (a>b) {float __tmp = a;a = b; b = __tmp;}

int draw(){
    int mx = matrix_getx();
    int my = matrix_gety();
    for (int x = 0; x < mx;x++){
        for (int y = 0; y < my;y++){
            float x0 = (float) x;
            float y0 = (float) y;
            for (int i_poly = 0; i_poly < NUMPOLYS; i_poly++){
                struct polygon poly = polys[i_poly];
                int counter = 0;
                // TODO: line iteration
                for (int i_point = poly.startpoint;i_point < poly.startpoint + poly.numpoints;i_point++){
                    float x1 = pointcloud[i_point];
                    float y1 = pointcloud[i_point];
                    float x2 = pointcloud[i_point];
                    float y2 = pointcloud[i_point];
                    // TODO: line iteration
                    _sort2(x1,x2);
                    _sort2(y1,y2);
                    if ((x1 < x0 && x0 < x2)||(y1 < y0 && y0 < y2)){ // x or y relevant
                        if ((x1 + (y0 - y1) * (x2-x1)/(y2-y1)) > x0) { // line cross above
                            counter ++;
                        }
                    }
                }
                if (counter&1){
                    //matrix_set(x,y,RGB(poly.red,poly.green,poly.blue));
                }
            }
        }
    }
}
