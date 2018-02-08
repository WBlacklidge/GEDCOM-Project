/*
* @file
* @author William Blacklidge
* @date 01/30/2018
* @brief This class impelements a GEDCOM Family.
*/
#include "GedcomFamily.h"
using namespace Utils::Gedcom;

#include "GedcomIndividual.h"

#include <map>
#include <iostream>

GedcomFamily::GedcomFamily(std::string id,
   std::string husbandId,
   std::string husbandName,
   std::string wifeId,
   std::string wifeName,
   std::vector<std::string> childIds,
   std::string marriageDate,
   std::string divorceDate) : m_id(id),
   m_husbandId(husbandId),
   m_husbandName(husbandName),
   m_wifeId(wifeId),
   m_wifeName(wifeName),
   m_childIds(childIds),
   m_marriageDate(marriageDate),
   m_divorceDate(divorceDate)
{
}

std::ostream& Utils::Gedcom::operator<<(std::ostream& os,
   const GedcomFamily& fam)
{
   os << "--------------------------------------------------------------------------------------------------------------" << std::endl;
   os << fam.m_id << "\t";
   if (fam.m_marriageDate.size() == 0)
   {
      os << "NA\t\t";
   }
   else
   {
      os << fam.m_marriageDate << "\t";
   }

   const std::string divorce_date = fam.m_divorceDate.size() == 0 ? "NA" : fam.m_divorceDate;
   os << divorce_date << "\t";
   os << fam.m_husbandId << "\t\t";
   os << fam.m_husbandName << "\t";
   os << fam.m_wifeId << "\t\t";
   os << fam.m_wifeName << "\t";

   if (0 == fam.m_childIds.size())
   {
      os << "   NA";
   }
   else
   {
      for (int child_itr = 0; child_itr < fam.m_childIds.size(); ++child_itr)
      {
         os << " " << fam.m_childIds[child_itr];
      }
   }

   std::cout << "\n--------------------------------------------------------------------------------------------------------------" << std::endl;

   return os;
}