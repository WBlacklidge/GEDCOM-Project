/**
* @file
* @author  Sreedhar Thirumanadham
* @date    03/12/2018
* @brief   This will test Recent Births.
*
*/
#include "gtest/gtest.h"
#include "GedcomFile.h"
#include "ErrorReporting.h"

namespace
{
	/** Test fixture for error tests. */
	class RecentBirths : public ::testing::Test
	{
	protected:
		/** Constructor. */
		RecentBirths()
		{
		}

		/** Set up the test fixture. This function gets called before every
		* TEST_F() test is run.
		*/
		virtual void SetUp()
		{
		}

		/** Tear down the test fixture. This function gets called after every
		* TEST_F() test is run.
		*/
		virtual void TearDown()
		{
		}
	};

	TEST_F(RecentBirths, RecentBirths_Test)
	{
		std::string ged_file = "data\\RecentBirthdays.ged";
		// Using the file path, create a GedcomFile object.
		Utils::Gedcom::GedcomFile my_file(ged_file);

		// Read each line from the GedComFile and save it.
		my_file.readLines();

		// Will print the before and after of parsing the GEDCOM file.
		// my_file.print();

		// Put some space between the two prints, easier on the eyes.
		std::cout << "\n\n\n";

		// Will print all of the individuals in the GEDCOM file Recent Births.
		my_file.printIndividualsBornRecently();

		// Done.
		my_file.close();
	}
}