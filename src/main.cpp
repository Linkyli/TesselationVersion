#pragma once

#include"TesselationPlane.h"
#include <stdio.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif
#define MPI 3.14159265358979323846 
using namespace std;

//static void glfw_error_callback(int error, const char* description){  fprintf(stderr, "Glfw Error %d: %s\n", error, description);}


int main() {

    Tesselation();
    
    return 0;

}
