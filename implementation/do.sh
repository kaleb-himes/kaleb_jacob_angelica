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
javac gui/Main.java
#/ create the header /#
javah gui.JavaPasser
#/ compile the main program /#
make
