#pragma once
/*
* @file
* @author William Blacklidge
* @date 01/30/2018
* @brief This class defines a GEDCOM Individual.
*/

#include <string>

namespace Utils
{
   namespace Gedcom
   {
      /** This class will define all the attributes
      * of a GEDCOM Individual. */
      class GedcomIndividual
      {
      public:
         /** ID of the individual. */
         std::string m_id;
         /** Name of the individual. */
         std::string m_name;
         /** Whether or not the individual is female. If true this individual is a female.
         * If false this individual is a male. */
         bool m_genderFemale;
         /** Birthday in Day/Month/Year format. */
         std::string m_birthday;
         /** The age of the individual. */
         unsigned int m_age;
         /** Whether or not this individual is still alive. */
         bool m_isAlive;
         /** The day this individual died in Day/Month/Year format. 
         * This string will be empty if the individual is still alive. */
         std::string m_deathday;
         /** A string containing the IDs of the children. */
         std::string m_childIds;
         /** A string containing the ID of the spouse. */
         std::string m_spouseId;

         /** Constructor */
         GedcomIndividual(std::string id,
            std::string name,
            bool genderFemale,
            std::string birthday,
            unsigned int age,
            bool isAlive,
            std::string deathday,
            std::string childIds,
            std::string spouseId);
      };

      /** Overloads the << operator for easier printing.
      * @return output stream
      * @param os output stream
      * @param indv The individual that is being printed. */
      std::ostream& operator<<(std::ostream& os,
         const GedcomIndividual& indv);
  
   }
}
