# OpenShores-IP-Patch
A client modification for the 2022 Shores of Hazeron MMO that adds an IP address input field, and redirects connections from the hardcoded *.hazeron.net to the entered IP address (or hostname).

The majority of the work is done in ASM client patches and Redirect.dll is just to offload a few functions. Moving more of the functionality to Redirect.dll requires importing the same exact Qt SDK as the original client, which appears to be Qt 5.8.0, along with MSVC v140 (2015).
