//------------------------------------------------------------------------------
//
// File:    apstaiutcdata.cc
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

#include "apstaiutcdata.h"
#include "apsmoduletaiutcdata.h"

namespace aps {

  namespace apsastrodata {

//======================= APSTaiUtcData ==========================

APSTaiUtcData :: APSTaiUtcData( APSSubModule * pAPSSubModule )
{
  pModule = new APSModuleTaiUtcData( pAPSSubModule );
}

APSTaiUtcData :: ~APSTaiUtcData( void )
{
  delete pModule;
}

void APSTaiUtcData :: CreateValue( const double Mjd, const int TaiUtc )
{
  std::pair<double,int> Pair = std::make_pair( Mjd, TaiUtc );
          
  Intervals.insert( Pair );
}

int APSTaiUtcData :: GetValue( const double Mjd, int & Value ) const
{
  int RetCode = APS_TAI_UTC_DATA_NO_ERROR;

  std::map<double,int>::const_iterator p = Intervals.upper_bound( Mjd );

  if( p != Intervals.end() ) {
    std::map<double,int>::const_iterator p1 = p;

    if( p1 != Intervals.begin() ) {
      --p1;

      Value = p1->second;
    }
    else {
      pModule->ErrorMessage( APS_TAI_UTC_DATA_LESS );    
      RetCode = APS_TAI_UTC_DATA_LESS;
    }
  }
  else {
    pModule->ErrorMessage( APS_TAI_UTC_DATA_MORE );    
    RetCode = APS_TAI_UTC_DATA_MORE;
  }

  return( RetCode );
}

std::ostream & APSTaiUtcData :: Print( std::ostream& s ) const
{
  s << "-------------- TaiUtcData begin ---------------" << std::endl;

  for( std::map<double,int>::const_iterator p = Intervals.begin();
       p != Intervals.end(); ++p ) {
    s << p->first << " " << p->second << std::endl;
  }

  s << "-------------- TaiUtcData end ---------------" << std::endl << std::endl;

  return( s );
}

}}

//---------------------------- End of file ---------------------------
