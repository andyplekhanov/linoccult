//------------------------------------------------------------------------------
//
// File:    loReadUpdatesData.h
//
// Purpose: Class for reading updates data base for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 17.04.2005
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

#include "apsistrfile.h"
#include "apsmodule.h"
#include "loData.h"
#include "loUpdateData.h"
#include "loUpdate.h"
#include "loReadUpdatesData.h"
#include "loModuleUpdatesDataReader.h"
#include "loUpdatesDataReaderSubModule.h"

namespace aps {

  namespace apslinoccult {

const int SHOW_UPDATE_NUMBER = 100;

//======================= LOReadUpdatesData ==========================

LOReadUpdatesData :: LOReadUpdatesData( LOUpdatesDataReaderSubModule * pLOUpdatesDataReaderSubModule,
                                        const std::string & UpdatesDataFileName )
{
  pModule    = new LOModuleUpdatesDataReader( pLOUpdatesDataReaderSubModule );
  pInputFile = new APSIStrFile( UpdatesDataFileName );  
}

LOReadUpdatesData :: ~LOReadUpdatesData( void )
{
  delete pModule;
  delete pInputFile;
}

bool LOReadUpdatesData :: ParseLine( const std::string & Str,
                                     std::string & sAsteroidID,
                                     std::string & sEpoch,
                                     std::string & sMeanAnomaly,
                                     std::string & sPericenter,
                                     std::string & sLongNode,
                                     std::string & sInclination,
                                     std::string & sEccenticity,
                                     std::string & sSemimajorAxis,
                                     std::string & sMajor,
                                     std::string & sMinor,
                                     std::string & sPA ) const
{
  std::stringstream istrstream( Str );
  std::string       NullParam;

  if( istrstream >> sAsteroidID ) {
    if( istrstream >> sEpoch ) {
      if( istrstream >> sMeanAnomaly ) {
        if( istrstream >> sPericenter ) {
          if( istrstream >> sLongNode ) {
            if( istrstream >> sInclination ) {
              if( istrstream >> sEccenticity ) {
                if( istrstream >> sSemimajorAxis ) {
                  if( istrstream >> sMajor ) {
                    if( istrstream >> sMinor ) {
                      if( istrstream >> sPA ) {
                        if( !( istrstream >> NullParam ) ) {
                          return( true );
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  return( false );
}

int LOReadUpdatesData :: ReadUpdate( LOUpdateData * pLOUpdateData, const std::string & pStr, const int LineNumber ) const
{
  std::string  sAsteroidID;
  std::string  sEpoch;
  std::string  sMeanAnomaly;
  std::string  sPericenter;
  std::string  sLongNode;
  std::string  sInclination;
  std::string  sEccenticity;
  std::string  sSemimajorAxis;
  std::string  sMajor;
  std::string  sMinor;
  std::string  sPA;
  int          AsteroidID;
  double       ObservationEpoch;
  double       M;
  double       W;
  double       O;
  double       I;
  double       E;
  double       A;
  double       Major;
  double       Minor;
  double       PA;
  int          RetCode = 0;

  std::ostringstream Msg;
  Msg << "Line " << LineNumber << std::endl;

  if( ParseLine( pStr, sAsteroidID, sEpoch, sMeanAnomaly, sPericenter, sLongNode, sInclination,
                 sEccenticity, sSemimajorAxis, sMajor, sMinor, sPA ) ) {
    std::stringstream istrstream( sAsteroidID );

    if( istrstream >> AsteroidID ) {
      std::stringstream istrstream( sEpoch );

      if( istrstream >> ObservationEpoch ) {
        std::stringstream istrstream( sMeanAnomaly );

        if( istrstream >> M ) {
          std::stringstream istrstream( sPericenter );

          if( istrstream >> W ) {
            std::stringstream istrstream( sLongNode );

            if( istrstream >> O ) {
              std::stringstream istrstream( sInclination );

              if( istrstream >> I ) {
                std::stringstream istrstream( sEccenticity );

                if( istrstream >> E ) {
                  std::stringstream istrstream( sSemimajorAxis );

                  if( istrstream >> A ) {
                    std::stringstream istrstream( sMajor );

                    if( istrstream >> Major ) {
                      std::stringstream istrstream( sMinor );

                      if( istrstream >> Minor ) {
                        std::stringstream istrstream( sPA );

                        if( istrstream >> PA ) {
                          pLOUpdateData->CreateUpdate( AsteroidID, ObservationEpoch, M, W, O, I, E, A, Major, Minor, PA );
                        }
                        else {
                          pModule->ErrorMessage( LO_UPDATES_PA_READ, Msg.str() );
                          RetCode = LO_UPDATES_PA_READ;
                        }
                      }
                      else {
                        pModule->ErrorMessage( LO_UPDATES_MINOR_READ, Msg.str() );
                        RetCode = LO_UPDATES_MINOR_READ;
                      }
                    }
                    else {
                      pModule->ErrorMessage( LO_UPDATES_MAJOR_READ, Msg.str() );
                      RetCode = LO_UPDATES_MAJOR_READ;
                    }
                  }
                  else {
                    pModule->ErrorMessage( LO_UPDATES_SEMIMAJOR_AXIS_READ, Msg.str() );
                    RetCode = LO_UPDATES_SEMIMAJOR_AXIS_READ;
                  }
                }
                else {
                  pModule->ErrorMessage( LO_UPDATES_ECCENTRICITY_READ, Msg.str() );
                  RetCode = LO_UPDATES_ECCENTRICITY_READ;
                }
              }
              else {
                pModule->ErrorMessage( LO_UPDATES_INCLINATION_READ, Msg.str() );
                RetCode = LO_UPDATES_INCLINATION_READ;
              }
            }
            else {
              pModule->ErrorMessage( LO_UPDATES_LONG_NODE_READ, Msg.str() );
              RetCode = LO_UPDATES_LONG_NODE_READ;
            }
          }
          else {
            pModule->ErrorMessage( LO_UPDATES_PERICENTER_READ, Msg.str() );
            RetCode = LO_UPDATES_PERICENTER_READ;
          }
        }
        else {
          pModule->ErrorMessage( LO_UPDATES_MEAN_ANOMALY_READ, Msg.str() );
          RetCode = LO_UPDATES_MEAN_ANOMALY_READ;
        }
      }
      else {
        pModule->ErrorMessage( LO_UPDATES_EPOCH_READ, Msg.str() );
        RetCode = LO_UPDATES_EPOCH_READ;
      }
    }
    else {
      pModule->ErrorMessage( LO_UPDATES_ASTEROID_ID_READ, Msg.str() );
      RetCode = LO_UPDATES_ASTEROID_ID_READ;
    }
  }
  else {
    pModule->ErrorMessage( LO_UPDATES_DATA_READER_UPDATE, Msg.str() );
    RetCode = LO_UPDATES_DATA_READER_UPDATE;
  }

  return( RetCode );
}

int LOReadUpdatesData :: Read( LOData * pLOData )
{
  int            Count;
  int            LineNumber;
  LOUpdateData * pLOUpdateData;
  std::string    Str;
  int            RetCode = LO_UPDATES_DATA_READER_NO_ERROR;

  pLOUpdateData = pLOData->CreateUpdateData();

  if( pInputFile->Open() ) {
    pModule->InfoMessage( LO_UPDATES_DATA_READER_START_READING );

    Count = 0;

    LineNumber = 0;

    while( pInputFile->GetStr( Str ) ) {
      LineNumber++;

      if( ( Str[ 0 ] != '#') && ( !Str.empty() ) ) {
        RetCode = ReadUpdate( pLOUpdateData, Str, LineNumber );

        if( RetCode ) {
          pModule->ErrorMessage( LO_UPDATES_DATA_READER_READ_ERROR );
          RetCode = LO_UPDATES_DATA_READER_READ_ERROR;
          break;
        }

        if( !( Count % SHOW_UPDATE_NUMBER ) ) {
          pModule->StrMessage( LO_UPDATES_DATA_READER_PROGRESS );
        }

        Count++;
      }
    }

    pModule->StrMessage( LO_UPDATES_DATA_READER_NEW_LINE );

    std::ostringstream Msg;
    Msg << Count << " updates." << std::endl;
    pModule->InfoMessage( LO_UPDATES_DATA_READER_FINISH_READING, Msg.str() );

    pInputFile->Close();
  }
  else {
    pModule->ErrorMessage( LO_UPDATES_DATA_READER_OPEN_FILE );
    RetCode = LO_UPDATES_DATA_READER_OPEN_FILE;
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
