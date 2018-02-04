#pragma once
/*
* @file
* @author William Blacklidge
* @date 01/30/2018
* @brief This class is for reading data from a GedcomFile.
*/
#include <fstream>
#include <string>
#include <vector>

#include "GedcomObject.h"

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
         void print() const;

         /** Close the file. */
         void close();

         /** Destructor. */
         ~GedcomFile();
      };
   }
}