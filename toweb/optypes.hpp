#pragma once

#include <vector>
#include <string>
#include "helpers.hpp"
	
namespace Spider3d {

	class OpType {
		public:

			std::string sCode;
			std::string sName;
			float fR, fG, fB;

			void setCode( std::string& sCode ) { this->sCode = sCode; }
			void setCode( char *cpCode ) { this->sCode = std::string( cpCode ); }

			void setName( std::string& sName ) { this->sName = sName; }
			void setName( char *cpName ) { this->sName = std::string( cpName ); }

			OpType() : fR(1), fG(1), fB(1) {
				; // std::cout << "Constructor for OpType\n";
			}

			~OpType() {
				; // std::cout << "Destructor for OpType\n";
			}
	};

	class OpTypes {
		public:
			std::vector<OpType> mOpTypes;

			int add( OpType& opType ) {
				this->mOpTypes.push_back( opType );
				return 0;
			}

			int clear( void ) {
				this->mOpTypes.clear();
			}

			OpTypes() {
				; // std::cout << "Constructor for Operations\n";
			}
			~OpTypes() {
				; // std::cout << "Destructor for Operations\n";
			}

			unsigned int number( void ) {
				return this->mOpTypes.size(); 
			}
	};

}