#pragma once
#include "Utils.h"
#include <chrono>

void Utils::Gedcom::Utility::getCurrentYearMonthDay(int& year, int& month, int& day)
{
   // since we have a birthday we can calculate age using it.
   time_t t = time(0);
   struct tm buf;
   localtime_s(&buf, &t);
   year = buf.tm_year + 1900;
   month = buf.tm_mon + 1;
   day = buf.tm_mday;
}

bool Utils::Gedcom::Utility::isValidDate(const int year, const int month, const int day)
{
   if (year < 0 ||
      month < 0 ||
      day < 0 ||
      day > 31 ||
      month > 13)
   {
      return false;
   }

   switch (month)
   {
   case 1:
      if (day > 31)
      {
         return false;
      }

      break;
   case 2:
      if (day > 28)
      {
         return false;
      }
      break;
   case 3:
      if (day > 31)
      {
         return false;
      }
      break;
   case 4:
      if (day > 30)
      {
         return false;
      }
      break;
   case 5:
      if (day > 31)
      {
         return false;
      }
      break;
   case 6:
      if (day > 30)
      {
         return false;
      }
      break;
   case 7:
      if (day > 31)
      {
         return false;
      }
      break;
   case 8:
      if (day > 31)
      {
         return false;
      }
      break;
   case 9:
      if (day > 30)
      {
         return false;
      }
      break;
   case 10:
      if (day > 31)
      {
         return false;
      }
      break;
   case 11:
      if (day > 30)
      {
         return false;
      }
      break;
   case 12:
      if (day > 31)
      {
         return false;
      }
      break;
   }

   // We didn't find anything wrong with the date.
   return true;
}

int Utils::Gedcom::Utility::monthToInt(const std::string& month)
{
   if (month == "JAN")
   {
      return 1;
   }
   else if (month == "FEB")
   {
      return 2;
   }
   else if (month == "MAR")
   {
      return 3;
   }
   else if (month == "APR")
   {
      return 4;
   }
   else if (month == "MAY")
   {
      return 5;
   }
   else if (month == "JUN")
   {
      return 6;
   }
   else if (month == "JUL")
   {
      return 7;
   }
   else if (month == "AUG")
   {
      return 8;
   }
   else if (month == "SEP")
   {
      return 9;
   }
   else if (month == "OCT")
   {
      return 10;
   }
   else if (month == "NOV")
   {
      return 11;
   }
   else if (month == "DEC")
   {
      return 12;
   }

   return -1;
}

bool Utils::Gedcom::Utility::getYearMonthDayFromDateString(std::string& date,
   int& year, int& month, int& day)
{
   // If the string is empty something went wrong.  Return false.
   if (0 == date.size())
   {
      return false;
   }

   // parse out the birthday
   // String used to temporarily hold the parts of the birthday object.
   std::string temp_month, temp_day, temp_year;

   // Search until we get to the first space.  Everything to the left is the level.
   size_t position = date.find(' ');

   // Position now contains the location of the end of the first attribute, level.
   // Each character to the left of this position is the integer.
   temp_day = date.substr(0, position);

   // When level is 0 the tag and ID can be in either position.

   // Keep track of where we are starting.
   const size_t start_of_month = position + 1;

   // Keep track of the end position
   size_t end_of_month = 0;

   // Search for the next space in the line.
   position = date.find(' ', start_of_month);
   end_of_month = position;

   // Now get the month.
   temp_month = date.substr(start_of_month, end_of_month - start_of_month);

   // Keep track of where we are starting.
   const size_t start_of_year = position + 1;

   // Keep track of the end position
   size_t end_of_year = 0;

   // Search for the next space in the line.
   position = date.find(' ', start_of_year);
   end_of_year = position;

   // Now get the month.
   temp_year = date.substr(start_of_year, end_of_year - start_of_year);

   // Stores the returned size from stoi.
   std::string::size_type size = 0;
   year = std::stoi(temp_year, &size);
   month = monthToInt(temp_month);
   day = std::stoi(temp_day, &size);

   return true;
}

bool Utils::Gedcom::Utility::isOver150(const int startYear, const int startMonth, const int startDay,
   const int endYear, const int endMonth, const int endDay)
{
   if (endYear - startYear >= 150)
   {
      return true;
   }

   return false;
}

bool Utils::Gedcom::Utility::isDateGreaterThan(std::string& date1, std::string& date2)
{
   int date1_year;
   int date1_month;
   int date1_day;
   int date2_year;
   int date2_month;
   int date2_day;

   // Parse the string and get the tear, month and day
   const bool valid_date_1 = Utils::Gedcom::Utility::getYearMonthDayFromDateString(
      date1,
      date1_year,
      date1_month,
      date1_day);

   // Parse the string and get the tear, month and day
   const bool valid_date_2 = Utils::Gedcom::Utility::getYearMonthDayFromDateString(
      date2,
      date2_year,
      date2_month,
      date2_day);

   bool not_in_order = false;

   // If both dates were given we can error check.
   if (valid_date_1 && valid_date_2)
   {
      // Easiest check is year.
      if (date1_year > date2_year)
      {
         return false;
      }
      else if(date1_year < date2_year)
      {
         return true;
      }
      else
      {
         // They are equal.  Check month.
         if (date1_month > date2_month)
         {
            return false;
         }
         else if (date1_month < date2_month)
         {
            return true;
         }
         else
         {
            // They are equal.  Check day.
            if (date1_day > date2_day)
            {
               if (date1_day > date2_day)
               {
                  return false;
               }
               else
               {
                  // It is equal or less than.  We are set.
                  return true;
               }
            }
         }
      }
   }
   return true;
}