#include "GedcomFile.h"

int main(int argc, char* argv[])
{
   std::string temp = "..\\data\\proj02test.ged";
   // Accepts an absolute path to a file...
   if (1 < argc)
   {
      temp = argv[1];
   }

   Utils::Gedcom::GedcomFile my_file(temp);//"..\\data\\proj02test.ged");
   my_file.readLines();
   my_file.print();
   my_file.close();

   
   return 0;
}