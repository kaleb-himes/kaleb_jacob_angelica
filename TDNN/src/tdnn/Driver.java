/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tdnn;

import wincheck.Winchecker;

/**
 *
 * @author sweetness
 */
public class Driver {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        TDNN test = new TDNN(20, 40, 3);
        TDNN ran = new TDNN(20, 40, 3);
        test.train(60);

        //test trained network against random one
        int win = 0;
        for (int i = 0; i < 50; i++) {
            double[] board = new double[12 * 4];
            int player = (Math.random() > .5) ? 1 : 2;
            int player2 = (player == 1) ? 2 : 1;
            do {
                if (player == 1) {
                    board = test.exploit(player, board);
                    board = ran.random(player2, board);
                } else {
                    board = ran.random(player2, board);
                    board = test.exploit(player, board);
                }
            } while (Winchecker.check(board) < 0);
            System.out.println("Winner was player " + Winchecker.check(board) + " ai was " + player);
            System.out.println("Board State");
            int index = 0;
            for (int z = 0; z < 4; z++) {
                for (int h = 0; h < 12; h++) {
                    if (board[index] == 0) {
                        System.out.print(" 0.0");
                    } else {
                        System.out.print(" " + board[index]);
                    }
                    index++;
                }
                System.out.println("");
            }
            if (Winchecker.check(board) == player) {
                win++;
            }
        }
        System.out.println("percent won = " + (double)win / 50.0);

    }
}
