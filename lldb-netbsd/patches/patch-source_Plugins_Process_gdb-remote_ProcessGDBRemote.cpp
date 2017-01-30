$NetBSD$

--- source/Plugins/Process/gdb-remote/ProcessGDBRemote.cpp.orig	2016-12-17 10:30:03.000000000 +0000
+++ source/Plugins/Process/gdb-remote/ProcessGDBRemote.cpp
@@ -81,11 +81,13 @@
 
 #include "llvm/ADT/StringSwitch.h"
 #include "llvm/Support/raw_ostream.h"
+#include "llvm/Support/Threading.h"
 
 #define DEBUGSERVER_BASENAME "debugserver"
 using namespace lldb;
 using namespace lldb_private;
 using namespace lldb_private::process_gdb_remote;
+using namespace llvm;
 
 namespace lldb {
 // Provide a function that can easily dump the packet history if we know a
@@ -3427,9 +3429,9 @@ void ProcessGDBRemote::KillDebugserverPr
 }
 
 void ProcessGDBRemote::Initialize() {
-  static std::once_flag g_once_flag;
+  LLVM_DEFINE_ONCE_FLAG(g_once_flag);
 
-  std::call_once(g_once_flag, []() {
+  llvm::call_once(g_once_flag, []() {
     PluginManager::RegisterPlugin(GetPluginNameStatic(),
                                   GetPluginDescriptionStatic(), CreateInstance,
                                   DebuggerInitialize);