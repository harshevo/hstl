#include <cstdint>
#include <iostream>
#include <string>

struct Address
{
	std::string city;
	std::string country;
	uint16_t postalcode;

	auto isReflect() const
	{
		auto tuple = std::make_tuple(std::make_pair("city", city), std::make_pair("country", country),
									 std::make_pair("postalcode", postalcode));
		return tuple;
	};
};

struct Person
{
	std::string id;
	std::string name;
	Address address;

	auto isReflect() const
	{
		auto tuple =
			std::make_tuple(std::make_pair("id", id), std::make_pair("name", name), std::make_pair("address", address));
		return tuple;
	};
};

struct Server
{
	std::string id;
	Person person;

	auto isReflect() const
	{
		auto tuple = std::make_tuple(std::make_pair("id", id), std::make_pair("person", person));
		return tuple;
	};
};

template <typename T, typename = void> struct IsReflectable : std::false_type
{
};

template <typename T>
struct IsReflectable<T, std::void_t<decltype(std::declval<const T &>().isReflect())>> : std::true_type
{
};

template <typename T> void SerializeText(const T &obj, std::ostream &os, int indent = 0)
{
	if constexpr (IsReflectable<T>::value)
	{
		auto fields = obj.isReflect();

		std::apply(
			[&](auto &&...pair) {
				((os << std::string(indent, ' ') << pair.first << ": ", SerializeText(pair.second, os, indent + 2)),
				 ...);
			},
			fields);
	}
	else
	{
		os << obj << "\n";
	}
};

int main()
{
	Server p = {"1", {"1", "Don", {"Delhi", "India", 2030}}};

	SerializeText(p, std::cout);
}
