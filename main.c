#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wand/MagickWand.h>
#include <wand/magick_wand.h>
#include <sys/stat.h>
#include <sys/types.h>

/* To build use this

cc -o cutter main.c `pkg-config --cflags --libs MagickWand`

*/

static MagickWand *shared_wand;

void init_wand();
/* Filter types:
    Bessel, Catrom, Hanning, Mitchell, Sinc, Blackman, CubicGaussian, Hermite
    PointQuandratic, Triangle, Box, Lanczos
*/
void resize_image(char *input_name, char *output_name, const FilterTypes filter, int size);
void clean();

void generate_ios_images(char *input_name, char *output_name);
void generate_android_images(char *input_name, char *output_name);
void generate_win_images(char *input_name, char *output_name);

// iOS icon sizes
int ios_sizes[] = {167, 76, 152, 120, 180, 60, 87, 58, 29, 66, 44};
int android_sizes[] = {48, 72, 96, 144, 192, 512, 16, 24, 32, 64, 128};
int win_sizes[] = {170, 99, 71, 360, 210, 150, 106, 62, 44, 120, 70, 50, 58, 33, 24};


int main(int argc, char *argv[]) {

    if(argc < 3) {
        printf("Usage: cutter input output\n");
        return -1;
    }

    init_wand();

    generate_ios_images(argv[1], argv[2]);
    generate_android_images(argv[1], argv[2]);
    generate_win_images(argv[1], argv[2]);
/*
    resize_image("lena.jpg", "Bessel.png", BesselFilter);
    resize_image("lena.jpg", "Catrom.png", CatromFilter );
    resize_image("lena.jpg", "Hanning.png", HanningFilter );
    resize_image("lena.jpg", "Mitchell.png", MitchellFilter );
    resize_image("lena.jpg", "Sinc.png", SincFilter );
    resize_image("lena.jpg", "Blackman.png", BlackmanFilter);
    resize_image("lena.jpg", "CubicGaussian.png", CubicFilter );
    resize_image("lena.jpg", "Hermite.png", HermiteFilter );
    resize_image("lena.jpg", "Quadratic.png", QuadraticFilter);
    resize_image("lena.jpg", "Triangle.png", TriangleFilter );
    resize_image("lena.jpg", "Box.png", BoxFilter );
    resize_image("lena.jpg", "Lanczos.png", LanczosFilter );
    resize_image("lena.jpg", "Spline.png", SplineFilter );
    resize_image("lena.jpg", "Bartlett.png", BartlettFilter );
    resize_image("lena.jpg", "Jinc.png", JincFilter );
    resize_image("lena.jpg", "Gaussian.png", GaussianFilter );
*/

    clean();
    return 0;
}

void generate_ios_images(char *input_name, char *output_name) {
    int count = 11;

    mkdir("iOS", 0755);

    for (int i = 0; i < count; i++) {
        int size = ios_sizes[i];
	char *fixed_name = calloc(512, sizeof(char));
	sprintf(fixed_name,"%s%s%d%s", "iOS/", output_name, ios_sizes[i], ".png");
	resize_image(input_name, fixed_name, SincFilter, size);
	free(fixed_name);
    }   
}

void generate_android_images(char *input_name, char *output_name) {
   
    int count = 11;
    mkdir("Android", 0755);

    for (int i = 0; i < count; i++) {
        int size = android_sizes[i];
	char *fixed_name = calloc(512, sizeof(char));
	sprintf(fixed_name,"%s%s%d%s", "Android/", output_name, android_sizes[i], ".png");
        resize_image(input_name, fixed_name, SincFilter, size);
	free(fixed_name);
    }   
}

void generate_win_images(char *input_name, char *output_name) {
   
    int count = 15;
    mkdir("WinPhone", 0755);

    for (int i = 0; i < count; i++) {
        int size = win_sizes[i];
	char *fixed_name = calloc(512, sizeof(char));
	sprintf(fixed_name,"%s%s%d%s", "WinPhone/", output_name, win_sizes[i], ".png");
        resize_image(input_name, fixed_name, SincFilter, size);
	free(fixed_name);
    }   
}

void init_wand() {
    MagickWandGenesis();
    
}

void resize_image(char *input_name, char *output_name, const FilterTypes filter, int size) {
    
    int width = size;
    int height = size;
    
    shared_wand = NewMagickWand();
    MagickReadImage(shared_wand, input_name);
    MagickResizeImage(shared_wand, width, height, filter, 1);
    MagickSetImageFormat(shared_wand, "PNG");
    MagickWriteImage(shared_wand, output_name);
}

void clean() {
    if (shared_wand) {
        DestroyMagickWand(shared_wand);
    }

    MagickWandTerminus();
}
