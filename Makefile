EMCC=emcc

all: TSP.cpp
	$(EMCC) -O3 -s WASM=1 -o graph.js -s EXTRA_EXPORTED_RUNTIME_METHODS='["getValue", "setValue, sizeOf"]' -s EXPORTED_FUNCTIONS="['_calloc', '_find_best']" -s EXPORT_ES6=1 -s MODULARIZE=1 -std=c++11 TSP.cpp
