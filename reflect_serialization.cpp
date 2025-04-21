#include <iostream>
#include <string>

struct Address
{
	std::string city;
	std::string country;
};

struct Person
{
	std::string name;
	int age;
	Address address;
};

template <typename T> struct Reflect;

template <> struct Reflect<Person>
{
	static constexpr auto fields =
		std::make_tuple(std::make_pair("name", &Person::name), std::make_pair("age", &Person::age),
						std::make_pair("address", &Person::address));
};

template <> struct Reflect<Address>
{
	static constexpr auto fields =
		std::make_tuple(std::make_pair("city", &Address::city), std::make_pair("country", &Address::country));
};

template <typename T, typename = void> struct is_reflectable : std::false_type
{
};

template <typename T> struct is_reflectable<T, std::void_t<decltype(Reflect<T>::fields)>> : std::true_type
{
};

template <typename T> void SerializeText(const T &obj, std::ostream &os, int indent = 0)
{
	std::string indent_s = " ";

	if constexpr (is_reflectable<T>::value)
	{
		auto fields = Reflect<T>::fields;

		std::apply(
			[&](auto &&...pair) {
				((os << std::string(indent, ' ') << pair.first << ": ", SerializeText(obj.*pair.second, os, indent = 2),
				  os << "\n"),
				 ...);
			},
			fields);
	}
	else
	{
		os << obj;
	}
}

int main()
{
	Person p{"Don", 21, {"Delhi", "India"}};

	SerializeText(p, std::cout);
}
