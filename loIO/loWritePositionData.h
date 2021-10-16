//------------------------------------------------------------------------------
//
// File:    loWritePositionData.h
//
// Purpose: Class for writing position events data base for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 27.02.2005
//         version 0.2 20.04.2005 HTML output
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//------------------------------------------------------------------------------

#ifndef LO_WRITE_POSITION_DATA_H
#define LO_WRITE_POSITION_DATA_H

#include <string>

#include "apssort.h"

namespace aps {

  namespace apslib {
    class APSOStrFile;
  }

  namespace apslinoccult {

using apslib::APSOStrFile;
using apsmathlib::APSSort;

class LOData;
class LOPos;
class LOPointEvent;
class LOEventPosWriterSubModule;
class LOModuleEventPosWriter;

//========================= PointEventSort =============================

class PointEventSort : public APSSort
{
  private:

    int Compare( const void * pPtr1, const void * pPtr2, const int Type ) const;

  public:

    PointEventSort( void );

    virtual ~PointEventSort( void );
};

//======================= LOWritePositionData ==========================

class LOWritePositionData
{
  private:

    LOModuleEventPosWriter * pModule;

    const std::string GetSortName( const int Type ) const;

    int WriteMainTextHeader( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                             const unsigned int Number ) const;

    int WriteTextHeader( APSOStrFile * pOutputFile ) const;

    int WriteTextStr( const LOPointEvent * pLOPointEvent, APSOStrFile * pOutputFile ) const;

    int WriteTextFooter( APSOStrFile * pOutputFile ) const;

    int WriteTextTableBody( APSOStrFile * pOutputFile, const LOPointEvent ** ppLOPointEventArray,
                            const unsigned int Number, const int Type ) const;

    int WriteTextBody( const LOPos * pLOPos, APSOStrFile * pOutputFile,
                       const LOPointEvent ** ppLOPointEventArray, const unsigned int Number ) const;

    int WriteMainTextFooter( const LOPos * pLOPos, APSOStrFile * pOutputFile ) const;

    int WriteMainPDFHeader( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                            const unsigned int Number ) const;

    int WritePDFHeader( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                        const int Table, const int Page, const int Type ) const;

    int WritePDFStr( const LOPointEvent * pLOPointEvent, APSOStrFile * pOutputFile ) const;

    int WritePDFFooter( APSOStrFile * pOutputFile ) const;

    int WriteOnePDFTable( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                          const LOPointEvent ** ppLOPointEventArray, const unsigned int Number,
                          const int Type, const int Table, const unsigned int Page ) const;

    int WritePDFTableBody( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                           const LOPointEvent ** ppLOPointEventArray, const unsigned int Number,
                           const int Type, const int Table ) const;

    int WritePDFBody( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                      const LOPointEvent ** ppLOPointEventArray, const unsigned int Number ) const;

    int WriteMainPDFFooter( const LOPos * pLOPos, APSOStrFile * pOutputFile ) const;

    int WriteMainHTMLHeader( APSOStrFile * pOutputFile ) const;

    int WriteHTMLBody( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                       const LOPointEvent ** ppLOPointEventArray, const unsigned int Number ) const;

    int WriteMainHTMLFooter( APSOStrFile * pOutputFile ) const;

    int WriteTextFile( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                       const LOPointEvent ** ppLOPointEventArray, const unsigned int Number ) const;

    int WritePDFFile( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                      const LOPointEvent ** ppLOPointEventArray, const unsigned int Number ) const;

    int WriteHTMLFile( const LOPos * pLOPos, APSOStrFile * pOutputFile, const std::string & ProgramName,
                       const LOPointEvent ** ppLOPointEventArray, const unsigned int Number ) const;

    int ProcessOnePosition( const LOPos * pLOPos, const std::string & ProgramName ) const;

  public:

    LOWritePositionData( LOEventPosWriterSubModule * pLOEventPosWriterSubModule );

    virtual ~LOWritePositionData( void );

    int Write( LOData * pLOData );
};

}}

#endif

//---------------------------- End of file ---------------------------


