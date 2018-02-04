#pragma once
#include <string>
#include <vector>

namespace Utils
{
   namespace Gedcom
   {
      class GedcomFamily
      {
      public:
         std::string m_id;
         std::string m_husbandId;
         std::string m_wifeId;
         std::vector<std::string> m_childIds;
         std::string m_marriageDate;
         std::string m_divorceDate;
         
         GedcomFamily(std::string id,
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
      };
   }
}
