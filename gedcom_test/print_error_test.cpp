/**
* @file
* @author  William Blacklidge
* @date    02/12/2018
* @brief   This will test error printing.
*
*/

#include "gtest/gtest.h"


namespace
{
   /** Test fixture for error tests. */
   class PrintErrorTest : public ::testing::Test
   {
   public:

   protected:
      /** Constructor. */
      PrintErrorTest()
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

   TEST_F(PrintErrorTest, ToStringBool)
   {
      EXPECT_TRUE(true);
   }
}