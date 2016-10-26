# cpp_properties

This is a naive implementation of Java's Properties class functionality in C++11.

```c++
  #include "properties.h"

  #include <cassert>

  int main() {

	{
		utils::properties props {"test-data/1.properties"};

		assert(props.get_size() == 4);

		assert(props.get_string("value.1") == "No more");
		assert(props.get_string("one.more.key") == "No spaces!!!");
		assert(props.get_string("value21") == "Not again");
		assert(props.get_string("app.name") == "Hello world!");

	}

	{
		utils::properties props;
		props.load("1.properties");

		assert(props.get_size() == 4);

		assert(props.get_string("value.1") == "No more");
		assert(props.get_string("one.more.key") == "No spaces!!!");
		assert(props.get_string("value21") == "Not again");
		assert(props.get_string("app.name") == "Hello world!");

		props.clear();

		assert(props.get_size() == 0);

		try {
			assert(props.get_string("app.name") == "");
			assert(false);
		} catch (std::out_of_range& ex) {

		}
	}


	{
		utils::properties props;
		props.load("test-data/2.properties");
		assert(props.get_size() == 0);
	}

    return EXIT_SUCCESS;

    }
