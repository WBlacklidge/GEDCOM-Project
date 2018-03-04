#pragma once
#include <chrono>
#include <string>

void getCurrentYearMonthDay(int& year, int& month, int& day)
{
   // since we have a birthday we can calculate age using it.
   time_t t = time(0);
   struct tm buf;
   localtime_s(&buf, &t);
   year = buf.tm_year + 1900;
   month = buf.tm_mon + 1;
   day = buf.tm_mday;
}

void getYearMonthDayFromDateString(std::string& date, 
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
   std::string::size_type size;
   year = std::stoi(temp_year, &size);
   month = std::stoi(temp_month, &size);
   day = std::stoi(temp_day, &size);
}