#ifndef HWDG_CUSTOM_MAP_HPP
#define HWDG_CUSTOM_MAP_HPP

/**
* @file custom_map.hpp
* @author Jakub Grzana
* @date March 2022
* @brief Monstrosity
*
* Thin wrapper for std::unordered_map, providing iterators that allows easier iteration over content (skips key, returning only value) 
* It simplifies usage of Graph and other parts of this library, but it's terrible design choice afterall.
* 
* Operator -> for iterators is removed, because I couldn't make it work without terrible pointer hacking so it's safer this way.
*/

#include <unordered_map>

namespace HWDG
{	
	namespace Map
	{
		template<typename keytype, typename valuetype>
		class iterator : public std::unordered_map<keytype, valuetype>::iterator
		{
			public:
				valuetype* operator -> () = delete;
				valuetype& operator * ()
				{
					typename std::unordered_map<keytype, valuetype>::iterator& iter = *this;
					return iter->second;
				}
				iterator<keytype, valuetype>(const typename std::unordered_map<keytype, valuetype>::iterator& i) : std::unordered_map<keytype, valuetype>::iterator(i) {}
		};

		template<typename keytype, typename valuetype>
		class const_iterator : public std::unordered_map<keytype, valuetype>::const_iterator
		{
			public:
				const valuetype* operator -> () const = delete;
				const valuetype& operator * () const
				{
					const typename std::unordered_map<keytype, valuetype>::const_iterator& iter = *this;
					return iter->second;
				}
				const_iterator<keytype, valuetype>(const typename std::unordered_map<keytype, valuetype>::const_iterator& i) : std::unordered_map<keytype, valuetype>::const_iterator(i) {}
		};

		template<typename keytype, typename valuetype>
		class unordered_map : public std::unordered_map<keytype, valuetype>
		{
			public:
				iterator<keytype, valuetype> begin() { return iterator<keytype, valuetype>(std::unordered_map<keytype, valuetype>::begin()); }
				const_iterator<keytype, valuetype> cbegin() const { return const_iterator<keytype, valuetype>(std::unordered_map<keytype, valuetype>::cbegin()); }
				const_iterator<keytype, valuetype> begin() const { return const_iterator<keytype, valuetype>(std::unordered_map<keytype, valuetype>::begin()); }
				iterator<keytype, valuetype> end() { return (iterator<keytype, valuetype>) std::unordered_map<keytype, valuetype>::end(); }
				const_iterator<keytype, valuetype> cend() const { return const_iterator<keytype, valuetype>(std::unordered_map<keytype, valuetype>::cend()); }
				const_iterator<keytype, valuetype> end() const { return const_iterator<keytype, valuetype>(std::unordered_map<keytype, valuetype>::end()); }
				iterator<keytype, valuetype> find(const keytype& id) { return iterator<keytype, valuetype>(std::unordered_map<keytype, valuetype>::find(id)); }
				const_iterator<keytype, valuetype> find(const keytype& id) const { return const_iterator<keytype, valuetype>(std::unordered_map<keytype, valuetype>::find(id)); }
		};
	}
}

#endif