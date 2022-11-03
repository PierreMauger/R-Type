/**
 * @file Queue.hpp
 * @authors Pierre HAMEL • Dorian AYOUL • Jean-Baptiste BROCHERIE • Pierre MAUGER • Xavier TONNELLIER
 * @brief The network queue.
 * @copyright Epitech Rennes 2022
 */

#ifndef QUEUE_HPP_
#define QUEUE_HPP_

/// @cond
#include "NetCommon.hpp"
/// @endcond

/**
 * @brief The network queue.
 * @class Queue
 */
template <typename T> class Queue
{
    protected:
        std::mutex _mutex;
        std::deque<T> _queue;

    public:
        /**
         * @brief Queue destructor.
         * @fn ~Queue()
         */
        virtual ~Queue()
        {
            clear();
        }

        /**
         * @brief Put an element at the front.
         * @fn T &front()
         * @return The type of value to put at the front.
         */
        T &front()
        {
            std::scoped_lock lock(this->_mutex);
            return this->_queue.front();
        }

        /**
         * @brief Put an element at the back.
         * @fn T &back()
         * @return The type of value to put at the back.
         */
        T &back()
        {
            std::scoped_lock lock(this->_mutex);
            return this->_queue.back();
        }

        /**
         * @brief Push an element at the front.
         * @fn void push_front(T value)
         * @param value The value tu push at the front.
         */
        void push_front(T value)
        {
            std::scoped_lock lock(this->_mutex);
            this->_queue.push_front(value);
        }

        /**
         * @brief Push an element at the back.
         * @fn void push_back(T value)
         * @param value The value tu push at the back.
         */
        void push_back(T value)
        {
            std::scoped_lock lock(this->_mutex);
            this->_queue.push_back(value);
        }

        /**
         * @brief Pop an element at the front.
         * @fn T pop_front()
         * @return The type of value to pop at the front.
         */
        T pop_front()
        {
            std::scoped_lock lock(this->_mutex);
            T value = this->_queue.front();
            this->_queue.pop_front();
            return value;
        }

        /**
         * @brief Pop an element at the back.
         * @fn T pop_back()
         * @return The type of value to pop at the back.
         */
        T pop_back()
        {
            std::scoped_lock lock(this->_mutex);
            T value = this->_queue.back();
            this->_queue.pop_back();
            return value;
        }

        /**
         * @brief Check if the queue is empty.
         * @fn bool empty()
         * @return A boolean about if the queue is empty.
         */
        bool empty()
        {
            std::scoped_lock lock(this->_mutex);
            return this->_queue.empty();
        }

        /**
         * @brief Get the size of the queue.
         * @fn size_t size()
         * @return The size of the queue.
         */
        size_t size()
        {
            std::scoped_lock lock(this->_mutex);
            return this->_queue.size();
        }

        /**
         * @brief Clear the queue.
         * @fn void clear()
         */
        void clear()
        {
            std::scoped_lock lock(this->_mutex);
            this->_queue.clear();
        }
};

#endif /* !QUEUE_HPP_ */
