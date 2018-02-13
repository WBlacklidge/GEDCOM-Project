#pragma once
/*
* @file
* @author William Blacklidge
* @date 02/11/2018
* @brief This file will have utility functions for reporting errors.
*/
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
namespace Utils
{
   namespace Gedcom
   {
      /** This is a static function that can be used anywhere in the code 
      * to print an error and its relavent information. 
      * @param errorInfo The string containing the error information. 
      * @param functionName A string containing the name of the function.  This
      * must be provided in the calling function so a default can't be provided here.
      * @param lineNumber The lineNumber that the error was reported.
      * @fileName The file where the error occured. */
      static std::string reportError(
         std::string errorInfo,
         std::string functionName,
         int lineNumber = __LINE__,
         std::string fileName = __FILE__,
         std::string date = __DATE__,
         std::string time = __TIME__,
         bool toFile = true)
      {
         std::ostringstream str;
         str << "***An error occured************************************************" << std::endl;
         str << "File: " << fileName << std::endl;
         str << "Function: " << functionName << std::endl;
         str << "Line#:" << lineNumber << std::endl;
         str << "What: " << errorInfo << std::endl;
         str << "When: " << date << " " << time << std::endl;
         str << "******************************************************************" << std::endl;

         // write to a file.
         if (toFile)
         {
            std::ofstream my_file;
            my_file.open("C:/log/log.txt");
            my_file << str.str();
            my_file.close();
         }

         std::cout << str.str() << std::endl;

         return str.str();
      }
   }
}
