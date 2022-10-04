#include "queue.hpp"

//$----------- Constructors and destructors ------------$//

/// @brief Construct a new queue object
/// @tparam T
template <typename T> net::queue<T>::queue()
{
}

/// @brief Destroy the queue object
/// @tparam T
template <typename T> net::queue<T>::~queue()
{
    clear();
}

//$--------------------- Methods -----------------------$//

/// @brief Get the front object
/// @tparam T
/// @return T&
template <typename T> T &net::queue<T>::front()
{
    std::scoped_lock lock(this->_mutex);
    return this->_queue.front();
}

/// @brief Get the back object
/// @tparam T
/// @return T&
template <typename T> T &net::queue<T>::back()
{
    std::scoped_lock lock(this->_mutex);
    return this->_queue.back();
}

/// @brief Push a new value to the front of the queue
/// @tparam T
/// @param value
template <typename T> void net::queue<T>::push_front(T value)
{
    std::scoped_lock lock(this->_mutex);
    this->_queue.push_front(value);
}

/// @brief Push a new value to the back of the queue
/// @tparam T
/// @param value
template <typename T> void net::queue<T>::push_back(T value)
{
    std::scoped_lock lock(this->_mutex);
    this->_queue.push_back(value);
}

/// @brief Pop the front value from the queue
/// @tparam T
/// @return T
template <typename T> T net::queue<T>::pop_front()
{
    std::scoped_lock lock(this->_mutex);
    T value = this->_queue.front();
    this->_queue.pop_front();
    return value;
}

/// @brief Pop the back value from the queue
/// @tparam T
/// @return T
template <typename T> T net::queue<T>::pop_back()
{
    std::scoped_lock lock(this->_mutex);
    T value = this->_queue.back();
    this->_queue.pop_back();
    return value;
}

/// @brief Check if the queue is empty
/// @tparam T
/// @return bool
template <typename T> bool net::queue<T>::empty()
{
    std::scoped_lock lock(this->_mutex);
    return this->_queue.empty();
}

/// @brief Get the size of the queue
/// @tparam T
/// @return size_t
template <typename T> size_t net::queue<T>::size()
{
    std::scoped_lock lock(this->_mutex);
    return this->_queue.size();
}

/// @brief Clear the queue
/// @tparam T
template <typename T> void net::queue<T>::clear()
{
    std::scoped_lock lock(this->_mutex);
    this->_queue.clear();
}