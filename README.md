# OpenShores-IP-Patch
A client modification for the 2018 (13n60) Shores of Hazeron MMO that adds an IP address input field, and redirects connections from the hardcoded *.hazeron.net to the entered IP address (or hostname).

![IP input field pic](docs/Shores_of_Hazeron_Patched_nuFGN6YpUe.png)

The modification also stores the user-entered IP/host in the registry and restores it on client restart, just like with username and password for convenience.

The majority of the work is done in ASM client patches and Redirect.dll (built from dllmain.cpp) is just to offload a few functions. Moving more of the functionality to Redirect.dll requires importing the same exact Qt SDK as the original client, which appears to be Qt 5.8.0, along with MSVC v140 (VS2015).

The plan is to ideally move the ASM code to our own separate custom DLL, however that requires matching the build toolchain first.

To use the xdelta files, simply apply SoH_delta to Deantwo's original 2018 SoH .exe and auloginclient_delta to Deantwo's original 2018 AuLoginClient13.dll

Might eventually create a patcher that automatically applies the xdeltas and redirect.dll to an existing copy of the 2018 client

The .cave PE section is added with CFF explorer, and it's very small, meaning the exe does not meaningfully increase in size

This was my first reverse engineering/asm project of any kind, I fumbled my way through all of it with the help of chatgpt
