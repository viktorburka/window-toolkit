#include "wt-x11-driver.h"
#include "paintbrush.h"
#include "wtimage.h"
#include "rect.h"
#include "string.h"

int w = 100;
int h = 100;
char* data = 0;


WtDriverWidget::WtDriverWidget(int width, int height)
    : Widget(width, height)
{
//    char* data = (char*)malloc(w*h*4);
//    int size = w*h*4;
//    for(int i=0; i<size; i+=4) {
//        //                    B     G     R     A
//        const char bgra[] = { 0x00, 0x00, 0xFF, 0x00 };
//        memcpy(data+i, bgra, 4);
//    }
}

void WtDriverWidget::drawEvent(int x, int y, int width, int height)
{
//    PaintBrush pb(this);

//    WtImage image("examples/test.png");

//    int xc = this->width() - image.width();
//    int yc = this->height() - image.height();

//    pb.drawImage(image, Rect(xc, yc, image.width(), image.height()));

//    WtImage generatedImage(w, h, data);
//    pb.drawImage(generatedImage, Rect(0, this->height()-generatedImage.height(),
//                                      generatedImage.width(), generatedImage.height()));
}
