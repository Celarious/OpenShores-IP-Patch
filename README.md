# OpenShores-IP-Patch
A client modification for the 2022 Shores of Hazeron MMO that adds an IP address input field, and redirects connections from the hardcoded *.hazeron.net to the entered IP address (or hostname).

The majority of the work is done in ASM client patches and Redirect.dll (built from dllmain.cpp) is just to offload a few functions. Moving more of the functionality to Redirect.dll requires importing the same exact Qt SDK as the original client, which appears to be Qt 5.8.0, along with MSVC v140 (VS2015).

The plan is to produce an xdelta diff that shows the exact ASM changes made. Eventually, more would ideally be moved to our own separate custom DLL, however that requires matching the build toolchain first.
