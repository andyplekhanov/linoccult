//------------------------------------------------------------------------------
//
// File:    loStar.h
//
// Purpose: Star data for LinOccult.
//   
// (c) 2004-2021 Plekhanov Andrey
//
// Initial version 0.1 15.02.2004
//         version 0.2 10.06.2004 Mv has been added
//         version 0.3 17.08.2005 Parallax was added
//         version 0.4 11.01.2021 Gaia EDR3. SupNum was removed.
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

#ifndef LO_STAR_H
#define LO_STAR_H

namespace aps {

  namespace apslinoccult {

//======================= LOStar ==========================

class LOStar
{
  private:

    double        RA;
    float         pmRA;
    double        Dec;
    float         pmDec;
    float         Parallax;
    float         Vrad;
    double        Epoch;
    unsigned char Catalogue;
    int           StarNumber;
    short         Mv; // Magnitude from Green photometer

  public:

    LOStar( const double aRA, const float apmRA, const double aDec,
            const float apmDec, const float aParallax, const float aVrad,
            const double aEpoch, const unsigned char aCatalogue,
            const int aStarNumber, const short aMv );

    virtual ~LOStar( void );

    double GetRA( void ) const
      { return( RA ); }

    float GetpmRA( void ) const
      { return( pmRA ); }

    double GetDec( void ) const
      { return( Dec ); }

    float GetpmDec( void ) const
      { return( pmDec ); }

    float GetParallax( void ) const
      { return( Parallax ); }

    float GetVrad( void ) const
      { return( Vrad ); }

    double GetEpoch( void ) const
      { return( Epoch ); }
    
    unsigned char GetCatalogue( void ) const
      { return( Catalogue ); }

    int GetStarNumber( void ) const
      { return( StarNumber ); }

    short GetMv( void ) const
      { return( Mv ); }

    //virtual void Print( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------


