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
   /** Test fixture for marriage before divorce test. */
   class MarriageBeforeDivorceTest : public ::testing::Test
   {
   protected:
      /** Constructor. */
      MarriageBeforeDivorceTest()
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

   TEST_F(MarriageBeforeDivorceTest, AllDates)
   {
      std::string marriage = "19 JAN 1985";
      std::string divorce = "20 FEB 2012";
      // We expect this to return false, marriage before divorce
      EXPECT_FALSE(Gedcom::Utility::isDateGreaterThan(divorce, marriage));

      // We expect this to return true.  divorce and marriage on the same day.
      divorce = "19 JAN 1985";
      EXPECT_TRUE(Gedcom::Utility::isDateGreaterThan(divorce, marriage));

      // We expect this to be true.  Divorce after marriage.
      marriage = "26 MAR 2018";
      EXPECT_TRUE(Gedcom::Utility::isDateGreaterThan(divorce, marriage));

      // Try a few edge cases that should pass.

      // One day apart.
      divorce = "26 MAR 2018";
      marriage = "25 MAR 2018";
      EXPECT_FALSE(Gedcom::Utility::isDateGreaterThan(divorce, marriage));

      // One month apart.
      divorce = "26 MAR 2018";
      marriage = "26 FEB 2018";
      EXPECT_FALSE(Gedcom::Utility::isDateGreaterThan(divorce, marriage));

      // One year apart.
      divorce = "26 MAR 2018";
      marriage = "26 MAR 2017";
      EXPECT_FALSE(Gedcom::Utility::isDateGreaterThan(divorce, marriage));
   }
}