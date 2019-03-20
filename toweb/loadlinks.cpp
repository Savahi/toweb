#include "stdafx.h"

namespace Spider3d {

    static int fieldsToReadNum = 3;
    static const char *fieldsToRead[] = { "PredCode", "SuccCode", "TypeSF2" };

    int loadLinks( Links& links, const char *cpFile ) {

    	std::vector<std::string> fieldsNames;
        for( int i= 0 ; i < fieldsToReadNum ; i++ ) {
            fieldsNames.push_back( fieldsToRead[i] );
        }

        std::ifstream infile( cpFile );
        if( !infile.is_open() ) {
            return -1;
        }
        int numHeaderParsed = parseAllFileHeader( infile, links.fieldsNames, links.fieldsPositions );
        if( numHeaderParsed != -1 ) {
            int numFlagsParsed = parseAllFileHeaderFlags( infile, links.fieldsNames, links.fieldsFlags );
            if( numFlagsParsed == numHeaderParsed ) {
                int numTitlesParsed = parseAllFileHeaderTitles( infile, links.fieldsNames, links.fieldsTitles );
                if( numTitlesParsed == numHeaderParsed ) {
                    while(1) {
                        std::map<std::string,std::string> fieldsParsed;    
                        int numParsed = parseFileLine( infile, links.fieldsPositions, fieldsParsed );
                        if( numParsed == -1 ) {
                            break;
                        }
                        Link link;
                        link.sPredCode = fieldsParsed["PredCode"];
                        link.sSuccCode = fieldsParsed["SuccCode"];
                        int nScanned = sscanf( fieldsParsed["f_TypeSF2"].c_str(), "%lx", &link.iTypeSF2 );
                        link.bTypeSF2 = ( nScanned == 1 ) ? true : false;
                        links.add(link);
                    }
                }
            }
        }
        infile.close();
        return 0;
    }
}

