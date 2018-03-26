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
   /** Test fixture for divorce before death tests. */
   class DivorceBeforeDeathTest : public ::testing::Test
   {
   protected:
      /** Constructor. */
      DivorceBeforeDeathTest()
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

   TEST_F(DivorceBeforeDeathTest, AllDates)
   {
      std::string divorce = "19 JAN 1985";
      std::string death = "20 FEB 2012";
      // We expect this to return true, divorce was before death
      EXPECT_FALSE(Gedcom::Utility::isDateGreaterThan(death, divorce));

      // We expect this to return false.  Death and divorce on the same day.
      death = "19 JAN 1985";
      EXPECT_TRUE(Gedcom::Utility::isDateGreaterThan(death, divorce));

      // We expect this to be false.  Divorce after death.
      divorce = "26 MAR 2018";
      EXPECT_TRUE(Gedcom::Utility::isDateGreaterThan(death, divorce));

      // Try a few edge cases that should pass.

      // One day apart.
      death = "26 MAR 2018";
      divorce = "25 MAR 2018";
      EXPECT_FALSE(Gedcom::Utility::isDateGreaterThan(death, divorce));

      // One month apart.
      death = "26 MAR 2018";
      divorce = "26 FEB 2018";
      EXPECT_FALSE(Gedcom::Utility::isDateGreaterThan(death, divorce));

      // One year apart.
      death = "26 MAR 2018";
      divorce = "26 MAR 2017";
      EXPECT_FALSE(Gedcom::Utility::isDateGreaterThan(death, divorce));
   }
}