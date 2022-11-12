==75133== Memcheck, a memory error detector
==75133== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==75133== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==75133== Command: ./r-type_client
==75133== 
==75133== Syscall param ioctl(generic) points to uninitialised byte(s)
==75133==    at 0x4E5DAFF: ioctl (ioctl.c:36)
==75133==    by 0x5D3A84F: drmIoctl (in /usr/lib/x86_64-linux-gnu/libdrm.so.2.4.0)
==75133==    by 0x5D3D8EF: drmCommandWriteRead (in /usr/lib/x86_64-linux-gnu/libdrm.so.2.4.0)
==75133==    by 0xD829B7B: ??? (in /usr/lib/x86_64-linux-gnu/libdrm_nouveau.so.2.0.0)
==75133==    by 0xD82ACDA: nouveau_device_new (in /usr/lib/x86_64-linux-gnu/libdrm_nouveau.so.2.0.0)
==75133==    by 0x66ECCB6: nouveau_drm_screen_create (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5E823BA: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x647A7EE: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5E858E3: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5E832A3: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5CCBF53: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==75133==    by 0x5CBD3B8: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==75133==  Address 0x5a21402 is 2 bytes inside a block of size 72 alloc'd
==75133==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==75133==    by 0xD829B27: ??? (in /usr/lib/x86_64-linux-gnu/libdrm_nouveau.so.2.0.0)
==75133==    by 0xD82ACDA: nouveau_device_new (in /usr/lib/x86_64-linux-gnu/libdrm_nouveau.so.2.0.0)
==75133==    by 0x66ECCB6: nouveau_drm_screen_create (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5E823BA: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x647A7EE: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5E858E3: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5E832A3: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5CCBF53: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==75133==    by 0x5CBD3B8: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==75133==    by 0x5CB9B1B: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==75133==    by 0x4A93BE8: glad_glx_has_extension (glx.h:827)
==75133==    by 0x4A93BE8: glad_glx_find_extensions(_XDisplay*, int) (glx.h:855)
==75133== 
==75133== Syscall param ioctl(generic) points to uninitialised byte(s)
==75133==    at 0x4E5DAFF: ioctl (ioctl.c:36)
==75133==    by 0x5D3A84F: drmIoctl (in /usr/lib/x86_64-linux-gnu/libdrm.so.2.4.0)
==75133==    by 0x5D3D8EF: drmCommandWriteRead (in /usr/lib/x86_64-linux-gnu/libdrm.so.2.4.0)
==75133==    by 0xD82A3A5: nouveau_object_mthd (in /usr/lib/x86_64-linux-gnu/libdrm_nouveau.so.2.0.0)
==75133==    by 0xD82ACF9: nouveau_device_new (in /usr/lib/x86_64-linux-gnu/libdrm_nouveau.so.2.0.0)
==75133==    by 0x66ECCB6: nouveau_drm_screen_create (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5E823BA: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x647A7EE: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5E858E3: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5E832A3: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5CCBF53: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==75133==    by 0x5CBD3B8: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==75133==  Address 0x5a21492 is 2 bytes inside a block of size 136 alloc'd
==75133==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==75133==    by 0xD82A366: nouveau_object_mthd (in /usr/lib/x86_64-linux-gnu/libdrm_nouveau.so.2.0.0)
==75133==    by 0xD82ACF9: nouveau_device_new (in /usr/lib/x86_64-linux-gnu/libdrm_nouveau.so.2.0.0)
==75133==    by 0x66ECCB6: nouveau_drm_screen_create (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5E823BA: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x647A7EE: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5E858E3: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5E832A3: ??? (in /usr/lib/x86_64-linux-gnu/dri/nouveau_dri.so)
==75133==    by 0x5CCBF53: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==75133==    by 0x5CBD3B8: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==75133==    by 0x5CB9B1B: ??? (in /usr/lib/x86_64-linux-gnu/libGLX_mesa.so.0.0.0)
==75133==    by 0x4A93BE8: glad_glx_has_extension (glx.h:827)
==75133==    by 0x4A93BE8: glad_glx_find_extensions(_XDisplay*, int) (glx.h:855)
==75133== 
Failed to load image "R-Type/Assets/Sprites/Bonus". Reason: Image not of any known type, or corrupt
Failed to load image "R-Type/Assets/Sprites/CthulhuEye". Reason: Image not of any known type, or corrupt
Failed to load image "R-Type/Assets/Sprites/Parallax". Reason: Image not of any known type, or corrupt
Failed to load image "R-Type/Assets/Sprites/zDevourerOfGods". Reason: Image not of any known type, or corrupt
==75133== Syscall param socketcall.recvfrom(buf) points to unaddressable byte(s)
==75133==    at 0x4E6A86E: __libc_recv (recv.c:28)
==75133==    by 0x4E6A86E: recv (recv.c:23)
==75133==    by 0x1305EE: recv (socket2.h:38)
==75133==    by 0x1305EE: recv1 (socket_ops.ipp:811)
==75133==    by 0x1305EE: sync_recv1 (socket_ops.ipp:882)
==75133==    by 0x1305EE: receive<boost::asio::mutable_buffers_1> (reactive_socket_service_base.hpp:364)
==75133==    by 0x1305EE: unsigned long boost::asio::basic_stream_socket<boost::asio::ip::tcp, boost::asio::any_io_executor>::read_some<boost::asio::mutable_buffers_1>(boost::asio::mutable_buffers_1 const&) [clone .isra.0] (basic_stream_socket.hpp:1008)
==75133==    by 0x130FE9: eng::ClientNetwork::initClientNetwork() (ClientNetwork.cpp:34)
==75133==    by 0x131A0A: eng::ClientNetwork::ClientNetwork(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, unsigned short) (ClientNetwork.cpp:11)
==75133==    by 0x125473: construct_at<eng::ClientNetwork, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (stl_construct.h:97)
==75133==    by 0x125473: construct<eng::ClientNetwork, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (alloc_traits.h:518)
==75133==    by 0x125473: _Sp_counted_ptr_inplace<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (shared_ptr_base.h:519)
==75133==    by 0x125473: __shared_count<eng::ClientNetwork, std::allocator<eng::ClientNetwork>, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (shared_ptr_base.h:650)
==75133==    by 0x125473: __shared_ptr<std::allocator<eng::ClientNetwork>, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (shared_ptr_base.h:1342)
==75133==    by 0x125473: shared_ptr<std::allocator<eng::ClientNetwork>, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (shared_ptr.h:409)
==75133==    by 0x125473: allocate_shared<eng::ClientNetwork, std::allocator<eng::ClientNetwork>, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (shared_ptr.h:863)
==75133==    by 0x125473: make_shared<eng::ClientNetwork, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (shared_ptr.h:879)
==75133==    by 0x125473: eng::Client::createNetwork() (Client.cpp:14)
==75133==    by 0x125F5E: eng::Client::updateKeys() (Client.cpp:206)
==75133==    by 0x127C42: eng::Client::mainLoop() (Client.cpp:261)
==75133==    by 0x121933: main (main.cpp:22)
==75133==  Address 0x22d75ed8 is 0 bytes after a block of size 184 alloc'd
==75133==    at 0x4849013: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==75133==    by 0x125416: allocate (new_allocator.h:127)
==75133==    by 0x125416: allocate (allocator.h:185)
==75133==    by 0x125416: allocate (alloc_traits.h:464)
==75133==    by 0x125416: __allocate_guarded<std::allocator<std::_Sp_counted_ptr_inplace<eng::ClientNetwork, std::allocator<eng::ClientNetwork>, (__gnu_cxx::_Lock_policy)2> > > (allocated_ptr.h:98)
==75133==    by 0x125416: __shared_count<eng::ClientNetwork, std::allocator<eng::ClientNetwork>, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (shared_ptr_base.h:648)
==75133==    by 0x125416: __shared_ptr<std::allocator<eng::ClientNetwork>, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (shared_ptr_base.h:1342)
==75133==    by 0x125416: shared_ptr<std::allocator<eng::ClientNetwork>, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (shared_ptr.h:409)
==75133==    by 0x125416: allocate_shared<eng::ClientNetwork, std::allocator<eng::ClientNetwork>, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (shared_ptr.h:863)
==75133==    by 0x125416: make_shared<eng::ClientNetwork, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&, long unsigned int&> (shared_ptr.h:879)
==75133==    by 0x125416: eng::Client::createNetwork() (Client.cpp:14)
==75133==    by 0x125F5E: eng::Client::updateKeys() (Client.cpp:206)
==75133==    by 0x127C42: eng::Client::mainLoop() (Client.cpp:261)
==75133==    by 0x121933: main (main.cpp:22)
==75133== 
==75133== 
==75133== HEAP SUMMARY:
==75133==     in use at exit: 325,396 bytes in 3,601 blocks
==75133==   total heap usage: 2,628,411 allocs, 2,624,810 frees, 3,691,017,375 bytes allocated
==75133== 
==75133== LEAK SUMMARY:
==75133==    definitely lost: 0 bytes in 0 blocks
==75133==    indirectly lost: 0 bytes in 0 blocks
==75133==      possibly lost: 304 bytes in 2 blocks
==75133==    still reachable: 325,092 bytes in 3,599 blocks
==75133==         suppressed: 0 bytes in 0 blocks
==75133== Rerun with --leak-check=full to see details of leaked memory
==75133== 
==75133== Use --track-origins=yes to see where uninitialised values come from
==75133== For lists of detected and suppressed errors, rerun with: -s
==75133== ERROR SUMMARY: 7 errors from 3 contexts (suppressed: 0 from 0)
