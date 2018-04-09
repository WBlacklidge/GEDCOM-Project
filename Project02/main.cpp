/*
* @file
* @author William Blacklidge and Sreedhar Thirumanadham
* @date 01/30/2018
* @brief This is the main point of execution.
*/
#include "GedcomFile.h"

#include <iostream>

/** The main point of execution. 
* @param argc The number of argumenets. 
* @param argv An array of strings (char*) that is argc-sized. 
* @return This always returns 0. */
int main(int argc, char* argv[])
{
   const std::string test_file_names[]
   {
      "data\\divorce_before_death_test.ged",
      "data\\invalid_dates_test.ged",
      "data\\marriage_before_divorce_test.ged",
      "data\\NoUpcomingBirthdays.ged",
      "data\\over_150_birth_death_test.ged",
      "data\\print_error_test.ged",
      "data\\recentBirthdayntoday.ged",
      "data\\recentBirthdays.ged",
      "data\\recentDeaths.ged",
      "data\\same_name_birth_test.ged",
      "data\\unique_id_test.ged",
      "data\\UpcomingBirthdayisToday.ged",
      "data\\UpcomingBirthdays.ged",
      "data\\UpcomingBirthdaySameMonth.ged",
      "data\\UpcomingBirthdaySameYear.ged",
      "data\\MarriageAgeOver14.ged"
   };

   for (unsigned int i = 0; i < 16; ++i)
   {
      // TODO: I haven't tested passing in a command line value, so the string is hardcoded.
      std::string ged_file = test_file_names[i];

      //"\\data\\proj02test.ged"; 
      // "\\data\\unique_id_test.ged";

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
       //my_file.printfile();

     // Will print all of the individuals in the GEDCOM file in descending order based on ID.
      my_file.printIndividualsInDescendingId();

      // Put some space between the two prints, easier on the eyes.
      std::cout << "\n\n\n";

      // Will print all of the families in the GEDCOM file in descending order based on ID.
      my_file.printFamiliesInDescendingId();

      // Put some space between the two prints, easier on the eyes.
      std::cout << "\n\n\n";

      // Will print all of the individuals in the GEDCOM file upcoming birthdays.
      my_file.printIndividualsUpcomingBirthdays();


      // Put some space between the two prints, easier on the eyes.
      std::cout << "\n\n\n";

      // Will print all of the individuals in the GEDCOM file upcoming Annivarsaries.
      my_file.printIndividualsUpcomingAnnivarsaries();

      // Put some space between the two prints, easier on the eyes.
      std::cout << "\n\n\n";

      // Will print all of the individuals in the GEDCOM file Deceased.
      my_file.printIndividualsDeceased();

      // Put some space between the two prints, easier on the eyes.
      std::cout << "\n\n\n";

      // Will print all of the individuals recently born.
      my_file.printIndividualsBornRecently();

      // Put some space between the two prints, easier on the eyes.
      std::cout << "\n\n\n";

      // Will print all of the individuals recently Died.
      my_file.printIndividualsRecentDeaths();

      // Done.
      my_file.close();
   }

   return 0;
}