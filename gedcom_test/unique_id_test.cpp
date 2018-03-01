/**
* @file
* @author  William Blacklidge
* @date    02/12/2018
* @brief   This will test error printing.
*
*/
#include "gtest/gtest.h"
#include "GedcomFile.h"
#include "ErrorReporting.h"

namespace
{
   /** Test fixture for error tests. */
   class UniqueIdTest : public ::testing::Test
   {
   protected:
      /** Constructor. */
      UniqueIdTest()
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

   TEST_F(UniqueIdTest, UniqueFamilyIndividual)
   {
      std::string ged_file = "data\\unique_id_test.ged";
      // Using the file path, create a GedcomFile object.
      Utils::Gedcom::GedcomFile my_file(ged_file);

      // Read each line from the GedComFile and save it.
      my_file.readLines();

      // Will print the before and after of parsing the GEDCOM file.
      // my_file.print();

      // Will print all of the individuals in the GEDCOM file in descending order based on ID.
      my_file.printIndividualsInDescendingId();

      // Put some space between the two prints, easier on the eyes.
      std::cout << "\n\n\n";

      // Will print all of the families in the GEDCOM file in descending order based on ID.
      my_file.printFamiliesInDescendingId();

      // Done.
      my_file.close();
   }
}