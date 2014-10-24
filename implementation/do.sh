javac *.java
javah JavaWinChecker
#in the AI directory
cd AI
javac *.java
javah JavaTDNN
javah JavaClassifier
cd ..
#back in the implementation directory
#/ creates function prototype for the "pass" method /#
javac -d  gui.Main
#/ create the header /#
javah -jni gui.JavaPasser
#/ compile the main program /#
make
