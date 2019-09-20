struct rgb
{
    float r,g,b;
}


void saveBMP(char* path, int w, int h, int dpi, rgb* imageBuffer)
{
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
        unsigned int    size_header;    // 4 bytes
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



}

