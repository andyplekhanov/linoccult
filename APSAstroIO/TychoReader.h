//------------------------------------------------------------------------------
//
// File:    TychoReader.h
//
// Purpose: Tycho2 star catalog reader.
//          Read data from Tycho2.dat.
//   
// (c) 2004 Plekhanov Andrey
//
// Initial version 0.1 24.02.2004
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

#ifndef TYCHO_READER_H
#define TYCHO_READER_H

#include <string>

#include "apsibinastroio.h"

namespace aps {

  namespace apsastroio {

//======================= TychoReader ==========================

class TychoReader : protected APSIBinAstroIO
{
  protected:

    int ReadStar( void );

    int GetStarsNumber( off_t & StarsNumber ) const;

    int GetRA( int & pRA ) const;

    int GetpmRA( float & ppmRA ) const;

    int GetDec( int & pDec ) const;

    int GetpmDec( float & ppmDec ) const;

    int GetParallax( short & pParallax ) const;

    int GetMv( short & pMv ) const;

    int GetMp( short & pMp ) const;

    int GetCatalogue( unsigned char & pCatalogue ) const;

    int GetStarCatalogNumber( int & pNumber ) const;

  public:

    TychoReader( const std::string & pTychoFilePath );

    virtual ~TychoReader( void );
};

}}

#endif

//---------------------------- End of file ---------------------------
