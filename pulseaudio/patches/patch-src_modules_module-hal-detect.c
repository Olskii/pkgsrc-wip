$NetBSD: patch-src_modules_module-hal-detect.c,v 1.1 2012/10/08 12:58:37 ryo-on Exp $

--- src/modules/module-hal-detect.c.orig	2012-07-19 11:29:39.000000000 +0000
+++ src/modules/module-hal-detect.c
@@ -334,6 +334,11 @@ static int hal_device_load_oss(struct us
 
     /* We store only one entry per card, hence we look for the originating device */
     originating_udi = libhal_device_get_property_string(u->context, udi, "oss.originating_device", &error);
+    if (dbus_error_is_set(&error) || !originating_udi) {
+	if (dbus_error_is_set(&error))
+            dbus_error_free(&error);
+	originating_udi = libhal_device_get_property_string(u->context, udi, "sound.originating_device", &error);
+    }
     if (dbus_error_is_set(&error) || !originating_udi)
         goto fail;
 
