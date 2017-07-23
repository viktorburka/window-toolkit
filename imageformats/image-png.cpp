#include "image-png.h"
#include "wt.h"

#include <png.h>


using namespace Wt;


ImagePng::ImagePng()
{
}

bool ImagePng::readImage(const std::string & filePath)
{
    png_structp png_ptr;
    png_infop info_ptr;
    png_byte color_type;
    png_byte bit_depth;
    int number_of_passes;
    png_bytep * row_pointers;

    unsigned char header[8];

    FILE *fp = fopen(filePath.c_str(), "rb");
    if (!fp) {
        WtPrint() << "Can't read file" << filePath;
        return false;
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        WtPrint() << "Incorrect PNG fomrat:" << filePath;
        return false;
    }

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        WtPrint() << "Error creating PNG read struct";
        return false;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        WtPrint() << "Error creating PNG info struct";
        return false;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        WtPrint() << "Error setting PNG jmpbuf";
        return false;
    }

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    m_width = png_get_image_width(png_ptr, info_ptr);
    m_height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr))) {
        WtPrint() << "Error reading PNG file";
        return false;
    }

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * m_height);
    for (int y=0; y<m_height; y++)
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

    png_read_image(png_ptr, row_pointers);

    fclose(fp);

    m_data = new char[sizeof(char)*m_width*m_height*4];
    for (int i = 0; i < m_height; ++i) {
        png_byte* row = row_pointers[i];
        char* p = m_data + i*m_width*4;
        memcpy(p, row, m_width*4);
        for (int j = 0; j < m_width; ++j) {
            char* rgba = p + j*4;
            m_rgbaFunc(rgba);
        }
    }

    for (int y=0; y<m_height; y++)
        free(row_pointers[y]);

    free(row_pointers);

    return true;
}

char* ImagePng::data() const
{
    return m_data;
}

int ImagePng::width() const
{
    return m_width;
}

int ImagePng::height() const
{
    return m_height;
}

void ImagePng::setRGBAFunc(char* (*func)(char*))
{
    m_rgbaFunc = func;
}
