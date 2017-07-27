#include "wt-x11-driver.h"
#include "paintbrush.h"
#include "wtimage.h"
#include "rect.h"
#include "string.h"
#include "wt.h"

int w = 100;
int h = 100;
char* data = 0;


WtDriverWidget::WtDriverWidget(int width, int height)
    : Widget(width, height)
{
}

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
