#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.hpp"
#include "models.hpp"

namespace Spider3d {

    static int parseFileHeader( FILE *fp );
    static int parseFileLine( Models& models, FILE *fp );

    static int parseModel( Model& model, char *cpText );

    static int getValuesByColumnPos( char *cpLine, int *codeIndex, int *nameIndex, int *descriptionIndex, int *notesIndex );

    static int _iCodePos, _iNamePos, _iDescriptionPos, _iNotesPos;

    int loadModels( Models& models, const char *cpFile ) {

        FILE *fp;
        int status;
        fp = fopen( cpFile, "rb" );
        if( fp != NULL ) {
            status = parseFileHeader( fp );
            if( status != -1 ) {
                while(1) {
                    status = parseFileLine( models, fp );
                    if( status == -1 ) {
                        break;
                    }
                }
            }
            fclose(fp);
        }
        return 0;
    }


    static int parseFileHeader( FILE *fp ) {
        int ret_val=0;
        char *cpHeader;

        cpHeader = readLineFromFile(fp);
        if( cpHeader == NULL ) {
            return -1;
        }

        _iCodePos = getPosByColumnName( cpHeader, "Code" );
        if( _iCodePos == -1 ) {
            ret_val = -1;
        }
        _iNamePos = getPosByColumnName( cpHeader, "Name" );
        if( _iNamePos == -1 ) {
            ret_val = -1;
        }
        _iDescriptionPos = getPosByColumnName( cpHeader, "Description" );
        if( _iDescriptionPos == -1 ) {
            ret_val = -1;
        }
        _iNotesPos = getPosByColumnName( cpHeader, "Notes" );
        if( _iNotesPos == -1 ) {
            ret_val = -1;
        }

        free(cpHeader);
        return ret_val;
    }


    static int parseFileLine( Models& models, FILE *fp ) {
        int status, codeIndex, nameIndex, descriptionIndex, notesIndex;
        char *cpLine; 

        cpLine = readLineFromFile(fp);
        if( cpLine == NULL ) {
            return -1;
        }
        if( cpLine[0] != '/' && cpLine[0] != '#' ) { // Not a comment
            status = getValuesByColumnPos( cpLine, &codeIndex, &nameIndex, &descriptionIndex, &notesIndex );
            if( status == 0 ) {
                Model model;
                parseModel( model, &cpLine[descriptionIndex] );
                if( model.numFacets() > 0 ) {
                    model.setCode( trimString(&cpLine[codeIndex]) );
                    model.setName( &cpLine[nameIndex] );
                    model.setNotes( &cpLine[notesIndex] );
                    models.add(model);
                }
            }
        }
        free(cpLine);
        return 0;
    }


    static int parseModel( Model& model, char *cpText ) {
        int status, lenText, facetStart, facetEnd, pointStart, pointEnd, boxStart, boxEnd;
        int index, numBuffered;
        char caBuffer[READ_BUFFER_SIZE];
        float fX, fY, fZ;
        float xLeft, yBottom, zNear, xRight, yTop, zFar;

        lenText = strlen( cpText );

        // Searching for the faces and points inside
        facetEnd = 0;
        while(1) {
            status = findTagContent( cpText, "facet", facetEnd, lenText, &facetStart, &facetEnd );
            if( status == 0 ) {
                break;
            }
            Facet facet;

            pointEnd = facetStart;
            while(1) {
                status = findTagContent( cpText, "point", pointEnd, facetEnd, &pointStart, &pointEnd );
                if( status == 0 ) {
                    break;
                }

                for( index = pointStart, numBuffered = 0 ; index <= pointEnd && numBuffered < READ_BUFFER_SIZE ; ) {
                    if( cpText[index] == ',' ) {
                        caBuffer[ numBuffered ] = ' ';
                    } else {
                        caBuffer[ numBuffered ] = cpText[index];
                    }
                    index++;
                    numBuffered++;
                }
                caBuffer[ numBuffered ] = '\x0';
                //status = sscanf( caBuffer, " %f %f %f", &fX, &fY, &fZ );
                status = sscanf( caBuffer, " %f %f %f", &fX, &fZ, &fY ); // Y goes up in openGL
                if( status == 3 ) {
                    Vertex vertex( fX, fY, fZ );
                    facet.add(vertex);
                }
            }
            model.add(facet);
        }

        // Searchingfor the boxes
        boxEnd = 0;
        while(1) {
            status = findTagContent( cpText, "box", boxEnd, lenText, &boxStart, &boxEnd );
            if( status == 0 ) {
                break;
            }

            for( index = boxStart, numBuffered = 0 ; index <= boxEnd && numBuffered < READ_BUFFER_SIZE ; ) {
                if( cpText[index] == ',' ) {
                    caBuffer[ numBuffered ] = ' ';
                } else {
                    caBuffer[ numBuffered ] = cpText[index];
                }
                index++;
                numBuffered++;
            }
            caBuffer[ numBuffered ] = '\x0'; 
            //status = sscanf( caBuffer, " %f %f %f %f %f %f", &xLeft, &yBottom, &zNear, &xRight, &yTop, &zFar );
            status = sscanf( caBuffer, " %f %f %f %f %f %f", &xLeft, &zNear, &yBottom, &xRight, &zFar, &yTop );
            if( status == 6 ) {
                Facet facet;
                Vertex vertex;
                vertex.setXYZ( xLeft, yBottom, zNear ); facet.add(vertex);
                vertex.setXYZ( xLeft, yTop, zNear ); facet.add(vertex);
                vertex.setXYZ( xRight, yTop, zNear ); facet.add(vertex);
                vertex.setXYZ( xRight, yBottom, zNear ); facet.add(vertex);
                model.add(facet);
                facet.clear();
                vertex.setXYZ( xLeft, yBottom, zFar ); facet.add(vertex);
                vertex.setXYZ( xRight, yBottom, zFar ); facet.add(vertex);
                vertex.setXYZ( xRight, yTop, zFar ); facet.add(vertex);
                vertex.setXYZ( xLeft, yTop, zFar ); facet.add(vertex);
                model.add(facet);
                facet.clear();
                vertex.setXYZ( xLeft, yBottom, zNear ); facet.add(vertex);
                vertex.setXYZ( xLeft, yBottom, zFar ); facet.add(vertex);
                vertex.setXYZ( xRight, yBottom, zFar ); facet.add(vertex);
                vertex.setXYZ( xRight, yBottom, zNear ); facet.add(vertex);
                model.add(facet);
                facet.clear();
                vertex.setXYZ( xLeft, yTop, zNear ); facet.add(vertex);
                vertex.setXYZ( xRight, yTop, zNear ); facet.add(vertex);
                vertex.setXYZ( xRight, yTop, zFar ); facet.add(vertex);
                vertex.setXYZ( xLeft, yTop, zFar ); facet.add(vertex);
                model.add(facet);
                facet.clear();
                vertex.setXYZ( xLeft, yBottom, zNear ); facet.add(vertex);
                vertex.setXYZ( xLeft, yBottom, zFar ); facet.add(vertex);
                vertex.setXYZ( xLeft, yTop, zFar ); facet.add(vertex);
                vertex.setXYZ( xLeft, yTop, zNear ); facet.add(vertex);
                model.add(facet);
                facet.clear();
                vertex.setXYZ( xRight, yBottom, zNear ); facet.add(vertex);
                vertex.setXYZ( xRight, yTop, zNear ); facet.add(vertex);
                vertex.setXYZ( xRight, yTop, zFar ); facet.add(vertex);
                vertex.setXYZ( xRight, yBottom, zFar ); facet.add(vertex);
                model.add(facet);

            }
        }

        // Calculating min & max
        model.bMinMax = false;
        for( std::vector<Facet>::iterator facet = model.mFacets.begin() ; facet != model.mFacets.end() ; ++facet ) {
            facet->bMinMax=false;
            for( std::vector<Vertex>::iterator ve = facet->mVertices.begin() ; ve != facet->mVertices.end() ; ++ve ) {
                if( !facet->bMinMax ) {
                    facet->fMinX = facet->fMaxX = ve->mX; facet->fMinY = facet->fMaxY = ve->mY; facet->fMinZ = facet->fMaxZ = ve->mZ;
                    facet->bMinMax = true;
                } else {
                    if( ve->mX < facet->fMinX ) { facet->fMinX = ve->mX; }
                    if( ve->mX > facet->fMaxX ) { facet->fMaxX = ve->mX; }
                    if( ve->mY < facet->fMinY ) { facet->fMinY = ve->mY; }
                    if( ve->mY > facet->fMaxY ) { facet->fMaxY = ve->mY; }
                    if( ve->mZ < facet->fMinZ ) { facet->fMinZ = ve->mZ; }
                    if( ve->mZ > facet->fMaxZ ) { facet->fMaxZ = ve->mZ; }
                }
            }
            if( !facet->bMinMax ) {
                continue;
            }

            if( !model.bMinMax ) {
                model.fMinX = facet->fMinX; model.fMaxX = facet->fMaxX; 
                model.fMinY = facet->fMinY; model.fMaxY = facet->fMaxY; 
                model.fMinZ = facet->fMinZ; model.fMaxZ = facet->fMaxZ; 
                model.bMinMax = true;
            } else {
                if( facet->fMinX < model.fMinX ) { model.fMinX = facet->fMinX; }
                if( facet->fMaxX > model.fMaxX ) { model.fMaxX = facet->fMaxX; }
                if( facet->fMinY < model.fMinY ) { model.fMinY = facet->fMinY; }
                if( facet->fMaxY > model.fMaxY ) { model.fMaxY = facet->fMaxY; }
                if( facet->fMinZ < model.fMinZ ) { model.fMinZ = facet->fMinZ; }
                if( facet->fMaxZ > model.fMaxZ ) { model.fMaxZ = facet->fMaxZ; }
            }
        }
        return 0;
    }

    static int getValuesByColumnPos( char *cpLine, int *codeInex, int *nameIndex, int *descriptionIndex, int *notesIndex ) {
        int i, iPos, iLineLen;
        *codeInex=-1; 
        *nameIndex=-1;
        *descriptionIndex=-1;
        *notesIndex=-1;

        iLineLen = strlen( cpLine ); 
        for( i = 0, iPos = 0 ; i < iLineLen ; i++ ) {
            if( iPos == _iCodePos && *codeInex == -1 ) {
                *codeInex = i;
            } else if( iPos == _iNamePos && *nameIndex == -1 ) {
                *nameIndex = i;
            } else if( iPos == _iDescriptionPos && *descriptionIndex == -1 ) { 
                *descriptionIndex = i;
            } else if( iPos == _iNotesPos && *notesIndex == -1 ) {
                *notesIndex = i;
            } 
            if( cpLine[i] == '\t' ) {
                iPos++;
                cpLine[i] = '\x0';
            } else if( cpLine[i] == '\r' || cpLine[i] == '\n') {
                cpLine[i] = '\x0';            
            }
        }
        if( *codeInex == -1 || *nameIndex == -1 || *descriptionIndex == -1 || *notesIndex == -1 ) {
            return -1;
        }
        return 0;
    }

}