#pragma once

#include <vector>
#include <string>
#include "helpers.hpp"
	
namespace Spider3d {

	class Resource {
		public:
			std::string sCode;
			std::string sName;
			std::string sType;
			float fNumber;
			bool bNumber;

			Resource() {;}
			~Resource() {;}
	};

	class Resources {
		public:
			std::vector<Resource> mResources;

			int add( Resource& resource ) {
				this->mResources.push_back( resource );
				return 0;
			}

			int clear( void ) {
				this->mResources.clear();
			}

			Resources() {;}
			~Resources() {;}

			unsigned int number( void ) {
				return this->mResources.size(); 
			}
	};
}