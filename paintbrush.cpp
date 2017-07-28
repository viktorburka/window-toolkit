#include "paintbrush.h"
#include "widget.h"
#include "rect.h"
#include "wt.h"
#include "wtimage.h"
#include "platformimage.h"
#include "wtcolor.h"

#ifdef GP_X11
#include "paintbrush-x11.h"
#include "window-x11.h"
#endif

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

using namespace Wt;

/*!
    \class PaintBrush
    \inmodule Wt

    \brief The PaintBrush class implement platform independent drawing methods.

    \ingroup widgets

    PaintBrush provides a set of APIs to draw on a widgetsurface. It supports
    veriety of basic drawing methods such as \a drawRect, \a drawText,
    \a drawImage, etc.

    PaintBrush can only be uses in a widget's \a drawEvent function. The user
    should override that function in his own widget and instantiate PaintBrush
    there calling appropriate drawing methods.
*/

/*!
    Constructs PaintBrush instantiating appropriate platform dependent instance
    for drawing.
*/
PaintBrush::PaintBrush(Widget* widget)
    : m_surface(widget)
{
#ifdef GP_X11
    WindowX11* winX11 = static_cast<WindowX11*>(widget->m_platformWin.get());
    m_platformBrush = new PaintBrushX11(winX11);
#endif
}

/*!
    Draws rectangle with the outline color preset in \a setPaintColor method.
*/
void PaintBrush::drawRect(const Rect & rect)
{
    drawRect(rect.x(), rect.y(), rect.width(), rect.height());
}

/*!
    Draws rectangle with the outline color preset in \a setPaintColor method.
*/
void PaintBrush::drawRect(int x, int y, int width, int height)
{
    m_platformBrush->drawRect(x, y, width, height);
}

/*!
    Fills rectangle with the color preset in \a setPaintColor method.
*/
void PaintBrush::fillRect(const Rect & rect)
{
    fillRect(rect.x(), rect.y(), rect.width(), rect.height());
}

/*!
    Fills rectangle with the color preset in \a setPaintColor method.
*/
void PaintBrush::fillRect(int x, int y, int width, int height)
{
    int adjustedWidth = x + width >= m_surface->width() ? m_surface->width()-x : width;
    int adjustedHeight = y + height >= m_surface->height() ? m_surface->height()-y : height;

    m_platformBrush->fillRect(x, y, adjustedWidth, adjustedHeight);
}

/*!
    Sets outline or fill color for drawing primitives.
*/
void PaintBrush::setPaintColor(const std::string & colorName)
{
    m_platformBrush->setPaintColor(colorName);
}

/*!
    Draws text within \a rect boundary.
*/
void PaintBrush::drawText(const std::string & text, const Rect & rect)
{
    m_platformBrush->drawText(text, rect);
}

/*!
    Draws text with \a background color.
*/
void PaintBrush::drawText(const std::string & text, const WtColor & background)
{
    auto validate = [](FT_Error error,
                       const std::string & msg)
    {
        if (error != FT_Err_Ok) {
            WtPrint() << msg;
            exit(-1);
        }
    };

    const std::string fontFile = "Roboto-Regular.ttf";
    const int pointSize = 48;

    FT_Library library     = 0;
    FT_Face    face        = 0;
    FT_UInt    glyph_index = 0;
    FT_Error   error       = FT_Err_Ok;

    error = FT_Init_FreeType(&library);
    validate(error, "Error initializing FreeType library");

    error = FT_New_Face(library, fontFile.c_str(), 0, &face);
    validate(error, "Error creating font face");

    error = FT_Set_Char_Size(face, 0,
                             pointSize * 64,
                             m_surface->dpiX(),
                             m_surface->dpiY());
    validate(error, "Error setting font size");

    int x = 10;

    FT_BBox  bbox;
    FT_Glyph glyph;

    int maxHeight = 0;
    int maxBitmapTop = 0;

    for (int i = 0; i < text.size(); ++i) {

        glyph_index = FT_Get_Char_Index(face, text[i]);

        error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
        validate(error, "Error setting font size");

        error = FT_Get_Glyph(face->glyph, &glyph);
        validate(error, "Error getting glyph");

        FT_Glyph_Get_CBox(glyph, FT_GLYPH_BBOX_PIXELS, &bbox);

        maxHeight = std::max(int(bbox.yMax-bbox.yMin), maxHeight);
        maxBitmapTop = std::max(int(bbox.yMax), maxBitmapTop);

        FT_Done_Glyph(glyph);
    }

    int baselineY = maxHeight;

    for (int i = 0; i < text.size(); ++i) {

        glyph_index = FT_Get_Char_Index(face, text[i]);
        error = FT_Load_Glyph(face, glyph_index,
                              FT_LOAD_DEFAULT);
        validate(error, "Error setting font size");

        error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
        validate(error, "Error rendering glyph");

        int width  = face->glyph->bitmap.width;
        int height = face->glyph->bitmap.rows;

        unsigned char* buffer = face->glyph->bitmap.buffer;
        char* imgData = (char*)malloc(width*height*4);

        for (int i = 0; i < width*height; ++i) {
            char bgra[4]; bgra[0] = 0x00; bgra[1] = 0x00; bgra[2] = 0x00; bgra[3] = 0xFF;
            if (!*buffer) {
                memcpy(bgra, background.bgra(), 3);
            }
            ++buffer;
            memcpy(imgData + i*4, bgra, 4);
        }

        WtImage image(face->glyph->bitmap.width,
                      face->glyph->bitmap.rows,
                      imgData);
        drawImage(image, Rect(x, baselineY - face->glyph->bitmap_top,
                              image.width(), image.height()));

        x += (face->glyph->advance.x >> 6);

        free(imgData);
    }

    FT_Done_Face(face);
}

/*!
    Draws raster image.
*/
void PaintBrush::drawImage(const WtImage & image, const Rect & rect)
{
    m_platformBrush->drawImage(image, rect);
}
