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
      void reportError(
         std::ostringstream& str,
         std::string errorInfo,
         std::string functionName,
         int lineNumber = __LINE__,
         std::string fileName = __FILE__,
         std::string date = __DATE__,
         std::string time = __TIME__)
      {
         str << "***An error occured************************************************" << std::endl;
         str << "File: " << fileName << std::endl;
         str << "Function: " << functionName << std::endl;
         str << "Line#:" << lineNumber << std::endl;
         str << "What: " << errorInfo << std::endl;
         str << "When: " << date << " " << time << std::endl;
         str << "******************************************************************" << std::endl;

         std::cout << str.str() << std::endl;
      }
   }
}
