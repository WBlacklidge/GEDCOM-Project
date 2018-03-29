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
   /** Test fixture for BirthDeathOver150Test. */
   class BirthDeathOver150Test : public ::testing::Test
   {
   protected:
      /** Constructor. */
      BirthDeathOver150Test()
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

   TEST_F(BirthDeathOver150Test, AllDates)
   {
      // Over 150
      int start_year = 1785;
      int start_month = 1;
      int start_day = 30;

      int end_year = 2013;
      int end_month = 1;
      int end_day = 2;

      EXPECT_TRUE(Gedcom::Utility::isOver150(start_year, start_month, start_day,
         end_year, end_month, end_day));

      // Under 150
      start_year = 1985;
      start_month = 1;
      start_day = 30;

      end_year = 2013;
      end_month = 1;
      end_day = 2;

      EXPECT_FALSE(Gedcom::Utility::isOver150(start_year, start_month, start_day,
         end_year, end_month, end_day));
   }
}