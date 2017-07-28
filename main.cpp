#include "application.h"
#include "wt-x11-driver.h"
#include "pushbutton.h"
#include "wtlabel.h"
#include "listview.h"
#include "wttextedit.h"

#include "stdio.h"

#include <string>
#include <string.h>

using namespace Wt;

/*!
    Main function of the demo application that demonstrates
    WindowToolkit usage.
*/

int main(int argc, char * argv[])
{
    // Create application object. Should be created before any other
    // object that requires events
    Application application;

    // Create main application window. Constructor can take size as parameter
    WtDriverWidget window(800,600);

    // Create and setup PushButton widget. Parent widget is specified in the
    // constructor. If parent container is not specified, a standalone window
    // will be created
    PushButton pb(&window);
    pb.setSize(150, 80);
    pb.setPosition((window.width()-pb.width())/2,
                   (window.height()-pb.height())/2);
    pb.setText("Button");

    // Create and setup WtLabel widget
    WtLabel label(&window);
    label.setSize(150, 50);
    label.setPosition(10, 10);
    label.setText("Hello!");

    // Bind PushButton \a click event to the Label \a setText function
    // Once the button is clicked, the label text will be changed
    pb.bindEvent("click").to([&label]{label.setText("Button");});

    // Create and setup ListView widget
    ListView lw(&window);
    lw.setSize(200, 200);
    lw.setPosition(window.width()-lw.width()-10, 20);
    lw.setSelectedIndex(1);
    lw.setData({"1","2","3","4","5","6","7","8","9"});

    // Create and setup WtTextEdit widget
    WtTextEdit textEdit(&window);
    textEdit.setSize(300, 300);
    textEdit.setPosition(0, window.height()/2);
    textEdit.setText("A");

    // Show method is mandatory to call on the root most window
    // which in turn causes all the child widgets to become visible
    window.show();

    // Runs the application event loop and starts processing
    // all user events. This is a blocking all that will stay here
    // until the last application window is closed
    application.run();

    return 0;
}
