#include <iostream>
#include "tests/test.h"

int main()
{
    {
        // simple visual test
        std::cout << " =========== " << std::endl;
        std::cout << " VISUAL TEST " << std::endl;
        std::cout << " =========== " << std::endl << std::endl;

        IntervalMap<int, char> imap('-');
        imap.assign(1, 25, 'B');
        imap.assign(10, 20, 'C');
        imap.assign(5, 10, 'A');
        imap.assign(20, 23, 'D');

        for (auto it = imap.map().begin(); it != imap.map().end(); ++it)
            std::cout << it->first << ": " << it->second << std::endl;
        std::cout << std::endl;

        std::cout << " ... ";
        for (auto i = -2; i <= 27; ++i)
            std::cout << imap[i];
        std::cout << " ... ";
        std::cout << std::endl;
        std::cout << std::endl;
    }

    {
        // performance & correctness randomized test
        std::cout << " =============== " << std::endl;
        std::cout << " RANDOMIZED TEST " << std::endl;
        std::cout << " =============== " << std::endl << std::endl;
        double total_evaluation_time = 0;
        auto N = 3;
        for (auto i = 0; i < N; ++i)
        {
            std::cout << "running test #" << i << std::endl;
            total_evaluation_time += Test::TestMyKeyVal();
        }
        std::cout << "\n\nAverage eval time:   " << total_evaluation_time / (double)N << "ms.  " << std::endl;
        return 0;
    }

}
