#pragma once
#include <stdexcept>
#include <map>
#include <assert.h>

//#include "tests/test_key_val.h" // uncomment for intellisense

// Key type K : less-than comparable via operator<
// Key type V : equality-comparable via operator==
template<typename K, typename V>
class IntervalMap 
{
public:
	IntervalMap(V const& val) : val_begin_(val) {}

	void assign(K const& key_begin, K const& key_end, V const& val)
	{
		if (!(key_begin < key_end))
			return;

		const auto begin_lb = map_.lower_bound(key_begin);																		// O(log(size))
		V const& begin_prev_val = (begin_lb == map_.begin()) ? val_begin_ : std::prev(begin_lb)->second;
		
		auto end_ub = begin_lb; while ((end_ub != map_.end()) && !(key_end < end_ub->first)) ++end_ub;							// O(|key_end-key_begin|)
		V const& end_prev_val = (end_ub == map_.begin()) ? val_begin_ : std::prev(end_ub)->second;

		const auto end_lb = (end_ub == map_.begin()) ? end_ub : std::prev(end_ub);

		const auto del_end = (val == end_prev_val) ? end_ub : map_.emplace_hint(end_lb, key_end, end_prev_val);					// O(1) or O(log(size))
		const auto del_begin = (val == begin_prev_val) ? begin_lb : std::next(map_.insert_or_assign(begin_lb, key_begin, val));	// O(1) or O(log(size))
	
		map_.erase(del_begin, del_end);																							// O(|del_end-del_begin|)
	}

	V const& operator[](K const& key) const
	{
		auto it = map_.upper_bound(key);
		if (it == map_.begin())
			return val_begin_;
		else
			return std::prev(it)->second;
	}

	// consecutive map entries must not contain the same value
	void assertCanonicity() const
	{
		if (map_.size() == 0)
			return;
		auto it = ++map_.begin();
		auto prev_it = map_.begin();
		for (; it != map_.end(); ++prev_it, ++it)
			assert(!(prev_it->second == it->second));
	}

	std::map<K, V> const& map()
	{
		return map_;
	}

private:
	V val_begin_;
	std::map<K, V> map_;
};