//
// Created by drouar_b on 12/19/16.
//

#ifndef CPP_RTYPE_ISTOPWATCH_HH
#define CPP_RTYPE_ISTOPWATCH_HH

namespace helpers {
    /*!
     * @class IStopwatch
     * @brief Count time since last set()
     */
    class IStopwatch {
    public:
        virtual ~IStopwatch() { }
        /*!
         * @brief Set the stopwatch to the current time
         */
        virtual void set() = 0;
        /*!
         * @brief Get time since last set()
         * @return time in ms
         */
        virtual long elapsedMs() = 0;

        static IStopwatch *getInstance();
    };
}

#endif //CPP_RTYPE_ISTOPWATCH_HH
