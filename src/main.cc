/*
0 = basic console
1 = NOT IMPLEMENTED - non interactive (single command and skidaddle)
2 = NOT IMPLEMENTED - interactive cli
3 = NOT IMPLEMENTED - repl??? maybe?????

*/
#define MODE 0

//
//
//
//
//

#if MODE == 0

    #include <iostream>

    #include "licanc/include/licanc.hh"

    int main() {
        std::cout << "Hello world, this is Lican!\n";
        
        return 0;
    }

#elif MODE == 1
constexpr int test = 0;
#elif MODE == 2
constexpr int test = 0;
#elif MODE == 3
constexpr int test = 0;

#endif