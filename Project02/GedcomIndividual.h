#pragma once
#include <string>

namespace Utils
{
   namespace Gedcom
   {
      class GedcomIndividual
      {
      public:
         std::string m_id;
         std::string m_name;
         bool m_genderFemale;
         std::string m_birthday;
         unsigned int m_age;
         bool m_isAlive;
         std::string m_deathday;
         std::string m_child;
         std::string m_spouse;

         GedcomIndividual(std::string id,
            std::string name,
            bool genderFemale,
            std::string birthday,
            unsigned int age,
            bool isAlive,
            std::string deathday,
            std::string child,
            std::string spouse) :
            m_id(id),
            m_name(name),
            m_genderFemale(genderFemale),
            m_birthday(birthday),
            m_age(age),
            m_isAlive(isAlive),
            m_deathday(deathday),
            m_child(child),
            m_spouse(spouse)
         {
         }
      };
   }
}
