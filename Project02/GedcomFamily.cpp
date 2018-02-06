/*
* @file
* @author William Blacklidge
* @date 01/30/2018
* @brief This class impelements a GEDCOM Family.
*/
#include "GedcomFamily.h"
using namespace Utils::Gedcom;

GedcomFamily::GedcomFamily(std::string id,
   std::string husbandId,
   std::string wifeId,
   std::vector<std::string> childIds,
   std::string marriageDate,
   std::string divorceDate) : m_id(id),
   m_husbandId(husbandId),
   m_wifeId(wifeId),
   m_childIds(childIds),
   m_marriageDate(marriageDate),
   m_divorceDate(divorceDate)
{
}