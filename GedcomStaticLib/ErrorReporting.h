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
      enum ObjectType {e_none, e_indv, e_fam, e_other};
      /** This is a static function that can be used anywhere in the code 
      * to print an error and its relavent information. 
      * @param errorInfo The string containing the error information. 
      * @param functionName A string containing the name of the function.  This
      * must be provided in the calling function so a default can't be provided here.
      * @param lineNumber The lineNumber that the error was reported.
      * @fileName The file where the error occured. */
      static std::string reportError(
         std::string testId,
         ObjectType objType,
         std::string errorInfo,
         int lineNum,
         std::string functionName,
         int lineNumber = __LINE__,
         std::string fileName = __FILE__,
         std::string date = __DATE__,
         std::string time = __TIME__,
         bool toFile = true)
      {
         std::ostringstream str;
         str << "\nERROR: ";

         switch (objType)
         {
         case ObjectType::e_indv:
            str << "INDIVIDUAL: ";
            break;
         case ObjectType::e_fam:
            str << "FAMILY: ";
            break;
         case ObjectType::e_other:
            str << "OTHER: ";
            break;
         case ObjectType::e_none:
            str << "UNKNOWN: ";
            break;
         }

         str << testId << ": " << lineNum << ": " << std::endl;

         str << "File: " << fileName << std::endl;
         str << "Function: " << functionName << std::endl;
         str << "Code Line#:" << lineNumber << std::endl;
         str << "What: " << errorInfo << std::endl;
         str << "When: " << date << " " << time << std::endl;

         // write to a file.
         if (toFile)
         {
            std::ofstream my_file;
            my_file.open("data/log.txt");
            my_file << str.str();
            my_file.close();
         }

         std::cout << str.str() << std::endl;

         return str.str();
      }
   }
}
