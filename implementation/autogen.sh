# If this is a source checkout then call autoreconf with error as well
mkdir config
touch config/config.rpath

if test -d .git; then
  WARNINGS="all,error"
else
  WARNINGS="all"
fi

autoreconf --install --force --verbose

#where: 
# --force rebuilds ./configure regardless
# --install copies some missing files to the directory including txt files

