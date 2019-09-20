#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct rgb
{
    float r,g,b;
} rgb;


void saveBMP(char* path, int w, int h, int dpi, rgb* imageBuffer)
{
    FILE* img;
    int img_size = w*h;
    int file_size = 54+4*img_size;
    int ppm = dpi*39.375;


    struct BMP_file_header
    {
        unsigned char   BMP_type[2];// 2 bytes
        int             file_size;  // 4 bytes
        short           reserved1;  // 2 bytes
        short           reserved2;  // 2 bytes
        unsigned int    offset_bits;// 4 byte
                                    //---TOTAL: 14 bytes
    } fh;

    struct BMP_image_header
    {
        unsigned int    header_size;    // 4 bytes
        unsigned int    w;              // 4 bytes
        unsigned int    h;              // 4 bytes
        short int       planes;         // 2 bytes
        short int       bit_count;      // 2 bytes
        unsigned int    compression;    // 4 bytes
        unsigned int    img_size;       // 4 bytes
        unsigned int    ppm_x;          // 4 bytes
        unsigned int    ppm_y;          // 4 bytes
        unsigned int    clr_used;       // 4 bytes
        unsigned int    clr_important;  // 4 bytes
                                        //---TOTAL: 40 bytes
    } ih;

    memcpy(&fh.BMP_type, "BM", 2);
    fh.file_size        = file_size;
    fh.reserved1        = 0;
    fh.reserved2        = 0;
    fh.offset_bits      = 0;

    ih.header_size      = sizeof(ih);
    ih.w                = w;
    ih.h                = h;
    ih.planes           = 1;
    ih.bit_count        = 24;
    ih.compression      = 0;
    ih.img_size         = img_size;
    ih.ppm_x            = ppm;
    ih.ppm_y            = ppm;
    ih.clr_used         = 0;
    ih.clr_important    = 0;

    img = fopen(path, "wb");
    fwrite(&fh, 1, 14, img);
    fwrite(&ih, 1, sizeof(ih), img);

    for(int i=0; i<img_size; i++)
    {
        rgb pixel = imageBuffer[i];
        float r = pixel.r;
        float g = pixel.g;
        float b = pixel.b;
        unsigned char color[3] = {b, g, r};
        fwrite(color, 1, sizeof(color), img);



    }

    fclose(img);

}



int isInMandebrotSet(float a, float b)
{
    float x,y;
    float xold = 0;
    float yold = 0;
    
    for(int i=0;i<255;i++)
    {
        x = xold*xold-yold*yold+a;
        y = 2*xold*yold+b;
        xold = x;
        yold = y;

        if(x*x+y*y>10) return i;
    }

    return 255;
}






int main(void)
{


    int width  = 2000,
        height = 2000,
        dpi = 96;

    rgb* pixels = malloc(width * height * sizeof(rgb));

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int a = y * width + x;
            float xx = 3*(float)x/(float)width-1.5;
            float yy = 3*(float)y/(float)height-1.5;

            int c= isInMandebrotSet(xx,yy);
            
                pixels[a].r = c;
                pixels[a].g = c*c%256;
                pixels[a].b = c;
            
            
            /*
            if (isInMandebrotSet(xx,yy)) {
                
                pixels[a].r = 255;
                pixels[a].g = 255;
                pixels[a].b = 5;
            } else {
                pixels[a].r = 55;
                pixels[a].g = 55;
                pixels[a].b = 55;
            }
            */
        }
    }

    saveBMP("black_border.bmp", width, height, dpi, pixels);

    return 0;
}


