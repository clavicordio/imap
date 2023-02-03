# IntervalMap

An interval-map is a mutable data structure that maps half-open intervals of exact keys to values. 
Internally, it is built on top of an std::map. The functionality is designed for an efficient use in situations where intervals of consecutive keys are associated with the same value. 

The key functionality implemented in this repo is the `assign(k1, k2, v)` method, which maps the value `v` to the interval `[k1, k2)'. The class is designed for use with arbitrary classes K for key and V for value, assuming they implement an absolute minimum of functionality needed for the structure: K only needs `operator<`, and V only needs `operator==` (aside from copy and assignment operations, of course).

The class is designed to be cost-efficient does not perform unnecessary comparisons or assignments.
