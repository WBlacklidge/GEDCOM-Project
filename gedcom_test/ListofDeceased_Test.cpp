/**
* @file
* @author  Sreedhar Thirumanadham
* @date    03/12/2018
* @brief   This will test Deceased List.
*
*/
#include "gtest/gtest.h"
#include "GedcomFile.h"
#include "ErrorReporting.h"

namespace
{
	/** Test fixture for error tests. */
	class DeceasedList : public ::testing::Test
	{
	protected:
		/** Constructor. */
		DeceasedList()
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

	TEST_F(DeceasedList, DeceasedList_Test)
	{
		std::string ged_file = "data\\Family-2-6-Feb-2018-553.ged";
		// Using the file path, create a GedcomFile object.
		Utils::Gedcom::GedcomFile my_file(ged_file);

		// Read each line from the GedComFile and save it.
		my_file.readLines();

		// Will print the before and after of parsing the GEDCOM file.
		// my_file.print();

		// Put some space between the two prints, easier on the eyes.
		std::cout << "\n\n\n";

		// Will print all of the Deceased List individuals in the GEDCOM file 
		my_file.printIndividualsDeceased();

		// Done.
		my_file.close();
	}
}