#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <sstream>
#include"FileSystem.h"
#include"DiskDriver.h"

DiskDriver myDiskDriver;
SuperBlock mySuperBlock;

int main()
{
    //Initialize
    FileSystem fileSystem;
    fileSystem.Formatting();
    return 0;
}
