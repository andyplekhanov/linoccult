//------------------------------------------------------------------------------
//
// File:    loAppl.h
//
// Purpose: Asteroids occultation program for Linux
//          Header for LinOccult application
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 30.01.2004
//         version 0.2 22.02.2005 ReadEvents, WriteEvents were added
//         version 0.3 27.02.2005 WritePositions was added
//         version 0.4 15.03.2005 Sites reading was added
//         version 1.0 17.04.2005 Updates reading was added
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

#ifndef LIN_OCCULT_APPL_H
#define LIN_OCCULT_APPL_H

#include <string>

namespace aps {

  namespace apslinoccult {

class LOModuleAppl;
class LOData;

//======================= LinOccultAppl ==========================

class LinOccultAppl
{
  private:

    LOModuleAppl * pModule;

    int ReadUpdates( LOData * pLOData ) const;

    int ReadSites( LOData * pLOData ) const;

    int ReadEvents( LOData * pLOData ) const;

    int WriteEvents( LOData * pLOData ) const;

    int WritePositions( LOData * pLOData ) const;

  public:

    LinOccultAppl( const std::string & ProjectFilePath );

    virtual ~LinOccultAppl( void );

    int Run( void );
};

}}

#endif

//---------------------------- End of file ---------------------------
