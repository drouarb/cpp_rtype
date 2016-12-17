//
// Created by drouar_b on 11/25/16.
//

#ifndef RTYPE_STOPWATCH_HH
#define RTYPE_STOPWATCH_HH

#include <ctime>

namespace helpers {
    /*!
     * @class Stopwatch
     * @brief Count time since last set()
     */
    class Stopwatch {
    public:
        Stopwatch();
        ~Stopwatch();

        /*!
         * @brief set the stopwatch to the current time
         */
        void set();

        /*!
         * @brief get time since last set()
         * @return time in ms
         */
        long elapsedMs();

        /*!
         * @brief get time since last set()
         * @return time in μs
         */
        long elapsedUs();

    private:
        struct timeval startTime;
    };
}

#endif //RTYPE_STOPWATCH_HH
