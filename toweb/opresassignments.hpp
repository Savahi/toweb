#pragma once

#include <vector>
#include <string>
#include "helpers.hpp"
	
namespace Spider3d {
	class OpResAssignment {
		public:
			std::string sOperCode;
			std::string sResCode;
			float fNumber;
			bool bNumber;
			float fPrior;
			bool bPrior;

			OpResAssignment() {;}

			~OpResAssignment() {;}
	};

	class OpResAssignments {
		public:
			std::vector<OpResAssignment> mOpResAssignments;

			int add( OpResAssignment& opResAssignment ) {
				this->mOpResAssignments.push_back( opResAssignment );
				return 0;
			}

			int clear( void ) {
				this->mOpResAssignments.clear();
			}

			OpResAssignments() {;}
			~OpResAssignments() {;}

			unsigned int number( void ) {
				return this->mOpResAssignments.size(); 
			}
	};
}