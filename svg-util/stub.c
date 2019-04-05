// Automatically generated from svg
//
// Copyright (c) 2019, Jonathan Cyriax Brast, Adrian "vifino" Pistol <vifino@tty.sh>, "x41"
//
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.


#include <types.h>
#include <matrix.h>
#include <timers.h>
#include <random.h>
#include <stddef.h>
#include <stdlib.h>

typedef char bool;
#define true 1
#define false 0

struct polygon{
    int numpoints;
    int startpoint;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} polygon;


// DATA SECTION BEGIN
// manually written triangles.
#define NUMPOINTS 9
float pointcloud[NUMPOINTS*2] = {
    // x, y
    .0f,.0f,
    .0f,.1f,
    .07f,.05f,
    .1f,.0f,
    .1f,.1f,
    .03f,.05f,
    .0f,.1f,
    .1f,.1f,
    .05f,.03f
    //0.5f, 0.3f,
    //0.8f, 0.8f,
	//0.3f, 0.8f,
    //0.11f, 0.3f,
    //0.8f, 0.8f,
	//0.3f, 0.8f
};
#define NUMPOLYS 3
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
    .green = 255,
    .blue = 0,
    },{
	.numpoints = 3,
    .startpoint = 6,
    .red = 0,
    .green = 0,
    .blue = 255,
    }};
// DATA SECTION END

// SETTINGS SECTION BEGIN
static bool USE_MARGIN = true;
static float MARGIN_SIZE = 1.05;
static unsigned char bg_red = 255;
static unsigned char bg_green = 255;
static unsigned char bg_blue = 0;
// SETTINGS SECTION END

static int modno;

#define AA_NUM 8
static float aa_point_offsets[AA_NUM][2] = {
    {0.45f,0.4},
    {-0.4f,0.45},
    {-0.45f,-0.4},
    {0.4f,-0.45},
    {0.2f,0.05},
    {-0.05f,0.2},
    {-0.2f,-0.05},
    {0.05f,-0.2}
};



#define _max(a,b) (a) > (b) ? (a) : (b)

int draw(int argc, char* argv[]) {
    matrix_clear();
    int mx = matrix_getx();
    int my = matrix_gety();
    float max_x = pointcloud[0];
    float max_y = pointcloud[1];
    float min_x = pointcloud[0];
    float min_y = pointcloud[1];
    for (int i = 0; i < NUMPOINTS; i++){
        float x = pointcloud[i*2];
        float y = pointcloud[i*2+1];
        if (x > max_x) max_x = x;
        if (y > max_y) max_y = y;
        if (x <  min_x) min_x = x;
        if (y < min_y) min_y = y;
    }
    float scale = _max((max_x-min_x)/mx,(max_y-min_y)/my);
    if (USE_MARGIN) scale *= MARGIN_SIZE;
    float xoffset = (max_x + min_x)/2; 
    float yoffset = (max_y + min_y)/2; 

    for (int x = 0; x < mx;x++){
        for (int y = 0; y < my;y++){
            float xp = (float) x;
            xp -= mx/2; xp *= scale; xp += xoffset;
            float yp = (float) y;
            yp -= my/2; yp *= scale; yp += yoffset;
            unsigned char aa_r[AA_NUM];
            unsigned char aa_g[AA_NUM];
            unsigned char aa_b[AA_NUM];
            for (int i_aa=0;i_aa < AA_NUM; i_aa++){
                float x0 = xp + aa_point_offsets[i_aa][0]*scale;
                float y0 = yp + aa_point_offsets[i_aa][1]*scale;
                aa_r[i_aa] = bg_red;
                aa_g[i_aa] = bg_green;
                aa_b[i_aa] = bg_blue;
                for (int i_poly = 0; i_poly < NUMPOLYS; i_poly++){
                    struct polygon poly = polys[i_poly];
                    int counter = 0;
                    int start = poly.startpoint*2;
                    int end = poly.startpoint*2 + poly.numpoints*2;
                    for (int i_point = start; i_point < end; i_point+=2){
                        int idx = i_point;
                        float x1 = pointcloud[idx];
                        if (++idx >= end) idx = start;
                        float y1 = pointcloud[idx];
                        if (++idx >= end) idx = start;
                        float x2 = pointcloud[idx];
                        if (++idx >= end) idx = start;
                        float y2 = pointcloud[idx];
                        if ((x0 < x1 && x0 < x2) || (x0 > x1 && x0 > x2)) continue;
                        if ((x1-x0)*(x2-x0)<0){
                            if ((y1 + ((x0 - x1) * ((y2-y1)/(x2-x1)))) > y0 ) {
                                counter++;
                            }
                        }
                    }
                    if ((counter%2)){
                        aa_r[i_aa] = poly.red;
                        aa_g[i_aa] = poly.green;
                        aa_b[i_aa] = poly.blue;
                    }
                }
            }
            int red=0,green=0,blue=0;
            for (int i_aa=0;i_aa < AA_NUM; i_aa++){
                // TODO: gamma correction
                red += aa_r[i_aa];
                green += aa_g[i_aa];
                blue += aa_b[i_aa];
            }
            red /= AA_NUM;
            green /= AA_NUM;
            blue /= AA_NUM;
            matrix_set(x,y,RGB(red,green,blue));
        }
    }
    matrix_render();
	timer_add(udate()+30000000, modno, 0, NULL);
    return 0;
}

int init(int moduleno, char* argstr) {
    modno = moduleno;
	return 0;
}


void reset(void) {
    matrix_clear();
	// Nothing?
}

int deinit(void) {
	return 0;
}
