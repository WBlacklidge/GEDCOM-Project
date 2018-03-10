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

void Utils::Gedcom::Utility::getYearMonthDayFromDateString(std::string& date,
   int& year, int& month, int& day)
{
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