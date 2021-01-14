## Rendering the Animation

Animation rendering begins with the function [mainloop()](../main.cpp) when Glottie is compiled for Web Assembly. For all other cases rendering begins with the function [standaloneLoop()](../main.cpp).

The function *mainloop()* is used as the callback function for emscripten_set_main_loop().

Both *mainloop()* and *standaloneLoop()* calls [glDraw()](../gl/gl.cpp) perform the rendering.