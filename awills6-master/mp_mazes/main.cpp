#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze* maze = new SquareMaze();
    maze->makeMaze(33,33);
    maze->drawCreativeMaze();
    delete maze;
    return 0;
}
