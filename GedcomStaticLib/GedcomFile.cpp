/*
* @file
* @author William Blacklidge
* @date 01/30/2018
* @brief This class is for reading data from a Gedcom file.
*
* Implementation of the GedcomFile class.
*
*/
#include <ctime>
#include "GedcomFile.h"
using namespace Utils::Gedcom;

#include "ErrorReporting.h"

#include <iostream>

#include <algorithm>

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
      reportError("NA", ObjectType::e_other, "File failed to open.", -1, __FUNCTION__);
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
      reportError("NA", ObjectType::e_other, "File is not open, can't read lines.", -1, __FUNCTION__);
      return false;
   }

   // Keep track of line numbers.
   unsigned int current_line_number = 1;
   // Store every line.
   while (std::getline(m_file, line))
   {
	   GedcomObject temp(line, current_line_number);
      m_fields.push_back(temp);
      current_line_number++;
   }

   // Now that we have each line, extract the individuals and family.
   for (std::vector<GedcomObject>::iterator it = m_fields.begin(); it != m_fields.end();)
   {
      // This is an invalid record...
      if (!it->isValidTag())
      {
         // skip
         it++;
         continue;
      }

      // If this record is an individual or family.
      if (0 == it->getLevel() && it->isIndiOrFam())
      {
         if (it->getTag() == "INDI")
         {
            // All the attributes of an individual we need to gather.
            std::string id = it->getId();

            // clean up the ID.  It has '@' in it.
            id.erase(std::remove(id.begin(), id.end(), '@'), id.end());

            std::string name;
            bool gender_female;
            std::string birthday;
            unsigned int age = 0;
            bool is_alive = true;
            std::string deathday;
            std::string child;
            std::string spouse;
            
            // We got what we needed from this initial record.
            it++;

            // A level of 0 indicates that we have a new individual or family
            while (it->getLevel() != 0)
            {
               if ("NAME" == it->getTag())
               {
                  name = it->getArguements();

                  // clean the name up.  It has slashes in it.
                  name.erase(std::remove(name.begin(), name.end(), '/'), name.end());

                  it++;
                  continue;
               }
               else if ("SEX" == it->getTag())
               {
                  if ("M" == it->getArguements())
                  {
                     gender_female = false;
                  }
                  else if ("F" == it->getArguements())
                  {
                     gender_female = true;
                  }
                  it++;
                  continue;
               }
               else if ("BIRT" == it->getTag())
               {
                  // This line doesn't actually have anything, so go to the next line which should be DATE
                  it++;

                  if ("DATE" == it->getTag())
                  {
                     birthday = it->getArguements();

                     // parse out the birthday
                     // String used to temporarily hold the parts of the birthday object.
                     std::string month, day, year;

                     // Search until we get to the first space.  Everything to the left is the level.
                     size_t position = birthday.find(' ');

                     // Position now contains the location of the end of the first attribute, level.
                     // Each character to the left of this position is the integer.
                     day = birthday.substr(0, position);

                     // When level is 0 the tag and ID can be in either position.

                     // Keep track of where we are starting.
                     const size_t start_of_month = position + 1;

                     // Keep track of the end position
                     size_t end_of_month = 0;

                     // Search for the next space in the line.
                     position = birthday.find(' ', start_of_month);
                     end_of_month = position;

                     // Now get the month.
                     month = birthday.substr(start_of_month, end_of_month - start_of_month);

                     // Keep track of where we are starting.
                     const size_t start_of_year = position + 1;

                     // Keep track of the end position
                     size_t end_of_year = 0;

                     // Search for the next space in the line.
                     position = birthday.find(' ', start_of_year);
                     end_of_year = position;

                     // Now get the month.
                     year = birthday.substr(start_of_year, end_of_year - start_of_year);


                     // since we have a birthday we can calculate age using it.
                     time_t t = time(0);
                     struct tm buf;
                     localtime_s(&buf, &t);

                     // Stores the returned size from stoi.
                     std::string::size_type size;   

                     // Convert the string to integer
                     const int n_year = std::stoi(year, &size);

                     // The year is from 1900.  Subtract birthday from this date. 
                     age = (buf.tm_year + 1900) - n_year;
                  }
                  else
                  {
                     // This is bad, we somehow got an invalid DATE record.
                     reportError("NA", ObjectType::e_indv, 
                        "Invalid Date Record", it->getLineNumber(), __FUNCTION__);
                  }

                  it++;
                  continue;
               }
               else if ("DEAT" == it->getTag())
               {
                  // This person has a date for death so they are no longer alive.
                  is_alive = false;

                  // This line doesn't actually have anything, so go to the next line which should be DATE
                  it++;

                  if ("DATE" == it->getTag())
                  {
                     deathday = it->getArguements();
                  }
                  else
                  {
                     // This is bad, we somehow got an invalid DATE record.
                     reportError("NA", ObjectType::e_indv,
                        "Invalid Date Record", it->getLineNumber(), __FUNCTION__);
                  }

                  it++;
                  continue;
               }
               else if ("FAMC" == it->getTag())
               {
                  child = it->getArguements();
                  it++;
                  continue;
               }
               else if ("FAMS" == it->getTag())
               {
                  spouse = it->getArguements();
                  it++;
                  continue;
               }
               else
               {
                  // un handled tag.
                  it++;
                  continue;
               }
            }

            // We left the while loop which means we hit another 0.
            // Create an individual and insert it into the map.
            GedcomIndividual temp(id, 
               name, 
               gender_female, 
               birthday, 
               age, 
               is_alive, 
               deathday, 
               child, 
               spouse);

            // Check that the Indv ID is not already in the map.
            std::map<std::string, GedcomIndividual>::iterator it_find;

            // See if we can find the indv
            it_find = m_individuals.find(id);

            // m_families.end() means it wasn't found.
            if (it_find != m_individuals.end())
            {
               // We found the Indv already.
               // Don't add and log an error.
               reportError("US22", ObjectType::e_indv,
                  "Indvidual with ID: " + id + " already exists.",
                  it->getLineNumber(), __FUNCTION__);
            }
            else
            {
               m_individuals.insert(std::pair<std::string, GedcomIndividual>(id, temp));
            }
         }
         else if (it->getTag() == "FAM")
         {
            std::string id = it->getId();

            // clean up the ID.  It has '@' in it.
            id.erase(std::remove(id.begin(), id.end(), '@'), id.end());

            std::string husband_id;
            std::string husband_name;
            std::string wife_id;
            std::string wife_name;
            std::vector<std::string> child_ids;

            std::string marriage_date;
            std::string divorce_date;

            // We got what we needed from this initial record.
            it++;

            // A level of 0 indicates that we have a new individual or family
            while (it->getLevel() != 0)
            {
               if ("HUSB" == it->getTag())
               {
                  husband_id = it->getArguements();

                  // Get the husband name from the individuals map.
                  std::string temp_find_husb(husband_id);
                  temp_find_husb.erase(std::remove(temp_find_husb.begin(), temp_find_husb.end(), '@'), 
                     temp_find_husb.end());

                  // Check that the Family ID is not already in the map.
                  std::map<std::string, GedcomIndividual>::iterator it_find_husband;
                  it_find_husband = m_individuals.find(temp_find_husb);
                  if (it_find_husband == m_individuals.end())
                  {
                     reportError("NA", ObjectType::e_fam,
                        "Could not find Husband ID: " + temp_find_husb,
                        it->getLineNumber(), __FUNCTION__);
                  }
                  else
                  {
                     husband_name = it_find_husband->second.m_name;
                  }

                  it++;
                  continue;
               }
               else if ("WIFE" == it->getTag())
               {
                  wife_id = it->getArguements();

                  // Get the wife name from the individuals map.
                  std::string temp_find_wife(wife_id);
                  temp_find_wife.erase(std::remove(temp_find_wife.begin(), temp_find_wife.end(), '@'),
                     temp_find_wife.end());

                  // Check that the Family ID is not already in the map.
                  std::map<std::string, GedcomIndividual>::iterator it_find_wife;
                  it_find_wife = m_individuals.find(temp_find_wife);
                  if (it_find_wife == m_individuals.end())
                  {
                     reportError("NA", ObjectType::e_fam,
                        "Could not find Wife ID: " + temp_find_wife,
                        it->getLineNumber(), __FUNCTION__);
                  }
                  else
                  {
                     wife_name = it_find_wife->second.m_name;
                  }

                  it++;
                  continue;
               }
               else if ("CHIL" == it->getTag())
               {
                  child_ids.push_back(it->getArguements());
                  it++;
                  continue;
               }
               else if ("MARR" == it->getTag())
               {
                  // This line doesn't actually have anything, so go to the next line which should be DATE
                  it++;

                  if ("DATE" == it->getTag())
                  {
                     marriage_date = it->getArguements();
                  }
                  else
                  {
                     // This is bad, we somehow got an invalid DATE record.
                     reportError("NA", ObjectType::e_fam,
                        "Invalid Date Record",
                        it->getLineNumber(), __FUNCTION__);
                  }

                  it++;
                  continue;
               }
               else if ("DIV" == it->getTag())
               {
                  // This line doesn't actually have anything, so go to the next line which should be DATE
                  it++;

                  if ("DATE" == it->getTag())
                  {
                     divorce_date = it->getArguements();
                  }
                  else
                  {
                     // This is bad, we somehow got an invalid DATE record.
                     reportError("NA", ObjectType::e_fam,
                        "Invalid Date Record",
                        it->getLineNumber(), __FUNCTION__);
                  }
                  it++;
                  continue;
               }
               else
               {
                  // un handled tag.
                  it++;
                  continue;
               }
            }

            // We left the while loop which means we hit another 0.
            // Create an individual and insert it into the map.
            GedcomFamily temp(id,
               husband_id,
               husband_name,
               wife_id,
               wife_name,
               child_ids,
               marriage_date,
               divorce_date);

            // Check that the Family ID is not already in the map.
            std::map<std::string, GedcomFamily>::iterator it_find;

            // See if we can find the family
            it_find = m_families.find(id);
           
            // m_families.end() means it wasn't found.
            if (it_find != m_families.end())
            {
               // We found the family already.
               // Don't add and log an error.
               reportError("US22", ObjectType::e_fam,
                  "Family with ID: " + id + " already exists.",
                  it->getLineNumber(), __FUNCTION__);
            }
            else
            {
               m_families.insert(std::pair<std::string, GedcomFamily>(id, temp));
            }
         }
      }
      else
      {
         it++;
         continue;
      }
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
	std::vector<GedcomObject>::const_iterator it;
	for (it = m_fields.begin(); it != m_fields.end(); ++it)
	{
		std::cout << "--> ";
		it->printOriginal();

		std::cout << "<-- ";
		it->printParsed();
	}
}

void GedcomFile::printIndividualsInDescendingId() const
{
   std::cout << "*===============================================================================================================*" << std::endl;
   std::cout << "|ID:\t|Name:\t\t|Gender:|Birthday:\t\t|Age:\t|Alive:\t|Death:\t\t|Child:\t\t|Spouse:";
   std::cout << "\n*===============================================================================================================*" << std::endl;

   std::map<std::string, GedcomIndividual>::const_iterator it;
   for (it = m_individuals.begin(); it != m_individuals.end(); ++it)
   {
      std::cout << it->second;
   }

   std::cout << "*===============================================================================================================*" << std::endl;
}

void GedcomFile::printFamiliesInDescendingId() const
{
   std::cout << "*===============================================================================================================*" << std::endl;
   std::cout << "|ID:\t|Married:     |Div:  |Husband ID:\t|Husband Name:\t|Wife ID:\t|Wife Name:\t|Children:\t\t";
   std::cout << "*===============================================================================================================*" << std::endl;

   std::map<std::string, GedcomFamily>::const_iterator it;
   for (it = m_families.begin(); it != m_families.end(); ++it)
   {
      std::cout << it->second;
   }

   std::cout << "*===============================================================================================================*" << std::endl;
   
}