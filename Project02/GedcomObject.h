#pragma once
/*
* @file
* @author William Blacklidge
* @date 01/30/2018
* @brief This class defines a Gedcom Object.
*/
#include <string>

namespace Utils
{
   namespace Gedcom
   {
      /** Where in the array of strings this tag is located. */
      enum tags
      {
         e_individualId = 0,
         e_name,
         e_sex,
         e_birthOfIndividual,
         e_deathOfIndividual,
         e_individualIsChildInFam,
         e_individualIsSpouseInFam,
         e_family,
         e_marriageEvent,
         e_husbandInFam,
         e_wifeInFam,
         e_childInFam,
         e_divorceEvent,
         e_dateOfEvent,
         e_header,
         e_trailer,
         e_note,
         e_end /** This is the end of the tags. */
      };

      /** Array with string representations of the tags. */
      static const char* sc_tagsString[]{ "INDI", "NAME", "SEX", "BIRT", "DEAT",
         "FAMC", "FAMS", "FAM", "MARR", "HUSB", "WIFE", "CHIL", "DIV", "DATE", "HEAD",
         "TRLR", "NOTE" };

      class GedcomObject
      {
      public:
         /** Constructor
         * @param line The line to parse */
         GedcomObject(std::string& line,
            unsigned int lineNumber);

         /** Destructor */
         ~GedcomObject();

         /** Print a parsed GedcomObject. */
         void printParsed() const;

         /** Print the original string. */
         void printOriginal() const;

         /** Returns a copy of the ID 
         * @return The ID in string format.*/
         std::string getId() const;

         /** Accessor to return the level as a value 
         * @return The level */
         int getLevel() const;

         /** Accesor to return the tag as a value. 
         * @return The tag in string format.*/
         std::string getTag() const;

         /** Will check if the tag is indvidual or family.
         * @return True if INDI or FAM false if not. */
         bool isIndiOrFam() const;

         /** Will check if the passed in string is a valid tag.*/
         bool isValidTag() const;

         /** Get arguements */
         std::string getArguements() const;

         /** Get the line number
         * @return the line number this GEDCOM object was a created from. */
         unsigned int getLineNumber() const;

      private:
         /** Parse the string. */
         void parse();

         /** The unprocessed string read from the file. */
         std::string m_rawLine;

         /** Level of the input line. */
         unsigned int m_level;

         /** The unique identifier used to identify an individual or a family. */
         std::string m_id;

         /** The tag associated with the line ("INDI, "FAM", DATE") */
         std::string m_tag;

         /** Whether or not this is a valid GEDCOM entry. */
         bool m_isValid;

         /** The rest of the line beyond the level and tag. */
         std::string m_arguments;

         /** The line number this gedcom object was a created from. */
         unsigned int m_lineNumber;

         /** Will check that the tag and and level are compatible.
         * @param tag The string tag.
         * @param evel The integer level.
         * @return True if compatable false if not. */
         bool isTagCompatableWithLevel(const std::string& tag,
            const int level) const;
      };
   }
}