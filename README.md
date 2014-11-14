kaleb_jacob_angelica
====================

Use this to get the libgtk2.0 headers and files installed:

The following will need to be done prior to running ./autogen.sh ...

cd /etc/ld.so.conf.d
sudo touch your.conf
sudo vim your.conf

echo "/usr/<java_home_dir>/<java version>/include > /etc/ld.so.conf.d/your.conf
sudo ldconfig

for example on my system it looks like this:
-------------------------------------------------------------------------------
 echo "/usr/lib/jvm/java-7-openjdk-i386/include" > /etc/ld.so.conf.d/kaleb.conf
 sudo ldconfig
------------------------------------------------------------------------------- 

##TODO list : Put name next to task as soon as it's started
* Look at potential utilities needed then update list ie stack, queue, priority queue
* Skeletan functions of first AI requirement
* 
*
