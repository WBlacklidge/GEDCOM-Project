/*
* @file
* @author William Blacklidge and Sreedhar Thirumanadham
* @date 01/30/2018
* @brief This class is for reading data from a Gedcom file.
*
* Implementation of the GedcomFile class.
*
*/
#include <ctime>
#include "GedcomFile.h"
#include "Utils.h"
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

            // Before we add, error check the individual.
            int birth_year, birth_month, birth_day;
            int curr_year, curr_month, curr_day;
            Gedcom::Utility::getYearMonthDayFromDateString(birthday, birth_year, birth_month, birth_day);
            Gedcom::Utility::getCurrentYearMonthDay(curr_year, curr_month, curr_day);

            // If the birthday is not valid report an error.
            if (!Gedcom::Utility::isValidDate(birth_year, birth_month, birth_day))
            {
               // This individual is over 150.  Report this as an error.
               reportError("US42", ObjectType::e_indv,
                  "Living INDV named " + name + " has an invalid birthday " + birthday, it->getLineNumber(), __FUNCTION__);
            }

            // The year is from 1900.  Subtract birthday from this date. 
            age = curr_year - birth_year;

            // If someone is 150 or older after this calculation something went wrong.
            // We do !is_alive because if someone is dead we don't want to compare the
            // current date to their birth.
            if (age >= 150 && is_alive)
            {
               // This individual is over 150.  Report this as an error.
               reportError("US07", ObjectType::e_indv,
                  "Living INDV named " + name + " age calculated as >= 150", it->getLineNumber(), __FUNCTION__);
            }

            if (!is_alive)
            {
               // Was this person over 150 years old between birth and death?
               int death_year, death_month, death_day;

               Gedcom::Utility::getYearMonthDayFromDateString(birthday, birth_year, birth_month, birth_day);
               Gedcom::Utility::getYearMonthDayFromDateString(deathday, death_year, death_month, death_day);

               // If the birthday is not valid report an error.
               if (!Gedcom::Utility::isValidDate(death_year, death_month, death_day))
               {
                  // This individual is over 150.  Report this as an error.
                  reportError("US42", ObjectType::e_indv,
                     "INDV named " + name + " has an invalid death date " + deathday, it->getLineNumber(), __FUNCTION__);
               }

               if ((death_year - birth_year) >= 150)
               {
                  // This individual is over 150.  Report this as an error.
                  reportError("US07", ObjectType::e_indv,
                     "Dead INDV named " + name + " age calculated as >= 150", it->getLineNumber(), __FUNCTION__);
               }
            }

            // If birthday and name match something went wrong.
            std::map<std::string, GedcomIndividual>::const_iterator check_it;
            for (check_it = m_individuals.begin(); check_it != m_individuals.end(); ++check_it)
            {
               if ((*check_it).second.m_name == name &&
                  (*check_it).second.m_birthday == birthday)
               {
                  // More than one person has the same name and birthday.
                  reportError("US23", ObjectType::e_indv,
                     "INDV named " + name + " has identical name and birthday as an already processed individual.", it->getLineNumber(), __FUNCTION__);
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

            // Error check that marriage date is before divorce date.
            const bool marriage_before_divorce = Utils::Gedcom::Utility::isDateGreaterThan(
               marriage_date, 
               divorce_date);

            if (!marriage_before_divorce)
            {
               // ERROR occurred.  Report it.
               reportError("US04", ObjectType::e_indv,
                  "Indvidual with ID: " + id + " has a marriage date after the divorce date.",
                  it->getLineNumber(), __FUNCTION__);
            }

            // Find the wife to check her deathday.
            // Get the wife name from the individuals map.
            std::string temp_find_wife(wife_id);
            temp_find_wife.erase(std::remove(temp_find_wife.begin(), temp_find_wife.end(), '@'),
               temp_find_wife.end());
            std::map<std::string, GedcomIndividual>::iterator it_find_wife;
            it_find_wife = m_individuals.find(temp_find_wife);

            // Find the husb to check his deathday.
            // Get the husband name from the individuals map.
            std::string temp_find_husb(husband_id);
            temp_find_husb.erase(std::remove(temp_find_husb.begin(), temp_find_husb.end(), '@'),
               temp_find_husb.end());
            std::map<std::string, GedcomIndividual>::iterator it_find_husb;
            it_find_husb = m_individuals.find(temp_find_husb);

            bool wife_found = false;
            bool husb_found = false;
            bool divorce_before_death_wife;
            bool divorce_before_death_husb;

            // If we found the wife...
            if (it_find_wife != m_individuals.end())
            {
               wife_found = true;
               // Check divorce before death.
               divorce_before_death_wife = Utils::Gedcom::Utility::isDateGreaterThan(
                  divorce_date, it_find_wife->second.m_deathday);

               int year_apart;
               int month_apart;
               int day_apart;

               Utils::Gedcom::Utility::isDateApart(it_find_wife->second.m_birthday,
                  marriage_date, year_apart, month_apart, day_apart);

               // Check that the wife was at least 14 years older than marriage date.
               if (year_apart < 14)
               {
                  // ERROR occurred.  Report it.
                  reportError("US10", ObjectType::e_indv,
                     "Indvidual with ID: " + it_find_wife->second.m_id + " has a marriage date that is not at least 14 years from birth.",
                     it->getLineNumber(), __FUNCTION__);
               }
            }

            // If we found the husband...
            if (it_find_husb != m_individuals.end())
            {
               husb_found = true;
               // Check divorce before death.
               divorce_before_death_husb = Utils::Gedcom::Utility::isDateGreaterThan(
                  divorce_date, it_find_husb->second.m_deathday);

               int year_apart;
               int month_apart;
               int day_apart;

               Utils::Gedcom::Utility::isDateApart(it_find_husb->second.m_birthday,
                  marriage_date, year_apart, month_apart, day_apart);

               // Check that the husband was at least 14 years older than marriage date.
               if (year_apart < 14)
               {
                  // ERROR occurred.  Report it.
                  reportError("US10", ObjectType::e_indv,
                     "Indvidual with ID: " + it_find_husb->second.m_id  + " has a marriage date that is not at least 14 years from birth.",
                     it->getLineNumber(), __FUNCTION__);
               }
            }

            if (wife_found && !divorce_before_death_wife)
            {
               // ERROR occurred.  Report it.
               reportError("US06", ObjectType::e_indv,
                  "Wife with ID: " + it_find_wife->second.m_id + " has a divorce date after the death date.",
                  it->getLineNumber(), __FUNCTION__);
            }

            if (husb_found && !divorce_before_death_husb)
            {
               // ERROR occurred.  Report it.
               reportError("US06", ObjectType::e_indv,
                  "Husband with ID: " + it_find_husb->second.m_id + " has a divorce date after the death date.",
                  it->getLineNumber(), __FUNCTION__);
            }

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

void GedcomFile::printfile() const
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
   std::cout << "\n*===============================================================================================================*" << std::endl;

   std::map<std::string, GedcomFamily>::const_iterator it;
   for (it = m_families.begin(); it != m_families.end(); ++it)
   {
      std::cout << it->second;
   }

   std::cout << "*===============================================================================================================*" << std::endl;
   
}

void GedcomFile::printIndividualsUpcomingBirthdays() const
{
	std::cout << "*==========================================Upcoming Birthdays===================================================*" << std::endl;
	std::cout << "*===============================================================================================================*" << std::endl;
	std::cout << "|ID:\t|Name:\t\t|Gender:|Birthday:\t\t|Age:\t|Alive:\t|Death:\t\t|Child:\t\t|Spouse:";
	std::cout << "\n*===============================================================================================================*" << std::endl;

	std::map<std::string, GedcomIndividual>::const_iterator it;

	std::string birthday;
	int birth_year, birth_month, birth_day;
	int curr_year, curr_month, curr_day;
	int flag = 0;
	
	Gedcom::Utility::getCurrentYearMonthDay(curr_year, curr_month, curr_day);

	for (it = m_individuals.begin(); it != m_individuals.end(); ++it)
	{
		
		birthday = it->second.m_birthday;
		
		
		Gedcom::Utility::getYearMonthDayFromDateString(birthday, birth_year, birth_month, birth_day);

		
			
		if ( (birth_day >= curr_day) && (birth_month >= curr_month) && (curr_year >= birth_year))
		{

				std::cout << it->second;
				flag = 1;
		}

	}

	
	if (!flag)
	{
		std::cout << "*==========================================NO Upcoming Birthdays===================================================*" << std::endl;
	}

	

	std::cout << "*=======================================================================================================================*" << std::endl;
}


void GedcomFile::printIndividualsUpcomingAnnivarsaries() const
{

	std::cout << "*==========================================Upcoming Annivarsaries===================================================*" << std::endl;

	std::cout << "*===============================================================================================================*" << std::endl;
	std::cout << "|ID:\t|Name:\t\t|Gender:|Birthday:\t\t|Age:\t|Alive:\t|Death:\t\t|Child:\t\t|Spouse:";
	std::cout << "\n*===============================================================================================================*" << std::endl;

	std::map<std::string, GedcomIndividual>::const_iterator it;

	std::string deathday;
	int death_year, death_month, death_day;
	int curr_year, curr_month, curr_day;
	int flag = 0;

	Gedcom::Utility::getCurrentYearMonthDay(curr_year, curr_month, curr_day);

	for (it = m_individuals.begin(); it != m_individuals.end(); ++it)
	{



		if (!it->second.m_isAlive)
		{

			deathday = it->second.m_deathday;

			Gedcom::Utility::getYearMonthDayFromDateString(deathday, death_year, death_month, death_day);
	

			if ((death_day >= curr_day) && (death_month >= curr_month) && (curr_year >= death_year))
			{

				std::cout << it->second;
				flag = 1;
			}
			
		}

	}

	if (!flag)
	{
		std::cout << "*==========================================NO Upcoming Annivarsaries===================================================*" << std::endl;
	}

	std::cout << "*===============================================================================================================*" << std::endl;
}

void GedcomFile::printIndividualsDeceased() const
{

	std::cout << "*==========================================List of Deceased===================================================*" << std::endl;

	std::cout << "*===============================================================================================================*" << std::endl;
	std::cout << "|ID:\t|Name:\t\t|Gender:|Birthday:\t\t|Age:\t|Alive:\t|Death:\t\t|Child:\t\t|Spouse:";
	std::cout << "\n*===============================================================================================================*" << std::endl;

	std::map<std::string, GedcomIndividual>::const_iterator it;

	int flag = 0;


	for (it = m_individuals.begin(); it != m_individuals.end(); ++it)
	{

		if (!it->second.m_isAlive)
		{
				std::cout << it->second;
				flag = 1;
		}

	}

	if (!flag)
	{
		std::cout << "*==========================================All are Living Happyly===================================================*" << std::endl;
	}

	std::cout << "*=============================================================================================================================*" << std::endl;
}

void GedcomFile::printIndividualsBornRecently() const
{

	std::cout << "*==========================================Recent Births <=30 days===================================================*" << std::endl;

	std::cout << "*===============================================================================================================*" << std::endl;
	std::cout << "|ID:\t|Name:\t\t|Gender:|Birthday:\t\t|Age:\t|Alive:\t|Death:\t\t|Child:\t\t|Spouse:";
	std::cout << "\n*===============================================================================================================*" << std::endl;

	std::map<std::string, GedcomIndividual>::const_iterator it;

	std::string birthday;
	int birth_year, birth_month, birth_day;
	int curr_year, curr_month, curr_day;
	int flag = 0;

	Gedcom::Utility::getCurrentYearMonthDay(curr_year, curr_month, curr_day);

	for (it = m_individuals.begin(); it != m_individuals.end(); ++it)
	{

		birthday = it->second.m_birthday;


		Gedcom::Utility::getYearMonthDayFromDateString(birthday, birth_year, birth_month, birth_day);


		if ((((curr_day - birth_day) <= 0) || ((birth_day - curr_day) <= 0)) && ((curr_month-birth_month == 1) || (curr_month - birth_month == 0) || (birth_month - curr_month == 11)) && ((curr_year == birth_year) || (curr_year == birth_year + 1)))
		{

			std::cout << it->second;
			flag = 1;
		}

	}
	
	if (!flag)
	{
		std::cout << "*==========================================No one Born Recently===================================================*" << std::endl;
	}

	std::cout << "*=============================================================================================================================*" << std::endl;
}

void GedcomFile::printIndividualsRecentDeaths() const
{

	std::cout << "*==========================================Recent Deaths <=30 days===================================================*" << std::endl;

	std::cout << "*===============================================================================================================*" << std::endl;
	std::cout << "|ID:\t|Name:\t\t|Gender:|Birthday:\t\t|Age:\t|Alive:\t|Death:\t\t|Child:\t\t|Spouse:";
	std::cout << "\n*===============================================================================================================*" << std::endl;

	std::map<std::string, GedcomIndividual>::const_iterator it;

	std::string deathday;
	int death_year, death_month, death_day;
	int curr_year, curr_month, curr_day;
	int flag = 0;

	Gedcom::Utility::getCurrentYearMonthDay(curr_year, curr_month, curr_day);

	for (it = m_individuals.begin(); it != m_individuals.end(); ++it)
	{

		if (!it->second.m_isAlive)
		{

			deathday = it->second.m_deathday;

			Gedcom::Utility::getYearMonthDayFromDateString(deathday, death_year, death_month, death_day);


			if ((((curr_day - death_day) <= 0) || ((death_day - curr_day) <= 0)) && ((curr_month - death_month == 1) || (curr_month - death_month == 0) || (death_month - curr_month == 11)) && ((curr_year == death_year) || (curr_year == death_year + 1)))
			{

				std::cout << it->second;
				flag = 1;
			}

		}

	}



	if (!flag)
	{
		std::cout << "*==========================================No one Died Recently===================================================*" << std::endl;
	}

	std::cout << "*=============================================================================================================================*" << std::endl;
}