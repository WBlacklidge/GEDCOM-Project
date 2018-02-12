/**
* @file
* @author  William Blacklidge
* @date    02/12/2018
* @brief   This is the main for google test implementation.
*/
#include "gtest/gtest.h"
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) 
{
   testing::InitGoogleTest(&argc, argv);

   int results = RUN_ALL_TESTS();
   return results;
}
