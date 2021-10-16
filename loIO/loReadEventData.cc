//------------------------------------------------------------------------------
//
// File:    loReadEventData.cc
//
// Purpose: Class for reading occultation events data base for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 13.02.2005
//         version 0.2 22.02.2005 Start and end data were added
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
#include <iomanip>

#include "apsibinfile.h"
#include "apsmodule.h"
#include "apstime.h"
#include "loData.h"
#include "loEventData.h"
#include "loEvent.h"
#include "loReadEventData.h"
#include "loModuleEventDataReader.h"
#include "loEventDataReaderSubModule.h"

namespace aps {

  namespace apslinoccult {

static const int SHOW_EVENT_NUMBER   = 10000;

//======================= LOReadEventData ==========================

LOReadEventData :: LOReadEventData( LOEventDataReaderSubModule * pLOEventDataReaderSubModule,
                                    const std::string & EventDataFileName ) : LOAbsEventDataIO()
{
  pModule    = new LOModuleEventDataReader( pLOEventDataReaderSubModule );
  pInputFile = new APSIBinFile( EventDataFileName );  
}

LOReadEventData :: ~LOReadEventData( void )
{
  delete pModule;
  delete pInputFile;
}

int LOReadEventData :: ReadHeader( int & RecordsNumber ) const
{
  DescriptorType Descriptor;
  int            Version;
  int            Length;
  std::string    ProgramName;
  int            RetCode = LO_EVENT_DATA_READER_NO_ERROR;

  if( pInputFile->GetRecord( &Descriptor, sizeof( LOAbsEventDataIO :: Descriptor ) ) ) {
    if( Descriptor == LOAbsEventDataIO :: Descriptor ) {
      if( pInputFile->GetRecord( &Length, sizeof( Length ) ) ) {
        char * TmpStr = new char[ Length + 1 ];

        bool RetCode1 = pInputFile->GetRecord( TmpStr, Length );

        if( RetCode1 ) {
          TmpStr[ Length ] = 0x00;

          ProgramName = TmpStr;
        }

        delete [] TmpStr;

        if( RetCode1 ) {
          if( pInputFile->GetRecord( &Version, sizeof( Version ) ) ) {        
            if( Version == FILE_VERSION_1 ) {
              if( pInputFile->GetRecord( &RecordsNumber, sizeof( RecordsNumber ) ) ) {
                std::ostringstream Msg;
                Msg << "Program " << ProgramName << " version " << Version << " records number " <<
                       RecordsNumber << "." << std::endl;
                pModule->InfoMessage( LO_EVENT_DATA_READER_HEADER_INFO, Msg.str() );
              }
              else {
                pModule->ErrorMessage( LO_EVENT_DATA_READER_READ_ERROR );
                RetCode = LO_EVENT_DATA_READER_READ_ERROR;
              }
            }
            else {
              pModule->ErrorMessage( LO_EVENT_DATA_READER_WRONG_VERSION );
              RetCode = LO_EVENT_DATA_READER_WRONG_VERSION;
            }
          }
          else {
            pModule->ErrorMessage( LO_EVENT_DATA_READER_READ_ERROR );
            RetCode = LO_EVENT_DATA_READER_READ_ERROR;
          }
        }
        else {
          pModule->ErrorMessage( LO_EVENT_DATA_READER_READ_ERROR );
          RetCode = LO_EVENT_DATA_READER_READ_ERROR;
        }
      }
      else {
        pModule->ErrorMessage( LO_EVENT_DATA_READER_READ_ERROR );
        RetCode = LO_EVENT_DATA_READER_READ_ERROR;
      }
    }
    else {
      pModule->ErrorMessage( LO_EVENT_DATA_READER_WRONG_DESCRIPTOR );
      RetCode = LO_EVENT_DATA_READER_WRONG_DESCRIPTOR;
    }
  }
  else {
    pModule->ErrorMessage( LO_EVENT_DATA_READER_READ_ERROR );
    RetCode = LO_EVENT_DATA_READER_READ_ERROR;
  }

  return( RetCode );
}

int LOReadEventData :: ReadEvent( LOEventData * pLOEventData, int & Count,
                                  const double MjdStart, const double MjdEnd ) const
{
  int            i;
  int            AsteroidID;
  std::string    AsteroidName;
  double         Diameter;
  double         EphemerisUncertainty;
  double         ObservationEpoch;
  double         M;
  double         W;
  double         O;
  double         I;
  double         E;
  double         A;
  unsigned char  Catalog;
  int            StarNumber;
  short          Mv;
  short          ChebOrder;
  double       * pcX;
  double       * pcY;
  double       * pcZ;
  double         ET_UT;
  double         BeginOccTime;
  double         EndOccTime;
  int            EarthFlag;
  double         MaxDuration;
  double         StarRA;
  double         StarDec;
  double         MoonPhase;
  double         SunDist;
  double         MoonDist;
  double         Brightness;
  double         BrightDelta;
  double         Uncertainty;
  int            Length;

//---------------- AsteroidID -----------------

  if( !pInputFile->GetRecord( &AsteroidID, sizeof( AsteroidID ) ) ) {
    return( 1 );
  }

//---------------- AsteroidName -----------------

  if( !pInputFile->GetRecord( &Length, sizeof( Length ) ) ) {
    return( 1 );
  }

  if( Length ) {
    char * TmpStr = new char[ Length + 1 ];

    bool RetCode = pInputFile->GetRecord( TmpStr, Length );

    if( RetCode ) {
      TmpStr[ Length ] = 0x00;

      AsteroidName = TmpStr;
    }

    delete [] TmpStr;

    if( !RetCode ) {
      return( 1 );
    }
  }

//---------------- Diameter -----------------

  if( !pInputFile->GetRecord( &Diameter, sizeof( Diameter ) ) ) {
    return( 1 );
  }

//---------------- EphemerisUncertainty -----------------

  if( !pInputFile->GetRecord( &EphemerisUncertainty, sizeof( EphemerisUncertainty ) ) ) {
    return( 1 );
  }

//---------------- ObservationEpoch -----------------

  if( !pInputFile->GetRecord( &ObservationEpoch, sizeof( ObservationEpoch ) ) ) {
    return( 1 );
  }

//---------------- M -----------------

  if( !pInputFile->GetRecord( &M, sizeof( M ) ) ) {
    return( 1 );
  }

//---------------- W -----------------

  if( !pInputFile->GetRecord( &W, sizeof( W ) ) ) {
    return( 1 );
  }

//---------------- O -----------------

  if( !pInputFile->GetRecord( &O, sizeof( O ) ) ) {
    return( 1 );
  }

//---------------- I -----------------

  if( !pInputFile->GetRecord( &I, sizeof( I ) ) ) {
    return( 1 );
  }

//---------------- E -----------------

  if( !pInputFile->GetRecord( &E, sizeof( E ) ) ) {
    return( 1 );
  }

//---------------- A -----------------

  if( !pInputFile->GetRecord( &A, sizeof( A ) ) ) {
    return( 1 );
  }

//---------------- Catalog -----------------

  if( !pInputFile->GetRecord( &Catalog, sizeof( Catalog ) ) ) {
    return( 1 );
  }

//---------------- StarNumber -----------------

  if( !pInputFile->GetRecord( &StarNumber, sizeof( StarNumber ) ) ) {
    return( 1 );
  }

//---------------- Mv -----------------

  if( !pInputFile->GetRecord( &Mv, sizeof( Mv ) ) ) {
    return( 1 );
  }

//---------------- ChebOrder -----------------

  if( !pInputFile->GetRecord( &ChebOrder, sizeof( ChebOrder ) ) ) {
    return( 1 );
  }

//---------------- cX -----------------

  pcX = new double[ ChebOrder + 1 ];

  for( i = 0; i <= ChebOrder; i++ ) {
    if( !pInputFile->GetRecord( &pcX[ i ], sizeof( pcX[ 0 ] ) ) ) {
      return( 1 );
    }
  }

//---------------- cY -----------------

  pcY = new double[ ChebOrder + 1 ];

  for( i = 0; i <= ChebOrder; i++ ) {
    if( !pInputFile->GetRecord( &pcY[ i ], sizeof( pcY[ 0 ] ) ) ) {
      return( 1 );
    }
  }

//---------------- cZ -----------------

  pcZ = new double[ ChebOrder + 1 ];

  for( i = 0; i <= ChebOrder; i++ ) {
    if( !pInputFile->GetRecord( &pcZ[ i ], sizeof( pcZ[ 0 ] ) ) ) {
      return( 1 );
    }
  }

//---------------- ET_UT -----------------

  if( !pInputFile->GetRecord( &ET_UT, sizeof( ET_UT ) ) ) {
    return( 1 );
  }

//---------------- BeginOccTime -----------------

  if( !pInputFile->GetRecord( &BeginOccTime, sizeof( BeginOccTime ) ) ) {
    return( 1 );
  }

//---------------- EndOccTime -----------------

  if( !pInputFile->GetRecord( &EndOccTime, sizeof( EndOccTime ) ) ) {
    return( 1 );
  }

//---------------- EarthFlag -----------------

  if( !pInputFile->GetRecord( &EarthFlag, sizeof( EarthFlag ) ) ) {
    return( 1 );
  }

//---------------- MaxDuration -----------------

  if( !pInputFile->GetRecord( &MaxDuration, sizeof( MaxDuration ) ) ) {
    return( 1 );
  }

//---------------- StarRA -----------------

  if( !pInputFile->GetRecord( &StarRA, sizeof( StarRA ) ) ) {
    return( 1 );
  }

//---------------- StarDec -----------------

  if( !pInputFile->GetRecord( &StarDec, sizeof( StarDec ) ) ) {
    return( 1 );
  }

//---------------- MoonPhase -----------------

  if( !pInputFile->GetRecord( &MoonPhase, sizeof( MoonPhase ) ) ) {
    return( 1 );
  }

//---------------- SunDist -----------------

  if( !pInputFile->GetRecord( &SunDist, sizeof( SunDist ) ) ) {
    return( 1 );
  }

//---------------- MoonDist -----------------

  if( !pInputFile->GetRecord( &MoonDist, sizeof( MoonDist ) ) ) {
    return( 1 );
  }

//---------------- Brightness -----------------

  if( !pInputFile->GetRecord( &Brightness, sizeof( Brightness ) ) ) {
    return( 1 );
  }

//---------------- BrightDelta -----------------

  if( !pInputFile->GetRecord( &BrightDelta, sizeof( BrightDelta ) ) ) {
    return( 1 );
  }

//---------------- Uncertainty -----------------

  if( !pInputFile->GetRecord( &Uncertainty, sizeof( Uncertainty ) ) ) {
    return( 1 );
  }

  if( IfInInterval( MjdStart, MjdEnd, BeginOccTime, EndOccTime ) ) {
    pLOEventData->CreateEvent( AsteroidID, AsteroidName, Diameter, EphemerisUncertainty,
                               ObservationEpoch, M, W, O, I, E, A,
                               Catalog, StarNumber, Mv, ChebOrder,
                               pcX, pcY, pcZ, ET_UT,
                               BeginOccTime, EndOccTime, EarthFlag, MaxDuration,
                               StarRA, StarDec, MoonPhase, SunDist, MoonDist,
                               Brightness, BrightDelta, Uncertainty );
    Count++;
  }

  return( 0 );
}

int LOReadEventData :: Read( LOData * pLOData )
{
  int           i;
  int           Count;
  LOEventData * pLOEventData;
  double        MjdStart;
  double        MjdEnd;
  int           RecordsNumber;
  int           RetCode = LO_EVENT_DATA_READER_NO_ERROR;

  pLOEventData = pLOData->CreateEventData();

  if( pInputFile->Open() ) {
    if( !ReadHeader( RecordsNumber ) ) {
      {
      std::ostringstream Msg;
      Msg << RecordsNumber << " records. Start data " << pModule->GetStartYear() <<
             "/" << std::setfill( '0' ) << std::setw( 2 ) << pModule->GetStartMonth() <<
             "/" << std::setfill( '0' ) << std::setw( 2 ) << pModule->GetStartDay() <<
             " End data " << pModule->GetEndYear() <<
             "/" << std::setfill( '0' ) << std::setw( 2 ) << pModule->GetEndMonth() <<
             "/" << std::setfill( '0' ) << std::setw( 2 ) << pModule->GetEndDay() << "." << std::endl;

      pModule->InfoMessage( LO_EVENT_DATA_READER_START_READING, Msg.str() );
      }

      MjdStart = apsastroalg::Mjd( pModule->GetStartYear(), pModule->GetStartMonth(), pModule->GetStartDay() );
      MjdEnd = apsastroalg::Mjd( pModule->GetEndYear(), pModule->GetEndMonth(), pModule->GetEndDay() ) + 1.0;

      Count = 0;

      for( i = 0; i < RecordsNumber; i++ ) {
        RetCode = ReadEvent( pLOEventData, Count, MjdStart, MjdEnd );

        if( RetCode ) {
          pModule->ErrorMessage( LO_EVENT_DATA_READER_EVENT );
          RetCode = LO_EVENT_DATA_READER_EVENT;
          break;
        }

        if( !( i % SHOW_EVENT_NUMBER ) ) {
          pModule->StrMessage( LO_EVENT_DATA_READER_PROGRESS );
        }
      }

      pModule->StrMessage( LO_EVENT_DATA_READER_NEW_LINE );

      {
      std::ostringstream Msg;
      Msg << Count << " records." << std::endl;
      pModule->InfoMessage( LO_EVENT_DATA_READER_FINISH_READING, Msg.str() );
      }
    }
    else {
      pModule->ErrorMessage( LO_EVENT_DATA_READER_HEADER );
      RetCode = LO_EVENT_DATA_READER_HEADER;
    }

    pInputFile->Close();
  }
  else {
    pModule->ErrorMessage( LO_EVENT_DATA_READER_OPEN_FILE );
    RetCode = LO_EVENT_DATA_READER_OPEN_FILE;
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
