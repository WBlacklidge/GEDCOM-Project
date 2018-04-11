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
	  "data\\unique_id_test.ged",
      "data\\over_150_birth_death_test.ged",
      "data\\print_error_test.ged",
      "data\\MultipleBirths.ged",
      "data\\recentBirthdays.ged",
      "data\\recentDeaths.ged",
      "data\\same_name_birth_test.ged",
	  "data\\NoUpcomingBirthdays.ged",
      "data\\UpcomingBirthdayisToday.ged",
      "data\\UpcomingBirthdays.ged",
      "data\\UpcomingBirthdaySameMonth.ged",
      "data\\UpcomingBirthdaySameYear.ged",
      "data\\MarriageAgeOver14.ged",
      "data\\parents_not_too_old_test.ged",
	  "data\\CorrectGender.ged",
	  "data\\LargeAgeDiff.ged",
	  "data\\Family-2-6-Feb-2018-553.ged"
   };

   for (unsigned int i = 0; i < 20; ++i)
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



	   /* // TODO: I haven't tested passing in a command line value, so the string is hardcoded.
		 std::string ged_file = "data\\LargeAgeDiff.ged";

		 //"\\data\\proj02test.ged";
		 // "\\data\\unique_id_test.ged";

		 // Accepts an absolute path to a file...
		 if (1 < argc)
		 {
			 ged_file = argv[1];
		 }*/

		 // Using the file path, create a GedcomFile object.
	   Utils::Gedcom::GedcomFile my_file(ged_file);



	   switch (i)
	   {
	
	   case 0:
	   case 1:
	   case 2:
	   case 3:
	   case 4:
	   case 5:
	   case 6:
	   case 9:
	   case 15:
	   case 16:

		   // Read each line from the GedComFile and save it.
		   my_file.readLines();
		   // Will print the before and after of parsing the GEDCOM file.
		   //my_file.printfile();
		   
		   break;

	   case 10:
	   case 11:
	   case 12:
	   case 13:
	   case 14:
	  

		   // Read each line from the GedComFile and save it.
		   my_file.readLines();
		   // Will print the before and after of parsing the GEDCOM file.
		   //my_file.printfile();

			// Put some space between the two prints, easier on the eyes.
			 std::cout << "\n\n\n";

			// Will print all of the individuals in the GEDCOM file upcoming birthdays.
			 my_file.printIndividualsUpcomingBirthdays();
			 
		   break;

	   case 7:
	  
		   // Read each line from the GedComFile and save it.
		   my_file.readLines();
		   // Will print the before and after of parsing the GEDCOM file.
		   //my_file.printfile();

		   // Put some space between the two prints, easier on the eyes.
		   std::cout << "\n\n\n";

		   // Will print all of the individuals recently born.
		   my_file.printIndividualsBornRecently();

		   break;

	   case 8:

		   // Read each line from the GedComFile and save it.
		   my_file.readLines();
		   // Will print the before and after of parsing the GEDCOM file.
		   //my_file.printfile();

		   // Put some space between the two prints, easier on the eyes.
		   std::cout << "\n\n\n";

		   // Will print all of the individuals recently Died.
		   my_file.printIndividualsRecentDeaths();

		   break;

	   case 17:

		   // Read each line from the GedComFile and save it.
		   my_file.readLines();
		   // Will print the before and after of parsing the GEDCOM file.
		   //my_file.printfile();

		   // Put some space between the two prints, easier on the eyes.
		   std::cout << "\n\n\n";

		   // Will print all of the Correct gender roles .
		   my_file.printcorrectgenderrole();

		   break;

	   case 18:

		   // Read each line from the GedComFile and save it.
		   my_file.readLines();
		   // Will print the before and after of parsing the GEDCOM file.
		   //my_file.printfile();

		   // Put some space between the two prints, easier on the eyes.
		   std::cout << "\n\n\n";

		   // Will print all of the Large Age Diff.
		   my_file.printFamiliesLargeAgeDiff();

		   break;

	   case 19:

		   // Read each line from the GedComFile and save it.
		   my_file.readLines();
		   // Will print the before and after of parsing the GEDCOM file.
		   //my_file.printfile();

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

		   // Will print all of the individuals in the GEDCOM file in descending order based on ID.
		   my_file.printIndividualsInDescendingId();

		   // Put some space between the two prints, easier on the eyes.
		   std::cout << "\n\n\n";

		   // Will print all of the families in the GEDCOM file in descending order based on ID.
		   my_file.printFamiliesInDescendingId();

		   break;

	   default:

		   break;

	   }


	   // Done.
	   my_file.close();

   }

   return 0;
}