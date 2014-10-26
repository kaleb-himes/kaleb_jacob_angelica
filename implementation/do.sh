javac *.java
javah -d libs JavaWinChecker
#in the AI directory
cd AI
javac *.java
javah -d ../libs JavaTDNN
javah -d ../libs JavaClassifier
cd ..
#back in the implementation directory
#/ creates function prototype for the "pass" method /#
javac gui/Main.java
#/ create the header /#
javah -d libs gui.JavaPasser
#/ compile the main program /#
make
