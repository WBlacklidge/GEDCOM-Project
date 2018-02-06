/*
* @file
* @author William Blacklidge
* @date 01/30/2018
* @brief This is the main point of execution.
*/
#include "GedcomFile.h"

/** The main point of execution. 
* @param argc The number of argumenets. 
* @param argv An array of strings (char*) that is argc-sized. 
* @return This always returns 0. */
int main(int argc, char* argv[])
{
   // TODO: I haven't tested passing in a command line value, so the string is hardcoded.
   std::string ged_file = "..\\data\\Family-2-6-Feb-2018-553.ged"; //"..\\data\\proj02test.ged";
   
   // Accepts an absolute path to a file...
   if (1 < argc)
   {
      ged_file = argv[1];
   }

   // Using the file path, create a GedcomFile object.
   Utils::Gedcom::GedcomFile my_file(ged_file);

   // Read each line from the GedComFile and save it.
   my_file.readLines();

   // Will print the before and after of parsing the GEDCOM file.
   // my_file.print();

   // Will print all of the individuals in the GEDCOM file in descending order based on ID.
   my_file.printIndividualsInDescendingId();

   // Will print all of the families in the GEDCOM file in descending order based on ID.
   my_file.printFamiliesInDescendingId();

   // Done.
   my_file.close();

   return 0;
}