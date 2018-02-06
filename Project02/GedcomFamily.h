#pragma once
/*
* @file
* @author William Blacklidge
* @date 01/30/2018
* @brief This class defines a GEDCOM Family.
*/

#include <string>
#include <vector>

namespace Utils
{
   namespace Gedcom
   {
      /** This class will define all the attributes
      * of a GEDCOM Family. */
      class GedcomFamily
      {
      public:
         /** The ID of the family. */
         std::string m_id;
         /** The ID of the husband belonging to this family. */
         std::string m_husbandId;
         /** The ID of the wife belonging to this family. */
         std::string m_wifeId;
         /** A vector containing a list of children belonging to this family. */
         std::vector<std::string> m_childIds;
         /** The date the husband and wife got married in Day/Month/Year format. */
         std::string m_marriageDate;
         /** The date the husband and wife got divorced in Day / Month / Year format.
         * This string will be empty if they never got divorced. */
         std::string m_divorceDate;

         /** Constructor. */
         GedcomFamily(std::string id,
            std::string husbandId,
            std::string wifeId,
            std::vector<std::string> childIds,
            std::string marriageDate,
            std::string divorceDate);
      };
   }
}
