//------------------------------------------------------------------------------
//
// File:    UCAC2Reader.h
//
// Purpose: UCAC2 star catalog reader.
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

#ifndef UCAC2_READER_H
#define UCAC2_READER_H

#include <string>

#include "apsibinastroio.h"

namespace aps {

  namespace apsastroio {

//======================= TychoReader ==========================

class UCAC2Reader : protected APSIBinAstroIO
{
  protected:

    int GetStarsNumber( off_t & StarsNumber ) const;

    int GetRA( int & pRA ) const;

    int GetDec( int & pDec ) const;

    int GetU2Rmag( short & pU2Rmag ) const;

    int GetERAm( unsigned char & pERAm ) const;

    int GetEDEm( unsigned char & pEDEm ) const;

    int GetNObs( unsigned char & pNObs ) const;

    int GetEPos( unsigned char & pEPos ) const;

    int GetNCat( unsigned char & pNCat ) const;

    int GetCFLG( unsigned char & pCFLG ) const;

    int GetEpRAm( short & pEpRAm ) const;

    int GetEpDEm( short & pEpDEm ) const;

    int GetpmRA( int & ppmRA ) const;

    int GetpmDec( int & ppmDec ) const;

    int GetEpmRA( unsigned char & pEpmRA ) const;

    int GetEpmDE( unsigned char & pEpmDE ) const;

    int GetQpmRA( unsigned char & pQpmRA ) const;

    int GetQpmDE( unsigned char & pQpmDE ) const;

    int GetStarCatalogNumber( int & pNumber ) const;

    int Get2mJ( short & p2mJ ) const;

    int Get2mH( short & p2mH ) const;

    int Get2mKs( short & p2mKs ) const;

    int Get2mPh( unsigned char & p2mPh ) const;

    int Get2mCc( unsigned char & p2mCc ) const;

  public:

    UCAC2Reader( const std::string & pUCAC2FilePath );

    virtual ~UCAC2Reader( void );
};

}}

#endif

//---------------------------- End of file ---------------------------
