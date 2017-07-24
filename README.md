Window Toolkit is a C++ widgets toolkit.

As simple as the following picture may look representing just a few of widgets of Window Toolkit, it takes a lot of time and implementation to get that core setup and wiring to get something displayed on the screen.

<img src="https://github.com/viktorburka/window-toolkit/raw/master/doc/readme-md/window-toolkit.png" width="640" height="480">

Window Toolkit has a crossplatform nature given to it at the very beginning. Here are few key considerations that are put in it to provide cross platform support:

- It uses C++11 and STL and therefore is available on all those platforms that support it;
- It uses [CMake](https://cmake.org) as a build system providing therefore a large veriety of platforms it can be built for;
- It provides arcitecture that allows the user to extend it to new platforms by plugging new backends;
- It implements fonts rendering via low level [libfreetype](https://www.freetype.org) library that is available on a veriety of platforms as a core font rendering library

Currently it supports X11 backend as a rendering API on Linux via [Xlib](https://en.wikipedia.org/wiki/Xlib) C library which provides asyncronous API to render raster graphics.

I have Wayland backend in the works and right now its just proof of concept that renders some geometry on the screen. You can find that code in my other [playground](https://github.com/viktorburka/playground/tree/master) repository project [wt-wayland-backend](https://github.com/viktorburka/playground/tree/master/wt-wayland-backend). Although not very reach graphics displayed, it does all the setup and wiring necessary to get started.

Comparing to X11, [Wayland](https://wayland.freedesktop.org/) is a very cutting edge protocol that is based on rendering directly into the shared memory provided by the Wayland display server (currently I tested it on Weston) so that pixeles being rendered end up in the display server buffers right away. It is different from X11 where the user doesn't have direct access to the server buffers and the rendering happens via sending network commands that due to asyncronous nature and for optimization purposes don't get sent right away by default but accumulate in a package before they are transferred to the X11 display server by Xlib. This behaviour can be changed by forcing those commands to be sent right away but still it is a much slower method than rendering directly into the buffer. At the time I started writing Window Toolkit, Wayland was not very stable as well as there was a lack of documentation and examples on how it works. X11 from another side has proven to be reliable by decades its been in production as well has much better documentation available.

There is also another well known client library that implements X11 protocol called [xcb](https://xcb.freedesktop.org/) that has syncronous nature comparing to Xlib that is asyncronous. I have plans to get it working as well some time later.
