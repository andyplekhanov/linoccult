//------------------------------------------------------------------------------
//
// File:    TaiUtcReader.cc
//
// Purpose: Read data from TAI-UTC file.
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

#include "TaiUtcReader.h"
#include "apstaiutcdata.h"
#include "apsmoduletaiutcreader.h"
#include "apstime.h"

namespace aps {

  namespace apsastroio {

const std::string end_of_header( "----------" );

//======================= TaiUtcReader ==========================

TaiUtcReader :: TaiUtcReader( APSSubModule * pSubModule, const std::string & pTaiUtcFilePath ) :
                APSIStrFile( pTaiUtcFilePath )
{
  pModule = new APSModuleTaiUtcReader( pSubModule );
}

TaiUtcReader :: ~TaiUtcReader( void )
{
  delete pModule;
}

bool TaiUtcReader :: ParseLine( const std::string & Str, int & Day, int & Month,
                                int & Year, int & Value ) const
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

bool TaiUtcReader :: CheckMjd( const APSTaiUtcData * pAPSTaiUtcData, const double Mjd ) const
{
  const std::map<double,int> Intervals = pAPSTaiUtcData->GetIntervals();

  std::map<double,int>::const_iterator p_min = Intervals.begin();

  if( p_min != Intervals.end() ) {
    std::map<double,int>::const_iterator p_max = Intervals.end();

    --p_max;

    if( Mjd <= p_max->first ) {
      return( false );
    }
  }

  return( true );
}

bool TaiUtcReader :: SkipHeader( void )
{
  std::string Str;

  while( GetStr( Str ) ) {
    if( Str.substr( 0, end_of_header.length() ) == end_of_header ) {
      return( true );
    }
  }

  return( false );
}

int TaiUtcReader :: Read( APSTaiUtcData * pAPSTaiUtcData )
{
  std::string Str;
  int         Count;
  int         RetCode = APS_TAI_UTC_READER_NO_ERROR;

  if( Open() ) {
    if( SkipHeader() ) {
      Count = 0;

      while( GetStr( Str ) ) {
        int Day;
        int Month;
        int Year;
        int Value;

        Count++;

        if( ParseLine( Str, Day, Month, Year, Value ) ) {
          double Mjd = apsastroalg::Mjd( Year, Month, Day );

          if( !CheckMjd( pAPSTaiUtcData, Mjd ) ) {
            std::ostringstream Msg;
            Msg << Count << " line." << std::endl;
            pModule->ErrorMessage( APS_TAI_UTC_READER_SORT, Msg.str() );
            RetCode = APS_TAI_UTC_READER_SORT;
            break;
          }

          pAPSTaiUtcData->CreateValue( Mjd, Value );
        }
        else {
          std::ostringstream Msg;
          Msg << Count << " line." << std::endl;
          pModule->ErrorMessage( APS_TAI_UTC_READER_PARSE, Msg.str() );
          RetCode = APS_TAI_UTC_READER_PARSE;
          break;
        }
      }

      //pModule->StrMessage( APS_TAI_UTC_READER_NEW_LINE );

      {
        std::ostringstream Msg;
        Msg << Count << " records." << std::endl;
        pModule->InfoMessage( APS_TAI_UTC_READER_FINISH_READING, Msg.str() );
      }
    }
    else {
      pModule->InfoMessage( APS_TAI_UTC_READER_SKIP_HEADER );
    }
  }
  else {
    pModule->ErrorMessage( APS_TAI_UTC_READER_OPEN_FILE );
    RetCode = APS_TAI_UTC_READER_OPEN_FILE;
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------

