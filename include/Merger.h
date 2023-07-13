#pragma once


#include <string>
#include <list>
#include <unordered_map>

#include "BitfieldUtilities.h"
#include "File.h"


class Merger {
	static const int MAX_SIZE_OF_NAME = 10;
public:

	static std::string merge(const std::list<File<std::string>> files) {
		std::string mergedStr;

		std::vector<std::string> names;

		for (const auto& file : files) {
			names.push_back(cropName(getName(file.directory)));
		}

		names = makeUniq(names);

		

	}

private:

	static std::string cropName(const std::string& name) {
		return name.substr(0, MAX_SIZE_OF_NAME);
	}

	static vector<std::string> makeUniq(const std::vector<std::string>& names) {
		vector<std::string> uniqNames;
		unordered_map<std::string, int> namesMap;

		for (const std::string& name : names) {
			if (namesMap[name]++ > 0) {
				uniqNames.push_back(name + "(" + std::to_string(namesMap[name]) + ")");
			}
			else {
				uniqNames.push_back(name + "(" + std::to_string(namesMap[name]) + ")");
			}
		}

		return uniqNames;
	}

};