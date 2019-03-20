#include "stdafx.h"

namespace Spider3d {

    static int iCodePos, iNamePos, iTypePos, iNumberPos;

    static char caCode[] = "Code";
    static char caName[] = "Name";
    static char caType[] = "Type";
    static char caNumber[] = "Number";

    static int nFields = 4;
    static char *cpaFields[] = { caCode, caName, caType, caNumber };
    static int  *ipaFields[] = { &iCodePos, &iNamePos, &iTypePos, &iNumberPos };

    static int iCodeIndex, iNameIndex, iTypeIndex, iNumberIndex;
    static int *ipaFieldIndexes[] = { &iCodeIndex, &iNameIndex, &iTypeIndex, &iNumberIndex };

    int loadResources( Resources& resources, const char *cpFile ) {
        FILE *fp;
        char *cpLine;
        int iStatus;
        int nScanned;

        fp = fopen( cpFile, "rb" );
        if( fp != NULL ) {
            iStatus = parseFileHeader( fp, nFields, cpaFields, ipaFields );
            if( iStatus != -1 ) {
                while(1) {
                    cpLine = parseFileLine( fp, nFields, ipaFields, ipaFieldIndexes, &iStatus );
                    if( cpLine == NULL ) {
                        break;
                    }
                    Resource resource;
                    resource.sCode = std::string( trimString( &cpLine[iCodeIndex] ) );
                    resource.sName = std::string( trimString( &cpLine[iNameIndex] ) );
                    resource.sType = std::string( trimString( &cpLine[iTypeIndex] ) );
                    nScanned = sscanf( &cpLine[iNumberIndex], "%f", &resource.fNumber );
                    resource.bNumber = ( nScanned == 1 ) ? true : false;

                    resources.add( resource );

                    free(cpLine);
                }
            }
            fclose(fp);
        }
        return 0;
    }
}