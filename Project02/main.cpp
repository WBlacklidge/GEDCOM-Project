#include "GedcomFile.h"

int main(int argc, char* argv[])
{
   std::string temp = "..\\data\\Family-2-6-Feb-2018-553.ged"; //"..\\data\\proj02test.ged";
   // Accepts an absolute path to a file...
   if (1 < argc)
   {
      temp = argv[1];
   }

   Utils::Gedcom::GedcomFile my_file(temp);
   my_file.readLines();
   // my_file.print();
   my_file.printIndividuals();
   //below is broken still.
   my_file.printFamilies();
   my_file.close();


   return 0;
}