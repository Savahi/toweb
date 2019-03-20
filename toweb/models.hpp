#pragma once
#include "stdafx.h"

namespace Spider3d {

	class Vertex {
		public:
			double mX, mY, mZ;
			Vertex( void ) {
				; // std::cout << "Constructor for Vertex\n"; 
			}
			Vertex( double x, double y, double z ) : mX(x), mY(y), mZ(z) {
				; // std::cout << "Constructor for Vertex\n"; 
			}
			~Vertex(){
				; // std::cout << "Destructor for Vertex\n"; 
			}
			int setXYZ( double x, double y, double z ) {
				this->mX = x;
				this->mY = y;
				this->mZ = z;
				return 0;
			}
			int setXYZ( double *x, double *y, double *z ) {
				if( x != NULL ) { this->mX = *x; }
				if( y != NULL ) { this->mY = *y; }
				if( z != NULL ) { this->mZ = *z; }
				return 0;
			}
			int addX( double x ) { this->mX += x; }
			int addY( double y ) { this->mY += y; }
			int addZ( double z ) { this->mZ += z; }
	};

	class Facet {
		public:
			std::vector<Vertex> mVertices;

			bool bMinMax;
			double fMinX, fMaxX, fMinY, fMaxY, fMinZ, fMaxZ;

			int add( Vertex& vertex ) {
				this->mVertices.push_back( vertex );
				return 0;
			}

			void clear( void ) {
				this->mVertices.clear();
			}

			Facet() : bMinMax(false) {
				; // std::cout << "Constructor for Facet\n";
			}
			~Facet() {
				; // std::cout << "Destructor for Facet\n";
			}
	};

	class Model {
		
		public:
			std::vector<Facet> mFacets; 
			std::string sCode;
			std::string sName;
			std::string sNotes;
			bool bSelected;

			bool bMinMax;
			double fMinX, fMaxX, fMinY, fMaxY, fMinZ, fMaxZ;

			std::map<time_t,Operation*> operations; // Operations associated with the model

			int add( Facet& facet ) {
				this->mFacets.push_back( facet );
				return 0;
			}

			void setCode( std::string& code ) { this->sCode = code; }
			void setCode( char *cpCode ) { this->sCode = std::string( cpCode ); }

			void setName( std::string& name ) { this->sName = name; }
			void setName( char *cpName ) { this->sName = std::string( cpName ); }

			void setNotes( std::string& notes ) { this->sNotes = notes; }
			void setNotes( char *cpNotes ) { this->sNotes = std::string( cpNotes ); }

			unsigned int numFacets( void ) {
				return this->mFacets.size(); 
			}

			Model() : bSelected(false), bMinMax(false) {
				; // std::cout << "Constructor for Model\n";
			}

			Model( std::string code ) : sCode(code), bSelected(false), bMinMax(false) {
				; // std::cout << "Constructor for Model\n";
			}

			~Model() {
				; // std::cout << "Destructor for Model\n";
			}
	};

	class Models {
		public:
			std::vector<Model> mModels; 

			bool mAxis;
			float mGrid;
			float mXMargin, mYMargin, mZMargin;

			Models() {
				; // std::cout << "Constructor for Model\n";
			}

			~Models() {
				; // std::cout << "Destructor for Model\n";
			}
			int add( Model& model ) {
				this->mModels.push_back( model );
				return 0;
			}

			unsigned int number( void ) {
				return this->mModels.size(); 
			}

	};

}



