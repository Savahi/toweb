#include "stdafx.h"

namespace Spider3d {

    static int parseFileHeader( FILE *fp );
    static int parseFileLine( Operations& operations, FILE *fp );

    static int parseDates( char *cpActualStart, char *cpActualFinish, char *cpAsapStart, char *cpAsapFinish, Operation& operation );

    static int getValuesByColumnPos( char *cpLine, int *ipCode, int *ipName, int *ipType, 
        int *ipFactStart, int *ipFactFin, int *ipAsapStart, int *ipAsapFin, int *ipModel );

    static int _iCodePos, _iNamePos, _iTypePos, _iModelPos, _iFactStartPos, _iFactFinPos, _iAsapStartPos, _iAsapFinPos;

    int loadOperations( Operations& operations, const char *cpFile ) {

        FILE *fp;
        int iStatus;

        fp = fopen( cpFile, "rb" );
        if( fp != NULL ) {
            iStatus = parseFileHeader( fp );
            if( iStatus != -1 ) {
                while(1) {
                    iStatus = parseFileLine( operations, fp );
                    if( iStatus == -1 ) {
                        break;
                    }
                }
            }
            fclose(fp);
        }

        return 0;
    }

    static int parseFileHeader( FILE *fp ) {
        int iReturn=0;
        char *cpHeader;

        cpHeader = readLineFromFile(fp);
        if( cpHeader == NULL ) {
            return -1;
        }

        _iCodePos = getPosByColumnName( cpHeader, "code" );
        if( _iCodePos == -1 ) {
            iReturn = -1;
        }
        _iNamePos = getPosByColumnName( cpHeader, "name" );
        if( _iNamePos == -1 ) {
            iReturn = -1;
        }
        _iTypePos = getPosByColumnName( cpHeader, "type" );
        if( _iTypePos == -1 ) {
            iReturn = -1;
        }

        _iFactStartPos = getPosByColumnName( cpHeader, "factstart" );
        if( _iFactStartPos == -1 ) {
            iReturn = -1;
        }
        _iFactFinPos = getPosByColumnName( cpHeader, "factfin" );
        if( _iFactFinPos == -1 ) {
            iReturn = -1;
        }
        _iAsapStartPos = getPosByColumnName( cpHeader, "asapstart" );
        if( _iAsapStartPos == -1 ) {
            iReturn = -1;
        }
        _iAsapFinPos = getPosByColumnName( cpHeader, "asapfin" );
        if( _iAsapFinPos == -1 ) {
            iReturn = -1;
        }
        _iModelPos = getPosByColumnName( cpHeader, "model" );
        if( _iModelPos == -1 ) {
            iReturn = -1;
        }

        free(cpHeader);
        return iReturn;
    }

    static int parseFileLine( Operations& operations, FILE *fp ) {
        int iStatus, iCode, iName, iType, iFactStart, iFactFin, iAsapStart, iAsapFin, iModel;
        char *cpLine; 

        cpLine = readLineFromFile(fp);
        if( cpLine == NULL ) {
            return -1;
        }

        iStatus = getValuesByColumnPos( cpLine, &iCode, &iName, &iType, &iFactStart, &iFactFin, &iAsapStart, &iAsapFin, &iModel );
        if( iStatus == 0 ) {
            Operation operation;
            if( parseDates( &cpLine[iFactStart], &cpLine[iFactFin], &cpLine[iAsapStart], &cpLine[iAsapFin], operation ) == 0 ) {
                operation.sCode = std::string( trimString( &cpLine[iCode] ) );
                operation.sName = std::string( &cpLine[iName] );
                operation.sType = std::string( trimString( &cpLine[iType] ) );
                operation.sModelCode = std::string( trimString( &cpLine[iModel] ) );
                operations.add( operation );
            }
        }
        free(cpLine);
        return 0;
    }


    static int getValuesByColumnPos( char *cpLine, int *ipCode, int *ipName, int *ipType, 
        int *ipFactStart, int *ipFactFin, int *ipAsapStart, int *ipAsapFin, int *ipModel ) 
    {
        int i, iPos, iLineLen;
        *ipCode=-1;
        *ipName=-1; 
        *ipType=-1;
        *ipFactStart=-1;
        *ipFactFin=-1;
        *ipAsapStart=-1;
        *ipAsapFin=-1;
        *ipModel=-1;

        iLineLen = strlen( cpLine ); 
        for( i = 0, iPos = 0 ; i < iLineLen ; i++ ) {
            if( iPos == _iCodePos && *ipCode == -1 ) {
                *ipCode = i;
            } else if( iPos == _iNamePos && *ipName == -1 ) {
                *ipName = i;
            } else if( iPos == _iTypePos && *ipType == -1 ) {
                *ipType = i;
            } else if( iPos == _iFactStartPos && *ipFactStart == -1 ) {
                *ipFactStart = i;
            } else if( iPos == _iFactFinPos && *ipFactFin == -1 ) { 
                *ipFactFin = i;
            } else if( iPos == _iAsapStartPos && *ipAsapStart == -1 ) {
                *ipAsapStart = i;
            } else if( iPos == _iAsapFinPos && *ipAsapFin == -1 ) { 
                *ipAsapFin = i;
            } else if( iPos == _iModelPos && *ipModel == -1 ) {
                *ipModel = i;
            } 
            if( cpLine[i] == '\t' ) {
                iPos++;
                cpLine[i] = '\x0';
            } else if( cpLine[i] == '\r' || cpLine[i] == '\n') {
                cpLine[i] = '\x0';            
            }
        }
        if( *ipCode == -1 || *ipName == -1 || *ipType == -1 || 
            *ipFactStart == -1 || *ipFactFin == -1 || *ipAsapStart == -1 || *ipAsapFin == -1 || *ipModel == -1 ) {
            return -1;
        }
        return 0;
    }


    static int parseDate( char *cpDatetime, struct tm& tmDatetime ) {
        int iStatus;
        for( int i = 0 ; cpDatetime[i] != '\x0' ; i++ ) {
            if( cpDatetime[i] == '.' || cpDatetime[i] == '-' || cpDatetime[i] == ':' ) {
                cpDatetime[i] = ' ';
            }
        }
        iStatus = sscanf( cpDatetime, "%d %d %d %d %d", &tmDatetime.tm_mday, &tmDatetime.tm_mon, &tmDatetime.tm_year, &tmDatetime.tm_hour, &tmDatetime.tm_min );
        if( iStatus != 5 ) { 
            return -1;
        }
        tmDatetime.tm_year -= 1900;
        tmDatetime.tm_mon -= 1;
        tmDatetime.tm_sec = 0;
        tmDatetime.tm_wday = tmDatetime.tm_yday = tmDatetime.tm_isdst = 0;
        return 0;
    }

    static int parseDates( char *cpActualStart, char *cpActualFinish, char *cpAsapStart, char *cpAsapFinish, Operation& operation ) {
        int iStatus;

        iStatus = parseDate( cpActualStart, operation.tmActualStart );
        if( iStatus != -1 ) {
            operation.tActualStart = mktime( &(operation.tmActualStart) );
        } else {
            operation.tActualStart = 0;            
        }
        iStatus = parseDate( cpActualFinish, operation.tmActualFinish );
        if( iStatus != -1 ) {
            operation.tActualFinish = mktime( &(operation.tmActualFinish) );
        } else {
            operation.tActualFinish = 0;
        }
        
        iStatus = parseDate( cpAsapStart, operation.tmAsapStart );
        if( iStatus != -1 ) {
            operation.tAsapStart = mktime( &(operation.tmAsapStart) );
        } else {
            operation.tAsapStart = 0;
        }

        iStatus = parseDate( cpAsapFinish, operation.tmAsapFinish );
        if( iStatus != -1 ) {
            operation.tAsapFinish = mktime( &(operation.tmAsapFinish) );
        } else {
            operation.tAsapFinish = 0;            
        }
        
        operation.bDatesInitialized = true;
        
        return 0;
    }

}