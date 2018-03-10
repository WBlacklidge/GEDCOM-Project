/*
* @file
* @author William Blacklidge 
* @date 01/30/2018
* @brief This class impelements a GEDCOM Individual.
*/
#include "GedcomIndividual.h"
using namespace Utils::Gedcom;

#include <iostream>

GedcomIndividual::GedcomIndividual(std::string id,
   std::string name,
   bool genderFemale,
   std::string birthday,
   unsigned int age,
   bool isAlive,
   std::string deathday,
   std::string childIds,
   std::string spouseId) :
   m_id(id),
   m_name(name),
   m_genderFemale(genderFemale),
   m_birthday(birthday),
   m_age(age),
   m_isAlive(isAlive),
   m_deathday(deathday),
   m_childIds(childIds),
   m_spouseId(spouseId)
{
}

std::ostream& Utils::Gedcom::operator<<(std::ostream& os,
   const GedcomIndividual& indv)
{
   os << "--------------------------------------------------------------------------------------------------------------\n";
   os << indv.m_id << "\t";
   os << indv.m_name << "\t";
   const char gender_char = indv.m_genderFemale ? 'F' : 'M';
   os << gender_char << "\t";
   os << indv.m_birthday << "\t\t";
   os << indv.m_age << "\t";
   const char alive_char = indv.m_isAlive ? 'Y' : 'N';
   os << alive_char << "\t";
   if (indv.m_deathday.size() <= 0)
   {
      os << "NA\t\t";
   }
   else
   {
      os << indv.m_deathday << "\t";
   }

   if (indv.m_childIds.size() <= 0)
   {
      os << "NA\t\t";
   }
   else
   {
      os << indv.m_childIds << "\t\t";
   }

   if (indv.m_spouseId.size() <= 0)
   {
      os << "NA\t\t";
   }
   else
   {
      os << indv.m_spouseId << "\t\t";
   }
   os << "--------------------------------------------------------------------------------------------------------------" << std::endl;
   return os;
}