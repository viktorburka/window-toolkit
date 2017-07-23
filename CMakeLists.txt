cmake_minimum_required (VERSION 2.6)

link_directories(
    /home/victor/Dev/freetype-2.7.1/lib
)

project (wt-x11-driver)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(wt-x11-driver
               main.cpp
               application.cpp
               application.h
               platforms/xlib/window-x11.cpp
               platforms/xlib/window-x11.h
               platforms/xlib/application-x11.cpp
               platforms/xlib/application-x11.h
               platforms/xlib/image-x11.cpp
               platforms/xlib/image-x11.h
               platforms/xlib/paintbrush-x11.cpp
               platforms/xlib/paintbrush-x11.h
               interfaces/platformapplication.h
               interfaces/window.h
               interfaces/platformimage.h
               interfaces/platformpaintbrush.h
               interfaces/imageformat.h
               imageformats/image-png.cpp
               imageformats/image-png.h
               imageformats/imageformatfactory.cpp
               imageformats/imageformatfactory.h
               verification.cpp
               verification.h
               display-x11.cpp
               display-x11.h
               paintbrush.cpp
               paintbrush.h
               wt-x11-driver.cpp
               wt-x11-driver.h
               pushbutton.cpp
               pushbutton.h
               wtlabel.cpp
               wtlabel.h
               widget.cpp
               widget.h
               bindevent.cpp
               bindevent.h
               listview.cpp
               listview.h
               rect.cpp
               rect.h
               wt.cpp
               wt.h
               wttextedit.cpp
               wttextedit.h
               wtimage.cpp
               wtimage.h
               wtcolor.cpp
               wtcolor.h
               types.h)

target_link_libraries(wt-x11-driver X11 freetype png)
add_definitions(-DGP_X11)
#add_definitions(-DVISUAL_DEBUG)

target_include_directories(
    wt-x11-driver PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/platforms/xlib
  ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
  ${CMAKE_CURRENT_SOURCE_DIR}/imageformats
  /home/victor/Dev/freetype-2.7.1/include
  /home/victor/Dev/freetype-2.7.1/include/freetype2
#  /home/victor/Dev/libpng-1.6.29/include
)
