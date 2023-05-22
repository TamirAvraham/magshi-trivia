#pragma once
#include <concepts>
#include "responce.h"
template<class T>
concept stringfy = requires(T v){
	{v}->std::convertible_to<std::string>;
};
template<class T>
concept canBeToStringed = requires(T v) {
	{v.toString()}->std::convertible_to<std::string>;
};
class JsonSirealizer
{
public:
	template<class T> 
	static std::string getVectorAsString(std::vector<T> vector) requires stringfy<T>;
	template<class T> 
	static std::string getVectorAsString(std::vector<T> vector) requires canBeToStringed<T>;
};

template<class T>
inline std::string JsonSirealizer::getVectorAsString(std::vector<T> vector) requires stringfy<T> 
{
	std::string ret = "[";
	for (size_t i = 0; const auto & item : vector) {
		ret += item;
		ret += (++i == vector.size() ? ']' : ',');
	}
	return ret;
}

template<class T>
inline std::string JsonSirealizer::getVectorAsString(std::vector<T> vector) requires canBeToStringed<T>
{
	std::string ret = "[";
	for (size_t i = 0; const auto & item : vector) {
		ret += item.toString();
		ret += (++i == vector.size() ? ']' : ',');
	}
	return ret;
}