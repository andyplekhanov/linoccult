//------------------------------------------------------------------------------
//
// File:    EtUtReader.cc
//
// Purpose: Read data from ET-UT file.
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

#include <sstream>

#include "EtUtReader.h"
#include "apsetutdata.h"
#include "apsmoduleetutreader.h"
#include "apstime.h"

namespace aps {

  namespace apsastroio {

const std::string end_of_header( "----------" );

//======================= EtUtReader ==========================

EtUtReader :: EtUtReader( APSSubModule * pSubModule, const std::string & pEtUtFilePath ) :
              APSIStrFile( pEtUtFilePath )
{
  pModule = new APSModuleEtUtReader( pSubModule );
}

EtUtReader :: ~EtUtReader( void )
{
  delete pModule;
}

bool EtUtReader :: ParseLine( const std::string & Str, int & Day, int & Month,
                                int & Year, double & Value ) const
{
  std::stringstream istrstream( Str );

  if( istrstream >> Day ) {
    if( istrstream >> Month ) {
      if( istrstream >> Year ) {
        if( istrstream >> Value ) {
          return( true );
        }
      }
    }
  }

  return( false );
}

bool EtUtReader :: CheckMjd( const APSEtUtData * pAPSEtUtData, const double Mjd ) const
{
  const std::map<double,double> Intervals = pAPSEtUtData->GetIntervals();

  std::map<double,double>::const_iterator p_min = Intervals.begin();

  if( p_min != Intervals.end() ) {
    std::map<double,double>::const_iterator p_max = Intervals.end();

    --p_max;

    if( Mjd <= p_max->first ) {
      return( false );
    }
  }

  return( true );
}

bool EtUtReader :: SkipHeader( void )
{
  std::string Str;

  while( GetStr( Str ) ) {
    if( Str.substr( 0, end_of_header.length() ) == end_of_header ) {
      return( true );
    }
  }

  return( false );
}

int EtUtReader :: Read( APSEtUtData * pAPSEtUtData )
{
  std::string Str;
  int         Count;
  int         RetCode = APS_ET_UT_READER_NO_ERROR;

  if( Open() ) {
    if( SkipHeader() ) {
      Count = 0;

      while( GetStr( Str ) ) {
        int    Day;
        int    Month;
        int    Year;
        double Value;

        Count++;

        if( ParseLine( Str, Day, Month, Year, Value ) ) {
          double Mjd = apsastroalg::Mjd( Year, Month, Day );

          if( !CheckMjd( pAPSEtUtData, Mjd ) ) {
            std::ostringstream Msg;
            Msg << Count << " line." << std::endl;
            pModule->ErrorMessage( APS_ET_UT_READER_SORT, Msg.str() );
            RetCode = APS_ET_UT_READER_SORT;
            break;
          }

          pAPSEtUtData->CreateValue( Mjd, Value );
        }
        else {
          std::ostringstream Msg;
          Msg << Count << " line." << std::endl;
          pModule->ErrorMessage( APS_ET_UT_READER_PARSE, Msg.str() );
          RetCode = APS_ET_UT_READER_PARSE;
          break;
        }
      }

      //pModule->StrMessage( APS_ET_UT_READER_NEW_LINE );

      {
        std::ostringstream Msg;
        Msg << Count << " records." << std::endl;
        pModule->InfoMessage( APS_ET_UT_READER_FINISH_READING, Msg.str() );
      }
    }
    else {
      pModule->InfoMessage( APS_ET_UT_READER_SKIP_HEADER );
    }
  }
  else {
    pModule->ErrorMessage( APS_ET_UT_READER_OPEN_FILE );
    RetCode = APS_ET_UT_READER_OPEN_FILE;
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------

