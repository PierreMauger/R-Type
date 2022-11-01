#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Includes.hpp"

/**
 * @brief Engine namespace.
 * @namespace eng
 */
namespace eng

{
    /**
     * @brief The Engine's level.
     * @class Level
     */
    class Level
    {
        private:
            std::size_t _index;
            std::string _level;
            float _speedRead;

        public:
            /**
             * @brief Level constructor.
             * @fn Level()
             */
            Level();
            Level(std::vector<std::string> lines);
            /**
             * @brief Level destructor.
             * @fn ~Level()
             */
            ~Level() = default;
    };
}

#endif // LEVEL_HPP