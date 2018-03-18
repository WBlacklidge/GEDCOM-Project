#pragma once
#include <string>

namespace Utils
{
   namespace Gedcom
   {
      class Utility
      {
      public:
         static void getCurrentYearMonthDay(int& year, int& month, int& day);

         static bool isValidDate(const int year, const int month, const int day);

         static int monthToInt(const std::string& month);

         static bool getYearMonthDayFromDateString(std::string& date,
            int& year, int& month, int& day);

         static bool isOver150(const int startYear, const int startMonth, const int startDay,
            const int endYear, const int endMonth, const int endDay);

         static bool isDateGreaterThan(std::string& date1, std::string& date2);
      };
   }
}