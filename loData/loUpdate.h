//------------------------------------------------------------------------------
//
// File:    loUpdate.h
//
// Purpose: Data for storing update in LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 16.04.2005
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

#ifndef LO_UPDATE_H
#define LO_UPDATE_H

namespace aps {

  namespace apslinoccult {

//======================= LOUpdate ==========================

class LOUpdate
{
  private:

    int        AsteroidID;
    double     ObservationEpoch;
    double     M;
    double     W;
    double     O;
    double     I;
    double     E;
    double     A;
    double     Major;
    double     Minor;
    double     PA;
    LOUpdate * pNext;

  public:

    LOUpdate( const int aAsteroidID, const double aObservationEpoch,
              const double aM, const double aW, const double aO,
              const double aI, const double aE, const double aA,
              const double aMajor, const double aMinor,
              const double aPA, LOUpdate * apNext );

    virtual ~LOUpdate( void );

    LOUpdate * GetNextUpdatePtr( void ) const
      { return( pNext ); }

    int GetAsteroidID( void ) const
      { return( AsteroidID ); }

    double GetObservationEpoch( void ) const
      { return( ObservationEpoch ); }

    double GetM( void ) const
      { return( M ); }

    double GetW( void ) const
      { return( W ); }

    double GetO( void ) const
      { return( O ); }

    double GetI( void ) const
      { return( I ); }

    double GetE( void ) const
      { return( E ); }

    double GetA( void ) const
      { return( A ); }

    double GetMajor( void ) const
      { return( Major ); }

    double GetMinor( void ) const
      { return( Minor ); }

    double GetPA( void ) const
      { return( PA ); }

    //virtual void Print( void ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
