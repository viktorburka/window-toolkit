#include "wt-x11-driver.h"
#include "paintbrush.h"
#include "wtimage.h"
#include "rect.h"
#include "string.h"
#include "wt.h"

int w = 100;
int h = 100;
char* data = 0;

/*!
    WtDriverWidget is a class for testing WT widgets. It uses
    different WT classes to demonstrate how to use them. It is
    created as a top level window.
*/

/*!
    WtDriverWidget constructor.
*/
WtDriverWidget::WtDriverWidget(int width, int height)
    : Widget(width, height)
{
}

/*!
    Draws WtDriverWidget. Implements drawing of a PNG image by
    loading it from the disk drive first.
*/
void WtDriverWidget::drawEvent(int x, int y, int width, int height)
{
    PaintBrush pb(this);

    WtImage image("test.png");

    int xc = this->width() - image.width();
    int yc = this->height() - image.height();

    pb.drawImage(image, Rect(xc, yc, image.width(), image.height()));

//    WtImage generatedImage(w, h, data);
//    pb.drawImage(generatedImage, Rect(0, this->height()-generatedImage.height(),
//                                      generatedImage.width(), generatedImage.height()));
}
