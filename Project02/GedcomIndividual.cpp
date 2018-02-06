/*
* @file
* @author William Blacklidge
* @date 01/30/2018
* @brief This class impelements a GEDCOM Individual.
*/
#include "GedcomIndividual.h"
using namespace Utils::Gedcom;

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