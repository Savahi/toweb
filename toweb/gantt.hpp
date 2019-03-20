#pragma once
#include "stdafx.h"

namespace Spider3d {

#define FIELD_WIDTH_MASK    0x000000FF  // ширина колонки в символах (максимум 256)
#define FIELD_TYPE_MASK    0x00070000
#define FIELD_FORMAT_MASK    0x00F00000

#define FIELD_FLOAT   0x00010000  // вещественное число
#define FIELD_SIGNAL  0x00020000  // целое число
#define FIELD_INT     0x00030000  // целое число
#define FIELD_TIME    0x00040000  // дата-время
#define FIELD_STRING  0x00050000  // строка

#define FIELD_EDITABLE    0x10000000
#define FIELD_HIDDEN      0x20000000  // целое число

	class GanttOperation {
	public:
		std::vector<std::string> fields;

		GanttOperation() { ; }
		~GanttOperation() { ; }
	};

	class Gantt {
	public:
		std::vector<std::string> fieldsNames;
		std::map<std::string, int> fieldsPositions;	
		std::map<std::string, std::string> fieldsTitles;
		std::map<std::string, long int> fieldsFlags;

		std::vector<GanttOperation> operations;

		Gantt() { ; }
		~Gantt() { ; }

		int add(GanttOperation& ga) {
			this->operations.push_back(ga);
			return 0;
		}

		int size(void) {
			return this->operations.size();
		}

		int clear(void) {
			this->operations.clear();
		}

	};
}