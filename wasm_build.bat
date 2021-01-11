emcc main.cpp -std=c++17 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s EXPORTED_FUNCTIONS="['_loadJson', '_main']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -s WASM=1 -s USE_SDL=2 -O1 -s ASSERTIONS=1 -s SAFE_HEAP=1 -fsanitize=undefined -s ALLOW_MEMORY_GROWTH=1 -o player.js 

copy /Y player.js www
copy /Y player.wasm www

