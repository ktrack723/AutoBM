/*
    Winter 2021
    Automate your work assignment
    Written by SeungGeon Kim, special thanks to Ricky.Cha

    << This project was started because the author was pissed off thanks to his company that threw him and his colleage some crazy workload >>

    ~ External libraries used : LibXL (Paid version)
    ~ Build instructions : Just hit build, then make sure to have the required dlls together with the final executable. 
        This is currently set as a post-build event.
    ~ Any inquiries about the code can be forwarded either to keithrek@hanmail.net, or straight to the author, who should be working at 3F, JM building.

    Filename : AutoBM.cpp
    Edited : 2021-11-27
*/

#include "ConsoleManager.h"
#include "XLDataWrapper.h"



int main()
{
    CONSOLE.SetupLocal();

    XL_DW.ScanXLSX(L"itemtable.xlsx");

    return 0;
}