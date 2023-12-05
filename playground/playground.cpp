//
// Created by slinky on 12/2/23.
//

#include "Wad.h"

#include <iostream>

#include <regex>

int main() {
    Wad *myWad = Wad::loadWad("../sample1.wad");

    char buff [1024];
    int bytesRead = myWad->getContents("Gl/ad/os/cake.jpg", buff, 1024);

    std::cout << bytesRead << std::endl;

    return 0;
}