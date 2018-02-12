/**
* @file
* @author  William Blacklidge
* @date    02/12/2018
* @brief   This will test error printing.
*
*/
#include "gtest/gtest.h"
#include "ErrorReporting.h"

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

      /** Test for function name.  
      */
      void TestFunction(std::string& output)
      {
         // Give a line number that is something static we 
         // can test for later.
         const int line = 2408;
         std::ostringstream os;
         Utils::Gedcom::reportError(os, 
            "This is just a test", 
            __FUNCTION__,
            line,
            __FILE__);

         output = os.str();
      }
   };

   TEST_F(PrintErrorTest, TestFunctionName)
   {
      bool passed_test = false;
      std::string temp;
      TestFunction(temp);
      EXPECT_TRUE(std::string::npos != temp.find("TestFunction", 0));
   }

   TEST_F(PrintErrorTest, TestLineNumber)
   {
      bool passed_test = false;
      std::string temp;
      TestFunction(temp);
      EXPECT_TRUE(std::string::npos != temp.find("2408", 0));
   }

   TEST_F(PrintErrorTest, TestFileName)
   {
      bool passed_test = false;
      std::string temp;
      TestFunction(temp);
      EXPECT_TRUE(std::string::npos != temp.find("print_error_test.cpp", 0));
   }
}