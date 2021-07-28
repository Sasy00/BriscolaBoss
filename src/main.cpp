#include <iostream>
#include "GameManager.h"
int main(int argc, char **argv)
{
    std::cout << "Hello World!" << std::endl;
    GameManager manager(2);
    manager.init();
    
    
    while(!manager.update())
        ;
    return 0;
}