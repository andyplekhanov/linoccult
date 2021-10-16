//------------------------------------------------------------------------------
//
// File:    apstaiutcdata.cc
//
// Purpose: ET-UT data base.
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

#include "apsetutdata.h"
#include "apsmoduleetutdata.h"

namespace aps {

  namespace apsastrodata {

//======================= APSEtUtData ==========================

APSEtUtData :: APSEtUtData( APSSubModule * pAPSSubModule )
{
  pModule = new APSModuleEtUtData( pAPSSubModule );
}

APSEtUtData :: ~APSEtUtData( void )
{
  delete pModule;
}

void APSEtUtData :: CreateValue( const double Mjd, const double EtUt )
{
  std::pair<double,double> Pair = std::make_pair( Mjd, EtUt );
          
  Intervals.insert( Pair );
}

int APSEtUtData :: GetValue( const double Mjd, double & Value ) const
{
  int RetCode = APS_ET_UT_DATA_NO_ERROR;

  std::map<double,double>::const_iterator p_max = Intervals.upper_bound( Mjd );

  if( p_max != Intervals.end() ) {
    std::map<double,double>::const_iterator p_min = p_max;

    if( p_min != Intervals.begin() ) {
      --p_min;

      double c1 = ( p_max->first - Mjd ) / ( p_max->first - p_min->first );

      double c2 = 1.0 - c1;

      Value = c1 * p_min->second + c2 * p_max->second;
    }
    else {
      pModule->ErrorMessage( APS_ET_UT_DATA_LESS );    
      RetCode = APS_ET_UT_DATA_LESS;
    }
  }
  else {
    pModule->ErrorMessage( APS_ET_UT_DATA_MORE );    
    RetCode = APS_ET_UT_DATA_MORE;
  }

  return( RetCode );
}

std::ostream & APSEtUtData :: Print( std::ostream& s ) const
{
  s << "-------------- EtUtData begin ---------------" << std::endl;

  for( std::map<double,double>::const_iterator p = Intervals.begin();
       p != Intervals.end(); ++p ) {
    s << p->first << " " << p->second << std::endl;
  }

  s << "-------------- EtUtData end ---------------" << std::endl << std::endl;

  return( s );
}

}}

//---------------------------- End of file ---------------------------
