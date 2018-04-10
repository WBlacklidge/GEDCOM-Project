/**
* @file
* @author  William Blacklidge
* @date    03/05/2018
* @brief   This will test that the individual was at least 14 years old when married.
*
*/
#include "gtest/gtest.h"
#include "Utils.h"

using namespace Utils;

namespace
{
   /** Test fixture for MarriageAgeOver14Test. */
   class MarriageAgeOver14Test : public ::testing::Test
   {
   protected:
      /** Constructor. */
      MarriageAgeOver14Test()
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

   TEST_F(MarriageAgeOver14Test, Under14)
   {
      // Right at 13 years old.  Should fail.
      std::string birth = "19 JAN 1972";
      std::string marriage = "19 JAN 1985";
      
      int years_apart;
      int months_apart;
      int days_apart;

      Gedcom::Utility::isDateApart(birth, marriage, years_apart, months_apart, days_apart);

      EXPECT_TRUE(years_apart < 14);
   }

   TEST_F(MarriageAgeOver14Test, Exactly14)
   {
      // Right at 13 years old.  Should fail.
      std::string birth = "19 JAN 1971";
      std::string marriage = "19 JAN 1985";

      int years_apart;
      int months_apart;
      int days_apart;

      Gedcom::Utility::isDateApart(birth, marriage, years_apart, months_apart, days_apart);

      EXPECT_TRUE(years_apart == 14);
   }

   TEST_F(MarriageAgeOver14Test, Over14)
   {
      // Right at 13 years old.  Should fail.
      std::string birth = "19 JAN 1965";
      std::string marriage = "19 JAN 1985";

      int years_apart;
      int months_apart;
      int days_apart;

      Gedcom::Utility::isDateApart(birth, marriage, years_apart, months_apart, days_apart);

      EXPECT_TRUE(years_apart > 14);
   }
}