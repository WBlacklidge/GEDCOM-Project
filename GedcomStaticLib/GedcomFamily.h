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
         /** The name of the husband belonging to this family. */
         std::string m_husbandName;
         /** The ID of the wife belonging to this family. */
         std::string m_wifeId;
         /** The name of the wife belonging to this family. */
         std::string m_wifeName;
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
            std::string husbandName,
            std::string wifeId,
            std::string wifeName,
            std::vector<std::string> childIds,
            std::string marriageDate,
            std::string divorceDate);
      };

      /** Overloads the << operator for easier printing.
      * @return output stream
      * @param os output stream
      * @param indv The individual that is being printed. */
      std::ostream& operator<<(std::ostream& os,
         const GedcomFamily& indv);
   }
}
