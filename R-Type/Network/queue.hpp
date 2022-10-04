#pragma once

#include "common.hpp"

namespace net {
    template<typename T> class queue {
        protected:
            std::mutex _mutex;
            std::deque<T> _queue;

        public:
            queue();
            virtual ~queue();
            T &front();
            T &back();
            void push_front(T value);
            void push_back(T value);
            T pop_front();
            T pop_back();
            bool empty();
            size_t size();
            void clear();
    };
} // namespace network