#pragma once
/*
* @file
* @author William Blacklidge
* @date 01/30/2018
* @brief This class is for reading data from a GedcomFile.
*/
#include <fstream>
#include <string>
#include <map>
#include <cctype>

#include "GedcomObject.h"
#include "GedcomIndividual.h"
#include "GedcomFamily.h"

namespace Utils
{
   namespace Gedcom
   {
      class GedcomFile
      {
         /** The file. */
         std::fstream m_file;

         /** Current line number of the file. */
         int m_lineNumber;

         /** Data from the current line of the file. */
         std::vector<GedcomObject> m_fields;

         struct compare
         {
            bool operator()(std::string a, std::string b) const
            {
               // If they are different sizes we might have a variance
               // in number digits.
               std::string temp_a = a;
               std::string temp_b = b;
               if (a.size() != b.size())
               {
                  if (a.size() > b.size())
                  {
                     for (int i = 0; i < b.size(); ++i)
                     {
                        temp_b = b;
                        std::isdigit(static_cast<unsigned char>(temp_b[i]));
                        temp_b.insert(0, "0");
                     }
                  }
                  else if (b.size() > a.size())
                  {
                     for (int i = 0; i < a.size(); ++i)
                     {
                        temp_a = a;
                        std::isdigit(static_cast<unsigned char>(temp_a[i]));
                        temp_a.insert(0, "0");
                     }
                  }
               }

               return (temp_a.compare(temp_b) < 0);
            }
         };

         /** Data from the current line of the file. */
         std::map<std::string, GedcomFamily, compare> m_families;

         /** Data from the current line of the file. */
         std::map<std::string, GedcomIndividual, compare> m_individuals;

         /** Open a Gedcom File.
         * @return True if the file was opened successfully.
         * @param filename The name of the file to open.
         */
         bool open(const std::string& filename);

      public:
         /** Constructor.
         * @param filename The name of the file to open.
         * @param hasColumnHeaders Indicates the file has column headers.
         */
         GedcomFile(const std::string& filename);

         /** Read a line of data from the file.
         * @return False if the end of file was reached.
         */
         bool readLines();

         /** Print all the lines that have been read and unprocessed. */
         void printfile() const;

         /** Print all of the individuals in order by their ID. */
         void printIndividualsInDescendingId() const;

         /** Print all of the families in order by their ID. */
         void printFamiliesInDescendingId() const;

		 /** Print all of the individuals with upcoming birthdays. */
		 void printIndividualsUpcomingBirthdays() const;

		 /** Print all of the individuals with upcoming Annivarsaries. */
		 void printIndividualsUpcomingAnnivarsaries() const;

		 /** Print all of the individuals Deceased. */
		 void printIndividualsDeceased() const;

         /** Close the file. */
         void close();

         /** Destructor. */
         ~GedcomFile();
      };
   }
}