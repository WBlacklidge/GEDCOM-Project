/**
* @file
* @author  William Blacklidge
* @date    03/05/2018
* @brief   This will test that the utility function for parents not being too old.
*
*/
#include "gtest/gtest.h"
#include "Utils.h"

using namespace Utils;

namespace
{
   /** Test fixture for ParentsNotTooOldTest. */
   class ParentsNotTooOldTest : public ::testing::Test
   {
   protected:
      /** Constructor. */
      ParentsNotTooOldTest()
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

   TEST_F(ParentsNotTooOldTest, Under6080)
   {
      // Appropriate age, should pass.
      std::string child_birth = "19 JAN 2010";
      std::string father_birth = "19 JAN 1985";
      std::string mother_birth = "21 FEB 1983";
      
      int years_apart;
      int months_apart;
      int days_apart;

      Gedcom::Utility::isDateApart(father_birth, child_birth, years_apart, months_apart, days_apart);

      EXPECT_TRUE(years_apart < 80);

      Gedcom::Utility::isDateApart(mother_birth, child_birth, years_apart, months_apart, days_apart);

      EXPECT_TRUE(years_apart < 60);
   }

   TEST_F(ParentsNotTooOldTest, Over6080)
   {
      // Not within the age ranges. age, should pass.
      std::string child_birth = "19 JAN 2010";
      std::string father_birth = "19 JAN 1925";
      std::string mother_birth = "21 FEB 1933";

      int years_apart;
      int months_apart;
      int days_apart;

      Gedcom::Utility::isDateApart(father_birth, child_birth, years_apart, months_apart, days_apart);

      EXPECT_FALSE(years_apart < 80);

      Gedcom::Utility::isDateApart(mother_birth, child_birth, years_apart, months_apart, days_apart);

      EXPECT_FALSE(years_apart < 60);
   }
}