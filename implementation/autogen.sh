# If this is a source checkout then call autoreconf with error as well

# Generate the Java Headers if they don't already exist
./do_gen_java_libs.sh

# JAVA_INCLUDE_DIR="/usr/lib/jvm/java-7-openjdk-i386/include/"
# NEW_LIBRARY_LOC=/etc/ld.so.conf.d

CONFIG="config"
if [ ! -d "$CONFIG" ]; 
then
      # Control will enter here if $CONFIG doesn't exist.
      mkdir config
fi
touch config/config.rpath
# echo ""
# echo "A password prompt will appear. This is necessary"
# echo "to update your ldconfig to include java jni.h"
# echo ""

#add java lib to search path
# cd /etc/ld.so.conf.d
# sudo touch polarTTT.conf
# echo "$JAVA_INCLUDE_DIR" | sudo tee -a $NEW_LIBRARY_LOC/polarTTT.conf
# sudo ldconfig
# return to where we the bash is running from
# cd -

if test -d .git; then
  WARNINGS="all,error"
else
  WARNINGS="all"
fi

autoreconf --install --force --verbose -I m4

#where: 
# --force rebuilds ./configure regardless
# --install copies some missing files to the directory including txt files

