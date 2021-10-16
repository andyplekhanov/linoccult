//------------------------------------------------------------------------------
//
// File:    apstaiutcdata.h
//
// Purpose: TAI-UTC data base.
//   
// (c) Plekhanov Andrey
//
// Initial version 0.1
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

#ifndef APS_TAI_UTC_DATA_H
#define APS_TAI_UTC_DATA_H

#include <iostream>
#include <map>

namespace aps {

  namespace apslib {
    class APSSubModule;
  }

  namespace apsastrodata {

using apslib::APSSubModule;

class APSModuleTaiUtcData;

//======================== APSTaiUtcData ==========================

class APSTaiUtcData
{
  private:

    APSModuleTaiUtcData  * pModule;
    std::map<double,int>   Intervals;

  public:

    APSTaiUtcData( APSSubModule * pAPSSubModule );

    virtual ~APSTaiUtcData( void );

    void CreateValue( const double Mjd, const int TaiUtc );

    int GetValue( const double Mjd, int & Value ) const;

    const std::map<double,int> & GetIntervals( void ) const
      { return( Intervals ); }

    std::ostream & Print( std::ostream& s ) const;
};

}}

#endif

//---------------------------- End of file ---------------------------
