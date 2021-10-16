//------------------------------------------------------------------------------
//
// File:    TychoWriter.h
//
// Purpose: Tycho2 star catalog writer.
//   
// (c) 2006 Plekhanov Andrey
//
// Initial version 0.1 12.02.2006
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

#ifndef TYCHO_WRITER_H
#define TYCHO_WRITER_H

#include <string>

#include "apsobinastroio.h"

namespace aps {

  namespace apsastroio {

//======================= TychoWriter ==========================

class TychoWriter : protected APSOBinAstroIO
{
  protected:

    int PutRA( int RA ) const;

    int PutpmRA( float pmRA ) const;

    int PutDec( int Dec ) const;

    int PutpmDec( float pmDec ) const;

    int PutParallax( short Parallax ) const;

    int PutMv( short Mv ) const;

    int PutMp( short Mp ) const;

    int PutCatalogue( unsigned char Catalogue ) const;

    int PutStarCatalogNumber( int Number ) const;

  public:

    TychoWriter( const std::string & pTychoFilePath );

    virtual ~TychoWriter( void );
};

}}

#endif

//---------------------------- End of file ---------------------------
