/**
* @file
* @author  William Blacklidge
* @date    03/05/2018
* @brief   This will test invalid dates.
*
*/
#include "gtest/gtest.h"
#include "Utils.h"

using namespace Utils;

namespace
{
   /** Test fixture for invalid dates tests. */
   class InvalidDatesTest : public ::testing::Test
   {
   protected:
      /** Constructor. */
      InvalidDatesTest()
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

   TEST_F(InvalidDatesTest, AllDates)
   {
      // Valid Date 
      int year = 1985;
      int month = 1;
      int day = 30;
      EXPECT_TRUE(Gedcom::Utility::isValidDate(year, month, day));

      // Invalid Date 1
      year = 1985;
      month = 14;
      day = 30;
      EXPECT_FALSE(Gedcom::Utility::isValidDate(year, month, day));

      // Invalid Date 2
      year = 1985;
      month = 2;
      day = 29;
      EXPECT_FALSE(Gedcom::Utility::isValidDate(year, month, day));

      // Invalid Date 3
      year = 1985;
      month = 4;
      day = 31;
      EXPECT_FALSE(Gedcom::Utility::isValidDate(year, month, day));
   }
}