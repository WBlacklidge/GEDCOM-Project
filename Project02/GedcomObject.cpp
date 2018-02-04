/*
* @file
* @author William Blacklidge
* @date 01/30/2018
* @brief This class will parse a string line read from a Gedcom file and 
* fill in the attributes.
*
* Implementation of the GedcomObject class.
*
*/
#include "GedcomObject.h"
using namespace Utils::Gedcom;

#include <iostream>
GedcomObject::GedcomObject(std::string& line) : m_level(0),
m_id(""),
m_isValid(false)
{
   m_rawLine = line;
   parse();
}

GedcomObject::~GedcomObject()
{

}

void GedcomObject::printOriginal() const
{
   std::cout << m_rawLine << std::endl;
}

void GedcomObject::printParsed() const
{
   // Print in this format <level>|<tag>|<valid>|<args>
   const char valid_char = (m_isValid)?'Y':'N';
   const bool is_level_0 = (0 == m_level) ? true : false;
   const bool is_tag_indi_or_fam = isIndiOrFam(m_tag);

   if (is_level_0 && is_tag_indi_or_fam)
   {
      std::cout << m_level << "|" << m_tag << "|" << valid_char << "|" << m_id << std::endl;
   }
   else
   {
      if (!m_arguments.empty())
      {
         std::cout << m_level << "|" << m_tag << "|" << valid_char << "|" << m_arguments << std::endl;
      }
      else
      {
         std::cout << m_level << "|" << m_tag << "|" << valid_char << std::endl;
      }
   }
}

void GedcomObject::parse()
{
   // String used to temporarily hold the parts of the GEDCOM object.
   std::string temp;

   // Search until we get to the first space.  Everything to the left is the level.
   unsigned int position = m_rawLine.find(' ');

   // Position now contains the location of the end of the first attribute, level.
   // Each character to the left of this position is the integer.
   temp = m_rawLine.substr(0, position);

   // Convert the string representation to integer
   m_level = static_cast<unsigned int>(strtoul(temp.c_str(), NULL, 10));

   // When level is 0 the tag and ID can be in either position.

   // Keep track of where we are starting.
   const unsigned int start_of_tag = position+1;

   // Keep track of the end position
   unsigned int end_of_tag = 0;

   // Track if we have arguements
   bool is_args = true;

   // Search for the next space in the line.
   position = m_rawLine.find(' ', start_of_tag);

   if (std::string::npos == position)
   {
      //there is nothing left.
      is_args = false;
      position = start_of_tag;
      end_of_tag = m_rawLine.size();
   }
   else
   {
      end_of_tag = position;
   }

   // Now get the tag.
   temp.clear();
   temp = m_rawLine.substr(start_of_tag, end_of_tag - start_of_tag);

   const bool is_tag = isValidTag(temp);

   // If this is the special level 0 case 
   // If its one of the two tags that need this special case
   // or if an ID was present before the TAG...
   if (0 == m_level && (isIndiOrFam(temp) || !is_tag))
   {
      // If its a tag...
      if (is_tag)
      {
         // Set the tag
         m_tag = temp;
      }
      else
      {
         // Not a tag, must be an ID
         m_id = temp;
         is_args = false;
      }

      // Since the first was an ID check the next string for the tag.
      temp.clear();
      temp = m_rawLine.substr(position+1, m_rawLine.size() - 1);

      if (is_tag)
      {
         m_id = temp;
      }
      else
      {
         m_tag = temp;
      }

      m_isValid = isIndiOrFam(temp);

      // We got the ID and Tag, so we can exit this function.
      return;

   }
   // Non-level 0 case.
   else
   {
      m_tag = temp;
   }

   // Now that we have a tag we can tell if this is a valid entry or not.
   // Since we will only set it true if it finds something start it at false.
   if (isValidTag(m_tag))
   {
      // Now check that the tag and level are compatiable
      m_isValid = isTagCompatableWithLevel(m_tag, m_level);
   }
   else
   {
      m_isValid = false;
   }

   if (is_args)
   {
      // Position is at the end of the tag, so everything else is the arguements.
      temp.clear();
      temp = m_rawLine.substr(position + 1, m_rawLine.size() - position - 1);
      m_arguments = temp;
   }
}

bool GedcomObject::isValidTag(const std::string& tag) const
{
   for (unsigned int i = 0; i < Utils::Gedcom::e_end; ++i)
   {
      // As long as the tag is equal to any of our possible tags 
      // for this project it is valid.
      if (tag == Utils::Gedcom::sc_tagsString[i])
      {
         return true;
      }
   }

   return false;
}

bool GedcomObject::isIndiOrFam(const std::string& tag) const
{
   if ((tag == Utils::Gedcom::sc_tagsString[Utils::Gedcom::e_individualId]) ||
      (tag == Utils::Gedcom::sc_tagsString[Utils::Gedcom::e_family]))
   {
      return true;
   }
  
   return false;
}

bool GedcomObject::isTagCompatableWithLevel(const std::string& tag,
   const int level) const
{
   switch (level)
   {
   case 0:
      if ("INDI" == tag || "FAM" == tag || "HEAD" == tag || "TRLR" == tag || "NOTE" == tag)
      {
         return true;
      }
      else
      {
         return false;
      }
      break;
   case 1:
      if ("NAME" == tag || "SEX" == tag || "BIRT" == tag || "DEAT" == tag || "FAMC" == tag || 
         "FAMS" == tag || "MARR" == tag || "HUSB" == tag || "WIFE" == tag || "CHIL" == tag ||
         "DIV" == tag)
      {
         return true;
      }
      else
      {
         return false;
      }
      break;
   case 2:
      if ("DATE" == tag)
      {
         return true;
      }
      else
      {
         return false;
      }
      break;
   }

   return false;
}