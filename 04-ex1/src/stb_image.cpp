#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"



/* 
 * why this file:
 *
 * the creator of stb_image.h packed both the blueprint and the definitions within a single file. 
 * They wrapped all the heavy image-processing code inside a special conditional gate that looks like
 *
 * #ifdef STB_IMAGE_IMPLEMENTATION
 * .... "stb_image.h code"
 * ..
 * #endif
 *
 * When created this file `stb_image.cpp`, the compiler reads 
 * #define STB_... and #include "stb_image.h"
 * 
 * 1st line creates a temporary keyword flag in the compiler's brain...
 *
 * 2nd line The compiler opens de header. it sees the gate #ifdef STB_IMAGE_IMPLEMENTATION.
 * Because it "flipped that switch on" the line above, the gate opens, and the compiler processes
 * all the raw code right inside `stb_image.cpp` file.
 *
 * by making this file with the #define, the heavy code is compiled only once in its safe corner.
 * And `main.cpp` can then freely link to it without casuing clutter.
 * 
 * */
