package gui;
/**
 *
 * @author Kaleb
 */
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;
import javax.swing.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;

@SuppressWarnings("serial")
public class Main extends JFrame {

    private JLabel ai_lbl;                        /* Label */
    private static JProgressBar ai_progress_bar;  /* AI progress bar */
    private JPanel ai_thinking_quit_panel;        /* Panel for ai elements */
    private static JButton ai_v_ai_but;           /* Button for game mode */
    private static JButton ai_v_human_but;        /* Button for game mode */
    private static JButton human_v_ai_but;        /* Button for game mode */
    private static JButton human_v_human_but;     /* Button for game mode */
    private static JPanel game_board_panel;       /* Display of the board */
    private static JTextArea game_state_display;  /* Text area */
    private JLabel game_state_lbl;                /* Label for Text area*/
    private JPanel game_state_panel;              /* Panel for state elements */
    private JScrollPane game_state_scrollpane;    /* Scroll pane, Long game */
    
    private JPanel options_panel;                 /* Panel for quit/replay */
    private static JButton play_again_but;        /* Button for replay */
    private static JButton quit_but;              /* Button for quit */

    /* Legal Move Coodinates in (x,y) format:
     * We will use these to judge if a move is legal and paint the pixels up,
     * down, left, right, these coordinates are the center of the legal location
     *   
     *    Starting between Quadrant 1 and 2 on the verticle "NORTH" Line and
     *    moving clockwise around the circle. Always starting on the inner 
     *    radial circle and going to outter radial circle:
     *   
     *    Quadrant One starting at "NORTH" Line
     *          (250,175)(250,125)(250,75)(250,25)   North Line ->
     *          (284,183)(308,139)(331,94)(355,50)   Top spoke of Q1
     *          (316,215)(362,193)(406,169)(449,146) Bottom spoke of Q1
     */
    int[] a1 = {250, 175, 0};
    int[] a2 = {250, 125, 0};
    int[] a3 = {250, 75, 0};
    int[] a4 = {250, 25, 0};
    int[] b1 = {284, 183, 0};
    int[] b2 = {308, 139, 0};
    int[] b3 = {331, 94, 0};
    int[] b4 = {355, 50, 0};
    int[] c1 = {316, 215, 0};
    int[] c2 = {362, 193, 0};
    int[] c3 = {406, 169, 0};
    int[] c4 = {449, 146, 0};
    /*   
     *    Quadrant Four
     *          (325,250)(375,250)(425,250)(475,250) East Line
     *          (317,284)(361,308)(406,332)(450,354) Top spoke of Q4
     *          (284,316)(308,360)(331,404)(354,449) Bottom spoke of Q4
     *   
     */
    int[] d1 = {325, 250, 0};
    int[] d2 = {375, 250, 0};
    int[] d3 = {425, 250, 0};
    int[] d4 = {475, 250, 0};
    int[] e1 = {317, 284, 0};
    int[] e2 = {361, 308, 0};
    int[] e3 = {406, 332, 0};
    int[] e4 = {450, 354, 0};
    int[] f1 = {284, 316, 0};
    int[] f2 = {308, 360, 0};
    int[] f3 = {331, 404, 0};
    int[] f4 = {354, 449, 0};
    /*    Quadrant Three
     *          (250,325)(250,375)(250,425)(250,475) South Line
     *          (215,316)(192,360)(169,405)(146,449) Bottom spoke of Q3
     *          (184,284)(140,308)(95,330)(50,354)   TOp spoke of Q3
     * 
     */
    int[] g1 = {250, 325, 0};
    int[] g2 = {250, 375, 0};
    int[] g3 = {250, 425, 0};
    int[] g4 = {250, 475, 0};
    int[] h1 = {215, 316, 0};
    int[] h2 = {192, 360, 0};
    int[] h3 = {169, 405, 0};
    int[] h4 = {146, 449, 0};
    int[] i1 = {184, 284, 0};
    int[] i2 = {140, 308, 0};
    int[] i3 = {95, 330, 0};
    int[] i4 = {50, 354, 0};
    /*    Quadrant Two 
     *          (175,250)(125,250)(75,250)(25,250)   West Line
     *          (184,216)(140,192)(95,170)(51,146)   Bottom spoke of Q2
     *          (216,184)(192,139)(169,95)(147,51)   Top spoke of Q2
     */
    int[] j1 = {175, 250, 0};
    int[] j2 = {125, 250, 0};
    int[] j3 = {75, 250, 0};
    int[] j4 = {25, 250, 0};
    int[] k1 = {184, 216, 0};
    int[] k2 = {140, 192, 0};
    int[] k3 = {95, 170, 0};
    int[] k4 = {51, 146, 0};
    int[] l1 = {216, 184, 0};
    int[] l2 = {192, 139, 0};
    int[] l3 = {169, 95, 0};
    int[] l4 = {147, 51, 0};

    /* An array to store moves that are legal or not legal */
    int[][] legal_moves = new int[][]{a1, a2, a3, a4, b1, b2, b3, b4, c1, c2,
        c3, c4, d1, d2, d3, d4, e1, e2, e3, e4,
        f1, f2, f3, f4, g1, g2, g3, g4, h1, h2,
        h3, h4, i1, i2, i3, i4, j1, j2, j3, j4,
        k1, k2, k3, k4, l1, l2, l3, l4};
    
    char player = 'X';
    ClassLoader cl;
    final BufferedImage playerX_img;
    final BufferedImage playerO_img;
    final BufferedImage game_over_img;
    private static MouseListener[] m1;
    private static MouseListener[] m2;
    private static MouseListener[] m3;
    private static MouseListener[] m4;
    private static MouseListener[] m5;

    public Main() throws IOException {
        this.playerX_img = ImageIO.read(new File
                                            ("resources/X.png"));
        this.playerO_img = ImageIO.read(new File
                                            ("resources/O.png"));
        this.game_over_img = ImageIO.read(new File
                                    ("resources/game_over.png"));
        initComponents();
    }

    @SuppressWarnings("unchecked")

    // <editor-fold defaultstate="collapsed" desc="GUI Code looks aweful... LET'S HIDE IT!">                          
    private void initComponents() {

        game_state_panel = new JPanel();
        game_state_lbl = new JLabel();
        game_state_scrollpane = new JScrollPane();
        game_state_display = new JTextArea();
        options_panel = new JPanel();
        human_v_ai_but = new JButton();
        ai_v_human_but = new JButton();
        human_v_human_but = new JButton();
        ai_v_ai_but = new JButton();
        ai_thinking_quit_panel = new JPanel();
        quit_but = new JButton();
        ai_progress_bar = new JProgressBar();
        ai_lbl = new JLabel();
        play_again_but = new JButton();
        game_board_panel = new JPanel();

        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);

        game_state_panel.setBorder(BorderFactory.createBevelBorder
        (javax.swing.border.BevelBorder.RAISED));

        game_state_lbl.setText("Current Game State");

        game_state_display.setColumns(20);
        game_state_display.setRows(5);
        game_state_display.setText("Select a game mode\nto begin!");
        game_state_display.setFocusable(false);
        game_state_scrollpane.setViewportView(game_state_display);

        GroupLayout game_state_panelLayout = new GroupLayout(game_state_panel);
        game_state_panel.setLayout(game_state_panelLayout);
        game_state_panelLayout.setHorizontalGroup
        (game_state_panelLayout.createParallelGroup
        (GroupLayout.Alignment.LEADING)
                .addGroup(GroupLayout.Alignment.TRAILING,
                        game_state_panelLayout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent
        (game_state_scrollpane, GroupLayout.DEFAULT_SIZE, 178, Short.MAX_VALUE)
                                .addContainerGap())
                .addGroup(GroupLayout.Alignment.TRAILING,
                        game_state_panelLayout.createSequentialGroup()
                        .addContainerGap
        (GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(game_state_lbl)
                        .addGap(49, 49, 49))
        );

        game_state_panelLayout.setVerticalGroup
        (game_state_panelLayout.createParallelGroup
        (GroupLayout.Alignment.LEADING)
                .addGroup(game_state_panelLayout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(game_state_lbl)
                        .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(game_state_scrollpane)
                        .addContainerGap())
        );

        human_v_ai_but.setText("Human vs AI");
        human_v_ai_but.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent evt) {
                human_v_ai_butMouseClicked(evt);
            }
        });

        ai_v_human_but.setText("AI vs Human");
        ai_v_human_but.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent evt) {
                ai_v_human_butMouseClicked(evt);
            }
        });

        human_v_human_but.setText("Human vs Human");
        human_v_human_but.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent evt) {
                human_v_human_butMouseClicked(evt);
            }
        });

        ai_v_ai_but.setText("AI vs AI");
        ai_v_ai_but.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent evt) {
                ai_v_ai_butMouseClicked(evt);
            }
        });

        GroupLayout options_panelLayout = new GroupLayout(options_panel);
        options_panel.setLayout(options_panelLayout);
        options_panelLayout.setHorizontalGroup(
                options_panelLayout.createParallelGroup
        (GroupLayout.Alignment.LEADING)
                .addGroup(options_panelLayout.createSequentialGroup()
                        .addContainerGap(69, Short.MAX_VALUE)
                        .addComponent
        (human_v_ai_but, GroupLayout.PREFERRED_SIZE,
                                140, GroupLayout.PREFERRED_SIZE)
                        .addGap(32, 32, 32)
                        .addComponent
        (ai_v_human_but, GroupLayout.PREFERRED_SIZE,
                                140, GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent
        (human_v_human_but, GroupLayout.PREFERRED_SIZE,
                                140, GroupLayout.PREFERRED_SIZE)
                        .addGap(28, 28, 28)
                        .addComponent(ai_v_ai_but, GroupLayout.PREFERRED_SIZE,
                                140, GroupLayout.PREFERRED_SIZE)
                        .addGap(36, 36, 36))
        );

        options_panelLayout.setVerticalGroup(
                options_panelLayout.createParallelGroup
        (GroupLayout.Alignment.LEADING)
                .addGroup(options_panelLayout.createParallelGroup
        (GroupLayout.Alignment.BASELINE)
                        .addComponent
        (ai_v_human_but, GroupLayout.PREFERRED_SIZE,
                                39, GroupLayout.PREFERRED_SIZE)
                        .addComponent
        (human_v_ai_but, GroupLayout.PREFERRED_SIZE,
                                40, GroupLayout.PREFERRED_SIZE)
                        .addComponent
        (human_v_human_but, GroupLayout.PREFERRED_SIZE,
                                38, GroupLayout.PREFERRED_SIZE)
                        .addComponent(ai_v_ai_but, GroupLayout.PREFERRED_SIZE,
                                36, GroupLayout.PREFERRED_SIZE))
        );

        quit_but.setText("Quit");
        quit_but.setMaximumSize(new java.awt.Dimension(83, 23));
        quit_but.setMinimumSize(new java.awt.Dimension(83, 23));
        quit_but.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent evt) {
                quit_butMouseClicked(evt);
            }
        });

        ai_progress_bar.setFocusable(false);

        ai_lbl.setText("            AI thinking...");

        play_again_but.setText("Play Again");
        play_again_but.setPreferredSize(new java.awt.Dimension(53, 23));
        play_again_but.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent evt) {
                play_again_butMouseClicked(evt);
            }
        });

        GroupLayout ai_thinking_quit_panelLayout = new GroupLayout
        (ai_thinking_quit_panel);
        ai_thinking_quit_panel.setLayout(ai_thinking_quit_panelLayout);
        ai_thinking_quit_panelLayout.setHorizontalGroup
        (ai_thinking_quit_panelLayout.createParallelGroup
        (GroupLayout.Alignment.LEADING)
                .addGroup(ai_thinking_quit_panelLayout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent
        (play_again_but, GroupLayout.PREFERRED_SIZE,
                                100, GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(quit_but, GroupLayout.PREFERRED_SIZE,
                                100, GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addGroup(ai_thinking_quit_panelLayout.
                                createParallelGroup
        (GroupLayout.Alignment.LEADING, false)
                                .addComponent
        (ai_progress_bar, GroupLayout.DEFAULT_SIZE,
                                        178, Short.MAX_VALUE)
                                .addComponent
        (ai_lbl, GroupLayout.DEFAULT_SIZE,
                                     GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addContainerGap(GroupLayout.DEFAULT_SIZE,
                                Short.MAX_VALUE))
        );

        ai_thinking_quit_panelLayout.setVerticalGroup
        (ai_thinking_quit_panelLayout.createParallelGroup
        (GroupLayout.Alignment.LEADING)
                .addGroup(GroupLayout.Alignment.TRAILING,
                        ai_thinking_quit_panelLayout.createSequentialGroup()
                        .addContainerGap()
                        .addGroup
        (ai_thinking_quit_panelLayout.createParallelGroup
        (GroupLayout.Alignment.TRAILING)
                                .addComponent
        (play_again_but, GroupLayout.DEFAULT_SIZE,
                                      GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent
        (quit_but, GroupLayout.Alignment.LEADING,
                             GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE,
                                        Short.MAX_VALUE)
                                .addGroup(GroupLayout.Alignment.LEADING,
                            ai_thinking_quit_panelLayout.createSequentialGroup()
                                        .addGap(0, 0, Short.MAX_VALUE)
                                        .addComponent(ai_lbl)
                                        .addPreferredGap
        (LayoutStyle.ComponentPlacement.UNRELATED)
                                        .addComponent
        (ai_progress_bar, GroupLayout.PREFERRED_SIZE,
                                               19, GroupLayout.PREFERRED_SIZE)))
                        .addContainerGap())
        );

        game_board_panel.setBackground(new java.awt.Color(255, 255, 255));
        game_board_panel.setBorder(BorderFactory.createBevelBorder
        (javax.swing.border.BevelBorder.RAISED));
        game_board_panel.setFocusable(false);
        game_board_panel.setMaximumSize(new java.awt.Dimension(500, 500));
        game_board_panel.setMinimumSize(new java.awt.Dimension(500, 500));
        game_board_panel.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent evt) {
                    game_board_panelMouseClicked(evt);
            }
        });

        GroupLayout game_board_panelLayout = new GroupLayout(game_board_panel);
        game_board_panel.setLayout(game_board_panelLayout);
        game_board_panelLayout.setHorizontalGroup(
                game_board_panelLayout.createParallelGroup
        (GroupLayout.Alignment.LEADING)
                .addGap(0, 520, Short.MAX_VALUE)
        );
        game_board_panelLayout.setVerticalGroup(
                game_board_panelLayout.createParallelGroup
        (GroupLayout.Alignment.LEADING)
                .addGap(0, 520, Short.MAX_VALUE)
        );

        GroupLayout layout = new GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                .addComponent(options_panel, GroupLayout.DEFAULT_SIZE,
                        GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(ai_thinking_quit_panel, GroupLayout.DEFAULT_SIZE,
                        GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGroup(GroupLayout.Alignment.TRAILING,
                        layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent
        (game_board_panel, GroupLayout.PREFERRED_SIZE,
                           GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent
        (game_state_panel, GroupLayout.PREFERRED_SIZE,
                          GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE))
        );

        layout.setVerticalGroup(layout.createParallelGroup
        (GroupLayout.Alignment.LEADING)
                .addGroup(layout.createSequentialGroup()
                        .addComponent(ai_thinking_quit_panel,
                           GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE,
                                GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup
        (GroupLayout.Alignment.LEADING, false)
                                .addComponent
        (game_board_panel, GroupLayout.DEFAULT_SIZE,
                                      GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent
        (game_state_panel, GroupLayout.DEFAULT_SIZE,
                                     GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addPreferredGap
        (LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(options_panel, GroupLayout.PREFERRED_SIZE,
                           GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                        .addContainerGap
        (GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>                        

    private void quit_butMouseClicked(MouseEvent evt) {
        System.exit(0);
    }

    private void human_v_ai_butMouseClicked(MouseEvent evt) {
        paint_board(game_board_panel.getGraphics());
        game_state_display.setText("");
        set_all_non_focusable();
    }

    private void ai_v_human_butMouseClicked(MouseEvent evt) {
        paint_board(game_board_panel.getGraphics());
        game_state_display.setText("");
        set_all_non_focusable();
    }

    private void human_v_human_butMouseClicked(MouseEvent evt) {
        paint_board(game_board_panel.getGraphics());
        game_state_display.setText("");
        set_all_non_focusable();
    }

    private void ai_v_ai_butMouseClicked(MouseEvent evt) {
        paint_board(game_board_panel.getGraphics());
        game_state_display.setText("");
        set_all_non_focusable();
    }

    private void play_again_butMouseClicked(MouseEvent evt) {
        for (int i = 0; i < legal_moves.length; i++){
            legal_moves[i][2] = 0;
        }
        Graphics g = game_board_panel.getGraphics();
        game_board_panel.paint(g);
        g.setColor(Color.LIGHT_GRAY);
        game_board_panel.repaint();
        set_all_focusable();
        
    }

    private void game_board_panelMouseClicked(MouseEvent evt){
        Point a             = game_board_panel.getMousePosition();
        int x               = (int) a.getX();
        int y               = (int) a.getY();
        JavaPasser.pass(x, y, player);
        boolean successful  = false;
        String curr         = game_state_display.getText();
        int right_x, bottom_y, left_x, top_y;
        
        game_state_display.setText(curr + "x,y coordinate: " + x + ", " + y + "\n");
        
        /* Logic for checking if a move is legal */
        for (int i = 0; i < legal_moves.length; i++) {

            Graphics g = game_board_panel.getGraphics();
            int check_x = legal_moves[i][0];
            int check_y = legal_moves[i][1];
            int check_moved = legal_moves[i][2];

            left_x = x - 10;
            right_x = x + 10;
            top_y = y - 11;
            bottom_y = y + 11;

            if ((left_x <= check_x && check_x <= right_x)
                    && (top_y <= check_y && check_y <= bottom_y)
                    && check_moved == 0) {
                if (player == 'X') {
                    curr = game_state_display.getText();
                    game_state_display.setText(curr + "Player X moved\n");
                    g.drawImage(playerX_img, check_x - 10, check_y - 11, this);
                    successful = true;
                }else {
                    curr = game_state_display.getText();
                    game_state_display.setText(curr + "Player Y moved\n");
                    g.drawImage(playerO_img, check_x - 10, check_y - 11, this);
                    successful = true;
                }
                legal_moves[i][2] = 1;
            }
        } /* END OF IF LEGAL LOOP */
        if (successful == false) {
            curr = game_state_display.getText();
            game_state_display.setText(curr + "Not a Legal Move\n");
        }
        else if (player == 'X') {
            player = 'O';
        }
        else{
            player = 'X';
        }
        
        /* Case Nobody wins */
        int tie = 0;
        for (int i = 0; i < legal_moves.length; i++){
            if (legal_moves[i][2] == 1){
                tie++;
                if (tie == 48){
                    Graphics g = game_board_panel.getGraphics();
                    g.drawImage(game_over_img, 10, 60, this);
                    /* Activate play again button*/
                    play_again_but.setEnabled(true);  
                    /* And turn on the mouse listeners so user can click it */
                    for(int j = 0; j < m5.length; j++){
                        play_again_but.addMouseListener(m5[j]);
                    }
                }
            }
        }
    }
    
   

    protected static void paint_board(Graphics g) {
        game_board_panel.paint(g);
        g.setColor(Color.BLUE);

        /* Outter Ring */
        g.drawOval(25, 25, 450, 450);

        /* Second Ring */
        g.drawOval(75, 75, 350, 350);

        /* Third Ring*/
        g.drawOval(125, 125, 250, 250);

        /* Inner most Ring */
        g.drawOval(175, 175, 150, 150);

        /* Quadrant 1 */
        g.drawLine(284, 183, 355, 50);
        g.drawLine(316, 215, 449, 146);

        /* Quadrant 2 */
        g.drawLine(216, 184, 147, 51);
        g.drawLine(184, 216, 51, 146);

        /* Quadrant 3 */
        g.drawLine(184, 284, 51, 354);
        g.drawLine(215, 316, 146, 449);

        /* Quadrant 4 */
        g.drawLine(284, 316, 354, 449);
        g.drawLine(317, 284, 450, 354);

        /* The verticle */
        g.drawLine(250, 25, 250, 175);
        g.drawLine(250, 325, 250, 475);

        /* The horizontal */
        g.drawLine(325, 250, 475, 250);
        g.drawLine(175, 250, 25, 250);
    }

    protected static void set_all_non_focusable() {
        /* set buttons to appear inactive */
        ai_v_ai_but.setEnabled(false);
        human_v_human_but.setEnabled(false);
        ai_v_human_but.setEnabled(false);
        human_v_ai_but.setEnabled(false);
        play_again_but.setEnabled(false);
        
        /* turn off all the mouselisteners for these buttons */
        for(int i = 0; i < m1.length; i++){
            ai_v_ai_but.removeMouseListener(m1[i]);
        }
        
        for(int i = 0; i < m2.length; i++){
            human_v_human_but.removeMouseListener(m2[i]);
        }
        
        for(int i = 0; i < m3.length; i++){
            ai_v_human_but.removeMouseListener(m3[i]);
        }
       
        for(int i = 0; i < m4.length; i++){
            human_v_ai_but.removeMouseListener(m4[i]);
        }
        
        for(int i = 0; i < m5.length; i++){
            play_again_but.removeMouseListener(m5[i]);
        }
    }
    protected static void set_all_focusable() {
        ai_v_ai_but.setEnabled(true);
        human_v_human_but.setEnabled(true);
        ai_v_human_but.setEnabled(true);
        human_v_ai_but.setEnabled(true);
       
        /* Turn the mouse listeners back on */
        for(int i = 0; i < m1.length; i++) {   
            ai_v_ai_but.addMouseListener(m1[i]);
        }
        
        for(int i = 0; i < m2.length; i++){
            human_v_human_but.addMouseListener(m2[i]);
        }
        
        for(int i = 0; i < m3.length; i++){
            ai_v_human_but.addMouseListener(m3[i]);
        }
        
        for(int i = 0; i < m4.length; i++){
            human_v_ai_but.addMouseListener(m4[i]);
        }
    }

    public static void main(String args[]) {
        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {

                try {
                    new Main().setVisible(true);
                /* store mouselisteners in predefined arrays see variable section */
                m1 = ai_v_ai_but.getMouseListeners();
                m2 = human_v_human_but.getMouseListeners();
                m3 = ai_v_human_but.getMouseListeners();
                m4 = human_v_ai_but.getMouseListeners();
                m5 = play_again_but.getMouseListeners();
                } catch (IOException ex) {
                    Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
    }
}
