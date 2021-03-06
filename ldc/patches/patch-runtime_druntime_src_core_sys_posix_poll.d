$NetBSD$

Stolen from https://github.com/nrTQgc/druntime/tree/netbsd

--- runtime/druntime/src/core/sys/posix/poll.d.orig	2016-02-13 20:02:16.000000000 +0000
+++ runtime/druntime/src/core/sys/posix/poll.d
@@ -143,6 +143,41 @@ else version( FreeBSD )
 
     int poll(pollfd*, nfds_t, int);
 }
+else version( NetBSD )
+{
+    alias uint nfds_t;
+
+    struct pollfd
+    {
+        int     fd;
+        short   events;
+        short   revents;
+    };
+
+    enum
+    {
+        POLLIN      = 0x0001,
+        POLLPRI     = 0x0002,
+        POLLOUT     = 0x0004,
+        POLLRDNORM  = 0x0040,
+        POLLWRNORM  = POLLOUT,
+        POLLRDBAND  = 0x0080,
+        POLLWRBAND  = 0x0100,
+        //POLLEXTEND  = 0x0200,
+        //POLLATTRIB  = 0x0400,
+        //POLLNLINK   = 0x0800,
+        //POLLWRITE   = 0x1000,
+        POLLERR     = 0x0008,
+        POLLHUP     = 0x0010,
+        POLLNVAL    = 0x0020,
+
+        POLLSTANDARD = (POLLIN|POLLPRI|POLLOUT|POLLRDNORM|POLLRDBAND|
+        POLLWRBAND|POLLERR|POLLHUP|POLLNVAL)
+    }
+
+    int poll(pollfd*, nfds_t, int);
+}
+
 else version( Solaris )
 {
     alias c_ulong nfds_t;
