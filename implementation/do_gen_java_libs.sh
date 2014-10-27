cd game/
javac gui/Main.java 
javah -d ../libs gui.JavaPasser
#in the AI directory
cd AI
javac *.java
javah -d ../../libs JavaTDNN
javah -d ../../libs JavaClassifier
cd ../util
javac *.java
javah -d ../../libs JavaWinChecker
cd ../../
#back in the implementation directory
#/ creates function prototype for the "pass" method /#
#/ create the header /#
#/ compile the main program /#
