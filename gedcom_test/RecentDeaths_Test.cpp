/**
* @file
* @author  Sreedhar Thirumanadham
* @date    03/22/2018
* @brief   This will test Recent Deaths.
*
*/
#include "gtest/gtest.h"
#include "GedcomFile.h"
#include "ErrorReporting.h"

namespace
{
	/** Test fixture for error tests. */
	class RecentDeaths : public ::testing::Test
	{
	protected:
		/** Constructor. */
		RecentDeaths()
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

	TEST_F(RecentDeaths, RecentDeaths_Test)
	{
		std::string ged_file = "data\\RecentDeaths.ged";
		// Using the file path, create a GedcomFile object.
		Utils::Gedcom::GedcomFile my_file(ged_file);

		// Read each line from the GedComFile and save it.
		my_file.readLines();

		// Will print the before and after of parsing the GEDCOM file.
		// my_file.print();

		// Put some space between the two prints, easier on the eyes.
		std::cout << "\n\n\n";

		// Will print all of the individuals in the GEDCOM file Recent Deaths.
		my_file.printIndividualsRecentDeaths();

		// Done.
		my_file.close();
	}
}