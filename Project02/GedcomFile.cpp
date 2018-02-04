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

   // Store every line.
   while (std::getline(m_file, line))
   {
	   GedcomObject temp(line);
      m_fields.push_back(temp);
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

                     std::string::size_type sz;   


                     int n_year = std::stoi(year, &sz);

                     age = (buf.tm_year + 1900) - n_year;
                  }
                  else
                  {
                     // This is bad, we somehow got an invalid DATE record.
                     std::cout << "Invalid Date Record" << std::endl;
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
                     std::cout << "Invalid Date Record" << std::endl;
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
            m_individuals.insert(std::pair<std::string, GedcomIndividual>(id, temp));
         }
         else if (it->getTag() == "FAM")
         {
            std::string id = it->getId();

            // clean up the ID.  It has '@' in it.
            id.erase(std::remove(id.begin(), id.end(), '@'), id.end());

            std::string husband_id;
            std::string wife_id;
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
                  it++;
                  continue;
               }
               else if ("WIFE" == it->getTag())
               {
                  wife_id = it->getArguements();
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
                     std::cout << "Invalid Date Record" << std::endl;
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
                     std::cout << "Invalid Date Record" << std::endl;
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
               wife_id,
               child_ids,
               marriage_date,
               divorce_date);

            m_families.insert(std::pair<std::string, GedcomFamily>(id, temp));
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

void GedcomFile::printIndividuals() const
{
   std::cout << "*===============================================================================================================*" << std::endl;
   std::cout << "|ID:\t|Name:\t\t|Gender:|Birthday:\t\t|Age:\t|Alive:\t|Death:\t\t|Child:\t\t|Spouse:";
   std::cout << "\n*===============================================================================================================*" << std::endl;

   std::map<std::string, GedcomIndividual>::const_iterator it;
   for (it = m_individuals.begin(); it != m_individuals.end(); ++it)
   {
      std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
      std::cout << it->first << "\t";
      std::cout << it->second.m_name << "\t";
      const char gender_char = it->second.m_genderFemale ? 'F' : 'M';
      std::cout << gender_char << "\t";
      std::cout << it->second.m_birthday << "\t\t";
      std::cout << it->second.m_age << "\t";
      const char alive_char = it->second.m_isAlive ? 'Y' : 'N';
      std::cout << alive_char << "\t";
      if (it->second.m_deathday.size() <= 0)
      {
         std::cout << "NA\t\t";
      }
      else
      {
         std::cout << it->second.m_deathday << "\t";
      }
      
      if (it->second.m_child.size() <= 0)
      {
         std::cout << "NA\t\t";
      }
      else
      {
         std::cout << it->second.m_child << "\t\t";
      }

      if (it->second.m_spouse.size() <= 0)
      {
         std::cout << "NA\t\t";
      }
      else
      {
         std::cout << it->second.m_spouse << "\t\t";
      }
      std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
   }

   std::cout << "*====================================================================*" << std::endl;
}

void GedcomFile::printFamilies() const
{
   std::cout << "*===============================================================================================================*" << std::endl;
   std::cout << "|ID:\t|Married:\t\t|Divorced:|Husband ID:\t\t|Husband Name:\t|Wife ID:\t|Wife Name:\t\t|Children:\t\t";
   std::cout << "\n*===============================================================================================================*" << std::endl;

   std::map<std::string, GedcomFamily>::const_iterator it;
   for (it = m_families.begin(); it != m_families.end(); ++it)
   {
      std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
      std::cout << it->first << "\t";
      std::cout << it->second.m_marriageDate << "\t";
      const std::string divorce_date = it->second.m_divorceDate.size() == 0 ? "NA" : it->second.m_divorceDate;
      std::cout << divorce_date << "\t";
      std::cout << it->second.m_husbandId << "\t\t";

      std::string temp_find_husb(it->second.m_husbandId);
      temp_find_husb.erase(std::remove(temp_find_husb.begin(), temp_find_husb.end(), '@'), temp_find_husb.end());

      // Get the husband name from the other map.
      std::cout << m_individuals.find(temp_find_husb)->second.m_name << "\t";

      std::cout << it->second.m_wifeId << "\t\t";

      // Get the husband name from the other map.
      std::string temp_find_wife(it->second.m_wifeId);
      temp_find_wife.erase(std::remove(temp_find_wife.begin(), temp_find_wife.end(), '@'), temp_find_wife.end());

      std::cout << m_individuals.find(temp_find_wife)->second.m_name << "\t";

      for (int child_itr = 0; child_itr < it->second.m_childIds.size(); ++child_itr)
      {
         std::cout << " " << it->second.m_childIds[child_itr];
      }

      std::cout << "\t\t";

      std::cout << "--------------------------------------------------------------------------------------------------------------" << std::endl;
   }

   std::cout << "*====================================================================*" << std::endl;
   
}