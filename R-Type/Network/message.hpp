#pragma once

#include "common.hpp"

namespace net
{
    //$----------- Header message ------------$//

    /// @brief Define the message header
    /// @tparam T
    template <typename T> struct msg_header {
            T id{};
            uint32_t size = 0;
    };

    //$----------- Message packet ------------$//

    /// @brief Define the message packet
    /// @tparam T
    template <typename T> struct message {
            msg_header<T> header{};
            std::vector<uint8_t> body;

            //$--------------------- Methods -----------------------$//

            /// @brief Get the size of the message packet
            /// @return size_t
            size_t size() const
            {
                return sizeof(msg_header<T>) + body.size();
            }

            /// @brief Overload the << operator to insert data into the message packet
            /// @tparam DataType
            /// @param msg
            /// @param data
            /// @return net::message<T> &
            template <typename DataType> friend message<T> &operator<<(message<T> &msg, DataType &data)
            {
                // Check that the type of the data being inserted is copyable at the compilation time
                static_assert(std::is_standard_layout<DataType>::value, "Data can only be a standard layout type");

                size_t bodySize = msg.body.size();
                msg.body.resize(bodySize + sizeof(DataType));
                std::memcpy(msg.body.data() + bodySize, &data, sizeof(DataType));
                msg.header.size = msg.size();
                return msg;
            }

            /// @brief Overload the >> operator to extract data from the message packet
            /// @tparam DataType
            /// @param msg
            /// @param data
            /// @return net::message<T> &
            template <typename DataType> friend message<T> &operator>>(message<T> &msg, DataType &data)
            {
                // Check that the type of the data being extracted is copyable at the compilation time
                static_assert(std::is_standard_layout<DataType>::value, "Data can only be a standard layout type");

                size_t bodySize = msg.body.size() - sizeof(DataType);
                std::memcpy(&data, msg.body.data() + bodySize, sizeof(DataType));
                msg.body.resize(bodySize);
                msg.header.size = msg.size();
                return msg;
            }
    };

    //$----------- Message Owned (to ping back) ------------$//

    template <typename T> struct owned_message {
            std::shared_ptr<connection<T>> remote = nullptr;
            message<T> msg;
    };

} // namespace net