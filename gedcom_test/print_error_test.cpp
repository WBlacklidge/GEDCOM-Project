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
   class PrintErrorTest : public ::testing::Test
   {
   public:
      int m_testNumber;
   protected:
      /** Constructor. */
      PrintErrorTest() : m_testNumber(40)
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

         output = Utils::Gedcom::reportError(
            "This is just a test",
            __FUNCTION__,
            line,
            __FILE__);
      }
   };

   TEST_F(PrintErrorTest, TestFunctionName)
   {
      std::string temp;
      TestFunction(temp);
      EXPECT_TRUE(std::string::npos != temp.find("TestFunction", 0));
   }

   TEST_F(PrintErrorTest, TestLineNumber)
   {
      std::string temp;
      TestFunction(temp);
      EXPECT_TRUE(std::string::npos != temp.find("2408", 0));
   }

   TEST_F(PrintErrorTest, TestFileName)
   {
      std::string temp;
      TestFunction(temp);
      EXPECT_TRUE(std::string::npos != temp.find("print_error_test.cpp", 0));
   }

   TEST_F(PrintErrorTest, TestLogFile)
   {
      // Empty out the log.
      std::ofstream my_file;
      my_file.open("data/log.txt", std::ios::trunc);
      my_file.close();
      // Log is now empty

      // Force the error output
      // We don't want to do anything with the string it 
      // fills because this test tests the file.
      std::string does_not_matter;
      TestFunction(does_not_matter);

      std::ifstream input_file("data/log.txt", std::ifstream::binary);

      input_file.clear();
      if (input_file)
      {
         // get length of file:
         input_file.seekg(0, input_file.end);
         int length = input_file.tellg();
         input_file.seekg(0, input_file.beg);

         char* buffer = new char[length];

         std::cout << "Reading " << length << " characters... ";
         // read data as a block:
         input_file.read(buffer, length);

         const std::string temp(buffer);

         EXPECT_TRUE(std::string::npos != temp.find("2408", 0));

         input_file.close();

         delete[] buffer;
      }
      else
      {
         EXPECT_TRUE(false);
      }
   }

   TEST_F(PrintErrorTest, TestBadGedcomEntry)
   {
      // Empty out the log.
      std::ofstream log_file;
      log_file.open("data/log.txt", std::ios::trunc);
      log_file.close();
      // Log is now empty

      std::string ged_file = "data/print_error_test.ged"; 

      // Using the file path, create a GedcomFile object.
      Utils::Gedcom::GedcomFile my_file(ged_file);

      // Read each line from the GedComFile and save it.
      my_file.readLines();

      std::ifstream input_file("data/log.txt", std::ifstream::binary);

      if (input_file)
      {
         // get length of file:
         input_file.seekg(0, input_file.end);
         int length = input_file.tellg();
         input_file.seekg(0, input_file.beg);

         char* buffer = new char[length];

         std::cout << "Reading " << length << " characters... ";
         // read data as a block:
         input_file.read(buffer, length);

         const std::string temp(buffer);

         EXPECT_TRUE(std::string::npos != temp.find("Invalid Data Record Line# 22", 0));

         input_file.close();

         delete[] buffer;
      }
      else
      {
         EXPECT_TRUE(false);
      }
   }
}