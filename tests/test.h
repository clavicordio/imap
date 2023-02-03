#pragma once
#include "test_key_val.h"
#include "interval_map.h"
#include <chrono>
#include <random>
#include <assert.h>

struct Test
{
	static inline void PrintIntervalMap(IntervalMap<MyTypes::MyKey, MyTypes::MyVal> interval_map)
	{
		std::cout << " BEFORE =================================== " << std::endl;
		for (auto it = interval_map.map().begin(); it != interval_map.map().end(); ++it)
			std::cout << it->first.get() << ": " << it->second.get() << std::endl;
		std::cout << " =================================== " << std::endl;
	}

	static long long TestMyKeyVal(bool map_print = false, bool check_correctness = true, bool sleep_enabled = true)
	{
		const int kTestCount = 5;
		const int kMaxKeyCount = 100;

		const std::string default_value = "default_value";
		const std::string values[8] = { "A","B","C","D","E","F","G","H" };

		const int kMinKey = 1;
		const int kMaxKey = 100;

		std::random_device dev;
		std::mt19937 rng(dev());
		rng.seed(100);	// random seed

		typedef std::uniform_int_distribution<std::mt19937::result_type> UniformDist;
		auto total_duration = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();

		for (auto i = 0; i < kTestCount; ++i)
		{
			IntervalMap<MyTypes::MyKey, MyTypes::MyVal> interval_map(default_value);
			// work
			for (auto j = 0; j < kMaxKeyCount; ++j)
			{
				if (map_print)
				{
					PrintIntervalMap(interval_map);
				}

				UniformDist dist_key(1, kMaxKey);
				UniformDist dist_val_id(0, end(values) - begin(values) - 1);

				int random_key_1 = dist_key(rng);
				int random_key_2 = dist_key(rng);
				std::string random_val = values[dist_val_id(rng)];

				// ===================== THE MAIN WORK ====================== /
				if (sleep_enabled)
					MyTypes::gSleep = true;

				auto time_start = std::chrono::high_resolution_clock::now();
				interval_map.assign(MyTypes::MyKey(random_key_1), MyTypes::MyKey(random_key_2), MyTypes::MyVal(random_val));
				auto time_end = std::chrono::high_resolution_clock::now();

				if (sleep_enabled)
					MyTypes::gSleep = false;

				total_duration += time_end - time_start;
				// ===================== ============= ====================== /

				if (map_print)
				{
					std::cout << "Insert: [" << random_key_1 << "," << random_key_2 << "), val=" << random_val << std::endl;
					PrintIntervalMap(interval_map);
				}

				if (check_correctness)
				{
					for (auto k = random_key_1; k < random_key_2; ++k)
						assert(interval_map[k] == random_val);
					interval_map.assertCanonicity();
				}
			}
		}

		auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(total_duration);
		std::cout << "Evaluated in " << duration_ms.count() << " milliseconds (assign() functions only)." << std::endl;
		return duration_ms.count();
	};

};
