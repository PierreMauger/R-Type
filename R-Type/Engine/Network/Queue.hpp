#ifndef QUEUE_HPP_
#define QUEUE_HPP_

#include "NetCommon.hpp"

template <typename T> class Queue
{
    protected:
        std::mutex _mutex;
        std::deque<T> _queue;

    public:
        virtual ~Queue()
        {
            clear();
        }

        T &front()
        {
            std::scoped_lock lock(this->_mutex);
            return this->_queue.front();
        }

        T &back()
        {
            std::scoped_lock lock(this->_mutex);
            return this->_queue.back();
        }

        void push_front(T value)
        {
            std::scoped_lock lock(this->_mutex);
            this->_queue.push_front(value);
        }

        void push_back(T value)
        {
            std::scoped_lock lock(this->_mutex);
            this->_queue.push_back(value);
        }

        T pop_front()
        {
            std::scoped_lock lock(this->_mutex);
            T value = this->_queue.front();
            this->_queue.pop_front();
            return value;
        }

        T pop_back()
        {
            std::scoped_lock lock(this->_mutex);
            T value = this->_queue.back();
            this->_queue.pop_back();
            return value;
        }

        bool empty()
        {
            std::scoped_lock lock(this->_mutex);
            return this->_queue.empty();
        }

        size_t size()
        {
            std::scoped_lock lock(this->_mutex);
            return this->_queue.size();
        }

        void clear()
        {
            std::scoped_lock lock(this->_mutex);
            this->_queue.clear();
        }
};

#endif /* !QUEUE_HPP_ */