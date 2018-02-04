/*
* @file
* @author William Blacklidge
* @date 01/30/2018
* @brief This class is for reading data from a Gedcom file.
*
* Implementation of the GedcomFile class.
*
*/
#include "GedcomFile.h"
using namespace Utils::Gedcom;

#include <iostream>

GedcomFile::GedcomFile(const std::string& filename) : m_lineNumber(0)
{
   open(filename.c_str());
}

GedcomFile::~GedcomFile()
{
   if (m_file.is_open())
   {
      m_file.close();
   }
}

bool GedcomFile::open(const std::string& filename)
{
   m_file.open(filename.c_str(), std::ios_base::in);

   if (!m_file.is_open())
   {
      return false;
   }

   m_lineNumber = 0;

   return true;
}

void GedcomFile::close()
{
   m_file.close();
   m_file.clear();
}

bool GedcomFile::readLines()
{
   std::string line;

   // If the file isn't open we can't read anything
   if (!m_file.is_open())
   {
      return false;
   }

   while (std::getline(m_file, line))
   {
      GedcomObject temp(line);
      m_fields.push_back(temp);
   }

   // Get a line of data from the file
   if (m_file.good())
   {
      return true;
   }
   else
   {
      return false;
   }
}

void GedcomFile::print() const
{
   for (std::vector<std::string>::size_type i = 0; i != m_fields.size(); i++)
   {
      std::cout << "--> ";
      m_fields[i].printOriginal();

      std::cout << "<-- ";
      m_fields[i].printParsed();
   }
}