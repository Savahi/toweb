#pragma once

#include <vector>
#include <string>
#include "helpers.hpp"
	
namespace Spider3d {

	class OpLink {
		public:

			std::string sPredCode;
			std::string sSuccCode;
			std::string sTypeSF;
			std::string sLagType;
			std::string sLagUnit;
			float fLag;
			bool bLag;

			OpLink() {;}

			~OpLink() {;}
	};

	class OpLinks {
		public:
			std::vector<OpLink> mOpLinks;

			int add( OpLink& opLink ) {
				this->mOpLinks.push_back( opLink );
				return 0;
			}

			int clear( void ) {
				this->mOpLinks.clear();
			}

			OpLinks() {;}
			~OpLinks() {;}

			unsigned int number( void ) {
				return this->mOpLinks.size(); 
			}
	};

}