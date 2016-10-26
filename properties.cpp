/*
MIT License

Copyright (c) 2016 Sergey Nechaev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#include "properties.h"

#include <fstream>
#include <iostream>
#include <utility>

#include "strings.h"

utils::properties::properties() {
}

utils::properties::~properties() {
}

utils::properties::properties(const std::string file) {
	this->load(file);
}

void utils::properties::load(const std::string file) {

	std::cout << "== Read properties from file: [" << file << "]\n";

	std::ifstream infile(file);

	if (!infile) {
		std::cerr << "Cannot open file " << file << std::endl;
		return;
	}

	std::string key;
	std::string value;

	std::string line;

	for (line; std::getline(infile, line);) {

		if (strings::starts_with(line, "#") || strings::is_empty(line)) {

		} else {

			std::string::size_type pos = line.find_first_of("=");

			if (std::string::npos != pos) {

				value = line.substr(pos + 1, line.length());
				key = line.substr(0, pos);

				key = strings::trim(key);
				value = strings::trim(value);

				this->props.insert(std::pair<std::string, std::string> { key, value });

			} else {
				std::cerr << "Cannot parse '" << line << "'" << std::endl;
			}

		}

	}

	// list properties
	std::cout << "Loaded properties:\n";
	for (auto a : this->props) {
		std::cout << "\t '" << a.first + "': '" << a.second << "'" << "\n";
	}

}

int utils::properties::get_int(const std::string key) const {
	return stoi(get_string(key));

}

float utils::properties::get_float(const std::string key) const {
	return stof(get_string(key));

}

std::string utils::properties::get_string(const std::string key) const {
	return this->props.at(key);
}

void utils::properties::clear() {
	this->props.clear();
}

unsigned int utils::properties::get_size() const {
	return this->props.size();
}
