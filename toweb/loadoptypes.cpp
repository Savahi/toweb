#include "stdafx.h"

namespace Spider3d {

    static int _iCodePos, _iNamePos, _iColorPos;

    static char caCode[] = "Code";
    static char caName[] = "Name";
    static char caColor[] = "Color";

    static int nFields = 3;
    static char *cpaFields[] = { caCode, caName, caColor };
    static int  *ipaFields[] = { &_iCodePos, &_iNamePos, &_iColorPos };

    static int _iCodeIndex, _iNameIndex, _iColorIndex;
    static int *ipaFieldIndexes[] = { &_iCodeIndex, &_iNameIndex, &_iColorIndex };

    int loadOpTypes( OpTypes& opTypes, const char *cpFile ) {

        FILE *fp;
        char *cpLine;
        int iStatus;

        fp = fopen( cpFile, "rb" );
        if( fp != NULL ) {
            iStatus = parseFileHeader( fp, nFields, cpaFields, ipaFields );
            if( iStatus != -1 ) {
                while(1) {
                    int iParseFileLineStatus;
                    cpLine = parseFileLine( fp, nFields, ipaFields, ipaFieldIndexes, &iParseFileLineStatus );
                    if( cpLine == NULL ) {
                        break;
                    }
                    if( iParseFileLineStatus == 0 ) {
                        OpType opType;
                        opType.sCode = std::string( trimString( &cpLine[_iCodeIndex] ) );
                        opType.sName = std::string( &cpLine[_iNameIndex] );
                        int iColor;
                        int nScanned = sscanf( &cpLine[_iColorIndex], "%d", &iColor );
                        if( nScanned == 1 ) {
                            opType.fR = (float)(iColor & 0x0000FF) / 255.0;
                            opType.fG = (float)(iColor & 0x00FF00) / 255.0;
                            opType.fB = (float)(iColor & 0xFF0000) / 255.0;
                            opTypes.add( opType );
                        }
                    }
                    free(cpLine);
                }
            }
            fclose(fp);
        }
        return 0;
    }

}