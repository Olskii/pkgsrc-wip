$NetBSD$

--- src/Native/System.Native/pal_networking.cpp.orig	2016-02-08 16:12:54.000000000 +0000
+++ src/Native/System.Native/pal_networking.cpp
@@ -381,7 +381,138 @@ static void ConvertHostEntPlatformToPal(
     }
 }
 
-#if HAVE_GETHOSTBYNAME_R
+#if defined(HAVE_GETNAMEINFO) || defined(HAVE_GETADDRINFO)
+#define BUFFER_OVERFLOW 255
+static int copy_hostent(struct hostent* from, struct hostent* to,
+                        char* buffer, size_t buflen, int* error)
+{
+    int i, len;
+    char* ptr = buffer;
+
+    *error = 0;
+    to->h_addrtype = from->h_addrtype;
+    to->h_length = from->h_length;
+    to->h_name = static_cast<char*>(ptr);
+
+    /* copy hostname to buffer */
+    len= static_cast<int>(strlen(from->h_name)+1);
+    strcpy(ptr, from->h_name);
+    ptr += len;
+
+    /* copy aliases to buffer */
+    to->h_aliases = reinterpret_cast<char**>(ptr);
+    for(i = 0; from->h_aliases[i]; i++);
+    ptr += (i+1) * static_cast<int>(sizeof(char*));
+
+    for(i = 0; from->h_aliases[i]; i++)
+    {
+        len = static_cast<int>(strlen(from->h_aliases[i])+1);
+        if (static_cast<size_t>((ptr-buffer)+len) < buflen)
+        {
+            to->h_aliases[i] = ptr;
+            strcpy(ptr, from->h_aliases[i]);
+            ptr += len;
+        }
+        else
+        {
+            *error = BUFFER_OVERFLOW;
+            return *error;
+        }
+    }
+    to->h_aliases[i] = NULL;
+
+    /* copy addr_list to buffer */
+    to->h_addr_list = reinterpret_cast<char**>(ptr);
+    for(i = 0; reinterpret_cast<int*>(from->h_addr_list[i]) != 0; i++);
+    ptr += (i+1) * static_cast<int>(sizeof(int*));
+
+    for(i = 0; reinterpret_cast<int*>(from->h_addr_list[i]) != 0; i++)
+    {
+        len = sizeof(int);
+        if (static_cast<size_t>((ptr-buffer)+len) < buflen)
+        {
+            to->h_addr_list[i] = ptr;
+            memcpy(ptr, from->h_addr_list[i], static_cast<size_t>(len));
+            ptr += len;
+        }
+        else
+        {
+            *error = BUFFER_OVERFLOW;
+            return *error;
+        }
+    }
+    to->h_addr_list[i] = 0;
+    return *error;
+}
+#endif /* defined(HAVE_GETNAMEINFO) || defined(HAVE_GETADDRINFO) */
+
+#if defined(HAVE_GETNAMEINFO)
+static int gethostbyname_r(char const* hostname, struct hostent* result,
+                                       char* buffer, size_t buflen, hostent** entry, int* error)
+{
+#ifdef HAVE_PTHREAD_H
+    if (fr_hostbyname == 0)
+    {
+        pthread_mutex_init(&fr_hostbyname_mutex, NULL);
+        fr_hostbyname = 1;
+    }
+    pthread_mutex_lock(&fr_hostbyname_mutex);
+#endif
+
+    *entry = gethostbyname(hostname);
+    if ((!(*entry)) || ((*entry)->h_addrtype != AF_INET) || ((*entry)->h_length != 4))
+    {
+         *error = h_errno;
+         *entry = NULL;
+    }
+    else
+    {
+         copy_hostent(*entry, result, buffer, buflen, error);
+         *entry = result;
+    }
+
+#ifdef HAVE_PTHREAD_H
+    pthread_mutex_unlock(&fr_hostbyname_mutex);
+#endif
+
+    return h_errno;
+}
+#endif /* defined(HAVE_GETNAMEINFO) */
+
+#if defined(HAVE_GETADDRINFO)
+static int gethostbyaddr_r(const uint8_t* addr, const socklen_t len, int type, struct hostent* result,
+                           char* buffer, size_t buflen, hostent** entry, int* error)
+{
+#ifdef HAVE_PTHREAD_H
+    if (fr_hostbyaddr == 0)
+    {
+        pthread_mutex_init(&fr_hostbyaddr_mutex, NULL);
+        fr_hostbyaddr = 1;
+    }
+    pthread_mutex_lock(&fr_hostbyaddr_mutex);
+#endif
+
+    *entry = gethostbyaddr(reinterpret_cast<const char*>(addr), static_cast<unsigned int>(len), type);
+    if ((!(*entry)) || ((*entry)->h_addrtype != AF_INET) || ((*entry)->h_length != 4))
+    {
+         *error = h_errno;
+         *entry = nullptr;
+    }
+    else
+    {
+         copy_hostent(*entry, result, buffer, buflen, error);
+         *entry = result;
+    }
+
+#ifdef HAVE_PTHREAD_H
+    pthread_mutex_unlock(&fr_hostbyaddr_mutex);
+#endif
+
+    return h_errno;
+}
+#endif /* defined(HAVE_GETADDRINFO) */
+
+#if defined(HAVE_GETHOSTBYNAME_R) || defined(HAVE_GETNAMEINFO)
 static int GetHostByNameHelper(const uint8_t* hostname, hostent** entry)
 {
     assert(hostname != nullptr);
@@ -421,7 +552,7 @@ static int GetHostByNameHelper(const uin
         }
     }
 }
-#endif
+#endif /* defined(HAVE_GETHOSTBYNAME_R) || defined(HAVE_GETNAMEINFO) */
 
 extern "C" int32_t SystemNative_GetHostByName(const uint8_t* hostname, HostEntry* entry)
 {
@@ -436,7 +567,7 @@ extern "C" int32_t SystemNative_GetHostB
 #if HAVE_THREAD_SAFE_GETHOSTBYNAME_AND_GETHOSTBYADDR
     hostEntry = gethostbyname(reinterpret_cast<const char*>(hostname));
     error = h_errno;
-#elif HAVE_GETHOSTBYNAME_R
+#elif HAVE_GETHOSTBYNAME_R || HAVE_GETADDRINFO
     error = GetHostByNameHelper(hostname, &hostEntry);
 #else
 #error Platform does not provide thread-safe gethostbyname
@@ -451,7 +582,7 @@ extern "C" int32_t SystemNative_GetHostB
     return PAL_SUCCESS;
 }
 
-#if HAVE_GETHOSTBYADDR_R
+#if defined(HAVE_GETHOSTBYADDR_R) || defined(HAVE_HOSTADDRINFO)
 static int GetHostByAddrHelper(const uint8_t* addr, const socklen_t addrLen, int type, hostent** entry)
 {
     assert(addr != nullptr);
@@ -491,7 +622,7 @@ static int GetHostByAddrHelper(const uin
         }
     }
 }
-#endif
+#endif /* defined(HAVE_GETHOSTBYADDR_R) || defined(HAVE_HOSTADDRINFO) */
 
 extern "C" int32_t SystemNative_GetHostByAddress(const IPAddress* address, HostEntry* entry)
 {
@@ -1188,7 +1319,11 @@ extern "C" Error SystemNative_GetIPv4Mul
         return PAL_EINVAL;
     }
 
+#if HAVE_IP_MREQ
+    ip_mreq opt;
+#elif HAVE_IP_MREQN
     ip_mreqn opt;
+#endif
     socklen_t len = sizeof(opt);
     int err = getsockopt(socket, IPPROTO_IP, optionName, &opt, &len);
     if (err != 0)
@@ -1197,8 +1332,12 @@ extern "C" Error SystemNative_GetIPv4Mul
     }
 
     *option = {.MulticastAddress = opt.imr_multiaddr.s_addr,
+#if HAVE_IP_MREQ
+               .LocalAddress = opt.imr_interface.s_addr};
+#elif HAVE_IP_MREQN
                .LocalAddress = opt.imr_address.s_addr,
                .InterfaceIndex = opt.imr_ifindex};
+#endif
     return PAL_SUCCESS;
 }
 
@@ -1215,9 +1354,14 @@ extern "C" Error SystemNative_SetIPv4Mul
         return PAL_EINVAL;
     }
 
+#if HAVE_IP_MREQ
+    ip_mreq opt = {.imr_multiaddr = {.s_addr = option->MulticastAddress},
+                   .imr_interface = {.s_addr = option->LocalAddress}};
+#elif HAVE_IP_MREQN
     ip_mreqn opt = {.imr_multiaddr = {.s_addr = option->MulticastAddress},
                     .imr_address = {.s_addr = option->LocalAddress},
                     .imr_ifindex = option->InterfaceIndex};
+#endif
     int err = setsockopt(socket, IPPROTO_IP, optionName, &opt, sizeof(opt));
     return err == 0 ? PAL_SUCCESS : SystemNative_ConvertErrorPlatformToPal(errno);
 }
@@ -1729,21 +1873,29 @@ static bool TryGetPlatformSocketOption(i
 
                 // case PAL_SO_IP_DONTFRAGMENT:
 
+#ifdef IP_ADD_SOURCE_MEMBERSHIP
                 case PAL_SO_IP_ADD_SOURCE_MEMBERSHIP:
                     optName = IP_ADD_SOURCE_MEMBERSHIP;
                     return true;
+#endif
 
+#ifdef IP_DROP_SOURCE_MEMBERSHIP
                 case PAL_SO_IP_DROP_SOURCE_MEMBERSHIP:
                     optName = IP_DROP_SOURCE_MEMBERSHIP;
                     return true;
+#endif
 
+#ifdef IP_BLOCK_SOURCE
                 case PAL_SO_IP_BLOCK_SOURCE:
                     optName = IP_BLOCK_SOURCE;
                     return true;
+#endif
 
+#ifdef IP_UNBLOCK_SOURCE
                 case PAL_SO_IP_UNBLOCK_SOURCE:
                     optName = IP_UNBLOCK_SOURCE;
                     return true;
+#endif
 
                 case PAL_SO_IP_PKTINFO:
                     optName = IP_PKTINFO;
@@ -2317,8 +2469,13 @@ static Error CloseSocketEventPortInner(i
 static Error TryChangeSocketEventRegistrationInner(
     int32_t port, int32_t socket, SocketEvents currentEvents, SocketEvents newEvents, uintptr_t data)
 {
+#ifdef EV_RECEIPT
     const uint16_t AddFlags = EV_ADD | EV_CLEAR | EV_RECEIPT;
     const uint16_t RemoveFlags = EV_DELETE | EV_RECEIPT;
+#else
+    const uint16_t AddFlags = EV_ADD | EV_CLEAR;
+    const uint16_t RemoveFlags = EV_DELETE;
+#endif
 
     assert(currentEvents != newEvents);
 
@@ -2331,6 +2488,15 @@ static Error TryChangeSocketEventRegistr
     int i = 0;
     if (readChanged)
     {
+#if KEVENT_HAS_NUMERIC_DATA
+        EV_SET(&events[i++],
+               static_cast<uint64_t>(socket),
+               EVFILT_READ,
+               (newEvents & PAL_SA_READ) == 0 ? RemoveFlags : AddFlags,
+               0,
+               0,
+               data);
+#else
         EV_SET(&events[i++],
                static_cast<uint64_t>(socket),
                EVFILT_READ,
@@ -2338,6 +2504,7 @@ static Error TryChangeSocketEventRegistr
                0,
                0,
                reinterpret_cast<void*>(data));
+#endif
     }
 
     if (writeChanged)
@@ -2348,11 +2515,15 @@ static Error TryChangeSocketEventRegistr
                (newEvents & PAL_SA_WRITE) == 0 ? RemoveFlags : AddFlags,
                0,
                0,
-               reinterpret_cast<void*>(data));
+               data);
     }
 
     int err;
+#if KEVENT_REQUIRES_SIZE_T_NUMERICS
+    while (CheckInterrupted(err = kevent(port, events, static_cast<size_t>(i), nullptr, 0, nullptr)));
+#else
     while (CheckInterrupted(err = kevent(port, events, i, nullptr, 0, nullptr)));
+#endif
     return err == 0 ? PAL_SUCCESS : SystemNative_ConvertErrorPlatformToPal(errno);
 }
 
@@ -2364,7 +2535,11 @@ static Error WaitForSocketEventsInner(in
 
     auto* events = reinterpret_cast<struct kevent*>(buffer);
     int numEvents;
+#if KEVENT_REQUIRES_SIZE_T_NUMERICS
+    while (CheckInterrupted(numEvents = kevent(port, nullptr, 0, events, static_cast<size_t>(*count), nullptr)));
+#else
     while (CheckInterrupted(numEvents = kevent(port, nullptr, 0, events, *count, nullptr)));
+#endif
     if (numEvents == -1)
     {
         *count = -1;
@@ -2382,7 +2557,11 @@ static Error WaitForSocketEventsInner(in
     {
         // This copy is made deliberately to avoid overwriting data.
         struct kevent evt = events[i];
+#if KEVENT_HAS_NUMERIC_DATA
+        buffer[i] = {.Data = static_cast<unsigned long>(evt.udata), .Events = GetSocketEvents(static_cast<short>(evt.filter), static_cast<unsigned short>(evt.flags))};
+#else
         buffer[i] = {.Data = reinterpret_cast<uintptr_t>(evt.udata), .Events = GetSocketEvents(evt.filter, evt.flags)};
+#endif
     }
 
     *count = numEvents;