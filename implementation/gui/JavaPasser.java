package gui;
/**
 *
 * @author khimes
 */
public class JavaPasser {
    static {System.loadLibrary("PassImpl");}
    
    public static native void pass(int pass_x, int pass_y, char pass_player);

}
