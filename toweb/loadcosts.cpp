#include "stdafx.h"

namespace Spider3d {

    static int iCodePos, iNamePos;

    static char caCode[] = "Code";
    static char caName[] = "Name";

    static int nFields = 2;
    static char *cpaFields[] = { caCode, caName };
    static int  *ipaFields[] = { &iCodePos, &iNamePos };

    static int iCodeIndex, iNameIndex;
    static int *ipaFieldIndexes[] = { &iCodeIndex, &iNameIndex };

    int loadCosts( Costs& costs, const char *cpFile ) {
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
                        Cost cost;
                        cost.sCode = std::string( trimString( &cpLine[iCodeIndex] ) );
                        cost.sName = std::string( trimString( &cpLine[iNameIndex] ) );
                        costs.add( cost );
                    }

                    free(cpLine);
                }
            }
            fclose(fp);
        }
        return 0;
    }
}