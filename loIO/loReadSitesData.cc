//------------------------------------------------------------------------------
//
// File:    loReadSitesData.h
//
// Purpose: Class for reading sites data base for LinOccult.
//   
// (c) 2005 Plekhanov Andrey
//
// Initial version 0.1 14.03.2005
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
#include "apsangle.h"
#include "loData.h"
#include "loPosData.h"
#include "loPos.h"
#include "loReadSitesData.h"
#include "loModuleSitesDataReader.h"
#include "loSitesDataReaderSubModule.h"

namespace aps {

  namespace apslinoccult {

//======================= LOReadSitesData ==========================

LOReadSitesData :: LOReadSitesData( LOSitesDataReaderSubModule * pLOSitesDataReaderSubModule,
                                    const std::string & SitesDataFileName )
{
  pModule    = new LOModuleSitesDataReader( pLOSitesDataReaderSubModule );
  pInputFile = new APSIStrFile( SitesDataFileName );  
}

LOReadSitesData :: ~LOReadSitesData( void )
{
  delete pModule;
  delete pInputFile;
}

int LOReadSitesData :: GetCoord( const std::string & pStr, float & Coord ) const
{
  std::string            Str( pStr );
  std::string::size_type Pos1;
  std::string::size_type Pos2;
  std::string::size_type Pos3;
  int                    D;
  int                    M;
  double                 S;
  int                    RetCode = 0;

  Pos1 = Str.find_first_of( 'o' );

  Pos2 = Str.find_first_of( '\'' );

  Pos3 = Str.find_first_of( '"' );

  if( ( Pos1 == std::string::npos ) && ( Pos2 == std::string::npos ) && ( Pos3 == std::string::npos ) ) {
    std::stringstream istrstream( Str );

    if( !( istrstream >> Coord ) ) {
      RetCode = 1;
    }
  }
  else {
    if( ( Pos1 != std::string::npos ) && ( Pos2 != std::string::npos ) &&
        ( Pos3 != std::string::npos ) && ( Pos2 > Pos1 ) && ( Pos3 > Pos2 ) ) {
      Str[ Pos1 ] = ' ';
      Str[ Pos2 ] = ' ';
      Str[ Pos3 ] = ' ';

      std::stringstream istrstream( Str );

      if( istrstream >> D ) {
        if( istrstream >> M ) {
          if( istrstream >> S ) {
            Coord = apsmathlib::Ddd( D, M, S );
          }
          else {
            RetCode = 5;
          }
        }
        else {
          RetCode = 4;
        }
      }
      else {
        RetCode = 3;
      }
    }
    else {
      RetCode = 2;
    }
  }

  return( RetCode );
}

bool LOReadSitesData :: ParseLine( const std::string & Str,
                                   std::string & ObsName,
                                   std::string & EMail,
                                   std::string & sOutputFiles,
                                   std::string & sSort,
                                   std::string & sObserverLongitude,
                                   std::string & sObserverLatitude,
                                   std::string & sMaxDistance,
                                   std::string & sMaxMv,
                                   std::string & sMinDuration,
                                   std::string & sSunElev,
                                   std::string & sMinDrop,
                                   std::string & sMinProb,
                                   std::string & sMinCenterProb,
                                   std::string & sMinStarElev ) const
{
  std::stringstream istrstream( Str );
  std::string       NullParam;

  if( istrstream >> ObsName ) {
    if( istrstream >> EMail ) {
      if( istrstream >> sOutputFiles ) {
        if( istrstream >> sSort ) {
          if( istrstream >> sObserverLongitude ) {
            if( istrstream >> sObserverLatitude ) {
              if( istrstream >> sMaxDistance ) {
                if( istrstream >> sMaxMv ) {
                  if( istrstream >> sMinDuration ) {
                    if( istrstream >> sSunElev ) {
                      if( istrstream >> sMinDrop ) {
                        if( istrstream >> sMinProb ) {
                          if( istrstream >> sMinCenterProb ) {
                            if( istrstream >> sMinStarElev ) {
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
      }
    }
  }

  return( false );
}

int LOReadSitesData :: ReadSite( LOPosData * pLOPosData, const std::string & pStr, const int LineNumber ) const
{
  std::string  ObsName;
  std::string  EMail;
  std::string  sOutputFiles;
  std::string  sSort;
  std::string  sObserverLongitude;
  std::string  sObserverLatitude;
  std::string  sMaxDistance;
  std::string  sMaxMv;
  std::string  sMinDuration;
  std::string  sSunElev;
  std::string  sMinDrop;
  std::string  sMinProb;
  std::string  sMinCenterProb;
  std::string  sMinStarElev;
  unsigned int OutputFiles;
  unsigned int Sort;
  float        ObserverLongitude;
  float        ObserverLatitude;
  double       MaxDistance;
  float        MaxMv;
  double       MinDuration;
  double       SunElev;
  double       MinDrop;
  double       MinProb;
  double       MinCenterProb;
  double       MinStarElev;
  int          RetCode = 0;

  std::ostringstream Msg;
  Msg << "Line " << LineNumber << std::endl;

  if( ParseLine( pStr, ObsName, EMail, sOutputFiles, sSort, sObserverLongitude, sObserverLatitude,
                 sMaxDistance, sMaxMv, sMinDuration, sSunElev, sMinDrop, sMinProb, sMinCenterProb, sMinStarElev ) ) {
    std::stringstream istrstream( sOutputFiles );

    if( istrstream >> OutputFiles ) {
      std::stringstream istrstream1( sSort );

      if( istrstream1 >> Sort ) {
        if( !GetCoord( sObserverLongitude, ObserverLongitude ) ) {
          if( !GetCoord( sObserverLatitude, ObserverLatitude ) ) {
            std::stringstream istrstream2( sMaxDistance );

            if( istrstream2 >> MaxDistance ) {
              std::stringstream istrstream3( sMaxMv );

              if( istrstream3 >> MaxMv ) {
                std::stringstream istrstream4( sMinDuration );

                if( istrstream4 >> MinDuration ) {
                  std::stringstream istrstream5( sSunElev );

                  if( istrstream5 >> SunElev ) {
                    std::stringstream istrstream6( sMinDrop );

                    if( istrstream6 >> MinDrop ) {
                      std::stringstream istrstream7( sMinProb );

                      if( istrstream7 >> MinProb ) {
                        std::stringstream istrstream8( sMinCenterProb );

                        if( istrstream8 >> MinCenterProb ) {
                          std::stringstream istrstream9( sMinStarElev );

                          if( istrstream9 >> MinStarElev ) {
                            pLOPosData->CreatePosition( ObsName, EMail, OutputFiles, Sort, ObserverLongitude, ObserverLatitude,
                                                        MaxDistance, MaxMv, MinDuration, SunElev, MinDrop, MinProb, MinCenterProb, MinStarElev );
                          }
                          else {
                            pModule->ErrorMessage( LO_SITES_MIN_STAR_ELEV_READ, Msg.str() );
                            RetCode = LO_SITES_MIN_STAR_ELEV_READ;
                          }
                        }
                        else {
                          pModule->ErrorMessage( LO_SITES_MIN_CENTER_PROB_READ, Msg.str() );
                          RetCode = LO_SITES_MIN_CENTER_PROB_READ;
                        }
                      }
                      else {
                        pModule->ErrorMessage( LO_SITES_MIN_PROB_READ, Msg.str() );
                        RetCode = LO_SITES_MIN_PROB_READ;
                      }
                    }
                    else {
                      pModule->ErrorMessage( LO_SITES_MIN_DROP_READ, Msg.str() );
                      RetCode = LO_SITES_MIN_DROP_READ;
                    }
                  }
                  else {
                    pModule->ErrorMessage( LO_SITES_SUN_ELEV_READ, Msg.str() );
                    RetCode = LO_SITES_SUN_ELEV_READ;
                  }
                }
                else {
                  pModule->ErrorMessage( LO_SITES_MIN_DURATION_READ, Msg.str() );
                  RetCode = LO_SITES_MIN_DURATION_READ;
                }
              }
              else {
                pModule->ErrorMessage( LO_SITES_MAX_MV_READ, Msg.str() );
                RetCode = LO_SITES_MAX_MV_READ;
              }
            }
            else {
              pModule->ErrorMessage( LO_SITES_MAX_DISTANCE_READ, Msg.str() );
              RetCode = LO_SITES_MAX_DISTANCE_READ;
            }
          }
          else {
            pModule->ErrorMessage( LO_SITES_LATITUDE_READ, Msg.str() );
            RetCode = LO_SITES_LATITUDE_READ;
          }
        }
        else {
          pModule->ErrorMessage( LO_SITES_LONGITUDE_READ, Msg.str() );
          RetCode = LO_SITES_LONGITUDE_READ;
        }
      }
      else {
        pModule->ErrorMessage( LO_SITES_SORT_READ, Msg.str() );
        RetCode = LO_SITES_SORT_READ;
      }
    }
    else {
      pModule->ErrorMessage( LO_SITES_OUTPUT_FILES_READ, Msg.str() );
      RetCode = LO_SITES_OUTPUT_FILES_READ;
    }
  }
  else {
    pModule->ErrorMessage( LO_SITES_DATA_READER_SITE, Msg.str() );
    RetCode = LO_SITES_DATA_READER_SITE;
  }

  return( RetCode );
}

int LOReadSitesData :: Read( LOData * pLOData )
{
  int           Count;
  int           LineNumber;
  LOPosData   * pLOPosData;
  std::string   Str;
  int           RetCode = LO_SITES_DATA_READER_NO_ERROR;

  pLOPosData = pLOData->CreatePosData();

  if( pInputFile->Open() ) {
    pModule->InfoMessage( LO_SITES_DATA_READER_START_READING );

    Count = 0;

    LineNumber = 0;

    while( pInputFile->GetStr( Str ) ) {
      LineNumber++;

      if( ( Str[ 0 ] != '#') && ( !Str.empty() ) ) {
        RetCode = ReadSite( pLOPosData, Str, LineNumber );

        if( RetCode ) {
          pModule->ErrorMessage( LO_SITES_DATA_READER_READ_ERROR );
          RetCode = LO_SITES_DATA_READER_READ_ERROR;
          break;
        }

        Count++;
      }
    }

    pModule->StrMessage( LO_SITES_DATA_READER_NEW_LINE );

    std::ostringstream Msg;
    Msg << Count << " sites." << std::endl;
    pModule->InfoMessage( LO_SITES_DATA_READER_FINISH_READING, Msg.str() );

    pInputFile->Close();
  }
  else {
    pModule->ErrorMessage( LO_SITES_DATA_READER_OPEN_FILE );
    RetCode = LO_SITES_DATA_READER_OPEN_FILE;
  }

  return( RetCode );
}

}}

//---------------------------- End of file ---------------------------
