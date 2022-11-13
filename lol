==128281== Memcheck, a memory error detector
==128281== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==128281== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==128281== Command: ./r-type_client
==128281== 
==128281== Invalid read of size 8
==128281==    at 0x40286C8: strncmp (strcmp.S:172)
==128281==    by 0x400668D: is_dst (dl-load.c:216)
==128281==    by 0x400810E: _dl_dst_count (dl-load.c:253)
==128281==    by 0x400810E: expand_dynamic_string_token (dl-load.c:395)
==128281==    by 0x40082B7: fillin_rpath.isra.0 (dl-load.c:483)
==128281==    by 0x4008602: decompose_rpath (dl-load.c:654)
==128281==    by 0x400ABF5: cache_rpath (dl-load.c:696)
==128281==    by 0x400ABF5: cache_rpath (dl-load.c:677)
==128281==    by 0x400ABF5: _dl_map_object (dl-load.c:2165)
==128281==    by 0x4003494: openaux (dl-deps.c:64)
==128281==    by 0x4EB7C27: _dl_catch_exception (dl-error-skeleton.c:208)
==128281==    by 0x4003C7B: _dl_map_object_deps (dl-deps.c:248)
==128281==    by 0x400EA0E: dl_open_worker_begin (dl-open.c:592)
==128281==    by 0x4EB7C27: _dl_catch_exception (dl-error-skeleton.c:208)
==128281==    by 0x400DF99: dl_open_worker (dl-open.c:782)
==128281==  Address 0x593ab29 is 9 bytes inside a block of size 15 alloc'd
==128281==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==128281==    by 0x40271FF: malloc (rtld-malloc.h:56)
==128281==    by 0x40271FF: strdup (strdup.c:42)
==128281==    by 0x4008594: decompose_rpath (dl-load.c:629)
==128281==    by 0x400ABF5: cache_rpath (dl-load.c:696)
==128281==    by 0x400ABF5: cache_rpath (dl-load.c:677)
==128281==    by 0x400ABF5: _dl_map_object (dl-load.c:2165)
==128281==    by 0x4003494: openaux (dl-deps.c:64)
==128281==    by 0x4EB7C27: _dl_catch_exception (dl-error-skeleton.c:208)
==128281==    by 0x4003C7B: _dl_map_object_deps (dl-deps.c:248)
==128281==    by 0x400EA0E: dl_open_worker_begin (dl-open.c:592)
==128281==    by 0x4EB7C27: _dl_catch_exception (dl-error-skeleton.c:208)
==128281==    by 0x400DF99: dl_open_worker (dl-open.c:782)
==128281==    by 0x4EB7C27: _dl_catch_exception (dl-error-skeleton.c:208)
==128281==    by 0x400E34D: _dl_open (dl-open.c:883)
==128281== 
==128281== Invalid read of size 8
==128281==    at 0x40286C8: strncmp (strcmp.S:172)
==128281==    by 0x400668D: is_dst (dl-load.c:216)
==128281==    by 0x4007F79: _dl_dst_substitute (dl-load.c:295)
==128281==    by 0x40082B7: fillin_rpath.isra.0 (dl-load.c:483)
==128281==    by 0x4008602: decompose_rpath (dl-load.c:654)
==128281==    by 0x400ABF5: cache_rpath (dl-load.c:696)
==128281==    by 0x400ABF5: cache_rpath (dl-load.c:677)
==128281==    by 0x400ABF5: _dl_map_object (dl-load.c:2165)
==128281==    by 0x4003494: openaux (dl-deps.c:64)
==128281==    by 0x4EB7C27: _dl_catch_exception (dl-error-skeleton.c:208)
==128281==    by 0x4003C7B: _dl_map_object_deps (dl-deps.c:248)
==128281==    by 0x400EA0E: dl_open_worker_begin (dl-open.c:592)
==128281==    by 0x4EB7C27: _dl_catch_exception (dl-error-skeleton.c:208)
==128281==    by 0x400DF99: dl_open_worker (dl-open.c:782)
==128281==  Address 0x593ab29 is 9 bytes inside a block of size 15 alloc'd
==128281==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==128281==    by 0x40271FF: malloc (rtld-malloc.h:56)
==128281==    by 0x40271FF: strdup (strdup.c:42)
==128281==    by 0x4008594: decompose_rpath (dl-load.c:629)
==128281==    by 0x400ABF5: cache_rpath (dl-load.c:696)
==128281==    by 0x400ABF5: cache_rpath (dl-load.c:677)
==128281==    by 0x400ABF5: _dl_map_object (dl-load.c:2165)
==128281==    by 0x4003494: openaux (dl-deps.c:64)
==128281==    by 0x4EB7C27: _dl_catch_exception (dl-error-skeleton.c:208)
==128281==    by 0x4003C7B: _dl_map_object_deps (dl-deps.c:248)
==128281==    by 0x400EA0E: dl_open_worker_begin (dl-open.c:592)
==128281==    by 0x4EB7C27: _dl_catch_exception (dl-error-skeleton.c:208)
==128281==    by 0x400DF99: dl_open_worker (dl-open.c:782)
==128281==    by 0x4EB7C27: _dl_catch_exception (dl-error-skeleton.c:208)
==128281==    by 0x400E34D: _dl_open (dl-open.c:883)
==128281== 
Failed to load image "R-Type/Assets/Sprites/Bonus". Reason: Image not of any known type, or corrupt
Failed to load image "R-Type/Assets/Sprites/CthulhuEye". Reason: Image not of any known type, or corrupt
Failed to load image "R-Type/Assets/Sprites/Parallax". Reason: Image not of any known type, or corrupt
Failed to load image "R-Type/Assets/Sprites/zDevourerOfGods". Reason: Image not of any known type, or corrupt
==128281== Syscall param socketcall.recvfrom(buf) points to unaddressable byte(s)
==128281==    at 0x4E6A86E: __libc_recv (recv.c:28)
==128281==    by 0x4E6A86E: recv (recv.c:23)
==128281==    by 0x13052E: recv (socket2.h:38)
==128281==    by 0x13052E: recv1 (socket_ops.ipp:811)
==128281==    by 0x13052E: sync_recv1 (socket_ops.ipp:882)
==128281==    by 0x13052E: receive<boost::asio::mutable_buffers_1> (reactive_socket_service_base.hpp:364)
==128281==    by 0x13052E: unsigned long boost::asio::basic_stream_socket<boost::asio::ip::tcp, boost::asio::any_io_executor>::read_some<boost::asio::mutable_buffers_1>(boost::asio::mutable_buffers_1 const&) [clone .isra.0] (basic_stream_socket.hpp:1008)
==128281==    by 0x130F29: eng::ClientNetwork::initClientNetwork() (ClientNetwork.cpp:34)
==128281==    by 0x13194A: eng::ClientNetwork::ClientNetwork(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, unsigned short) (ClientNetwork.cpp:11)
==128281==    by 0x124F06: make_unique<eng::ClientNetwork, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (unique_ptr.h:962)
==128281==    by 0x124F06: eng::Client::createNetwork() (Client.cpp:14)
==128281==    by 0x126AC1: eng::Client::updateNetwork() (Client.cpp:126)
==128281==    by 0x12797A: eng::Client::mainLoop() (Client.cpp:264)
==128281==    by 0x1218E3: main (main.cpp:22)
==128281==  Address 0x2707a8a8 is 0 bytes after a block of size 168 alloc'd
==128281==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==128281==    by 0x124EF5: make_unique<eng::ClientNetwork, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (unique_ptr.h:962)
==128281==    by 0x124EF5: eng::Client::createNetwork() (Client.cpp:14)
==128281==    by 0x126AC1: eng::Client::updateNetwork() (Client.cpp:126)
==128281==    by 0x12797A: eng::Client::mainLoop() (Client.cpp:264)
==128281==    by 0x1218E3: main (main.cpp:22)
==128281== 
==128281== 
==128281== HEAP SUMMARY:
==128281==     in use at exit: 328,135 bytes in 3,624 blocks
==128281==   total heap usage: 564,393 allocs, 560,769 frees, 1,081,309,997 bytes allocated
==128281== 
==128281== LEAK SUMMARY:
==128281==    definitely lost: 0 bytes in 0 blocks
==128281==    indirectly lost: 0 bytes in 0 blocks
==128281==      possibly lost: 0 bytes in 0 blocks
==128281==    still reachable: 328,135 bytes in 3,624 blocks
==128281==         suppressed: 0 bytes in 0 blocks
==128281== Rerun with --leak-check=full to see details of leaked memory
==128281== 
==128281== For lists of detected and suppressed errors, rerun with: -s
==128281== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
