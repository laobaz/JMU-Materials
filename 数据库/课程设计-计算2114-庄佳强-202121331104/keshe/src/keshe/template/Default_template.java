package keshe.template;

import javax.swing.*;
import java.awt.*;


public class Default_template {
    //创造一个模板，方便直接套
    public Default_template(JFrame jFrame){
        jFrame.setBounds(100,100,200,400);
        jFrame.setVisible(true);
        jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jFrame.setResizable(false);
        jFrame.setSize(600,200);
        Dimension screen = jFrame.getToolkit().getScreenSize();
        jFrame.setLocation((screen.width-jFrame.getSize().width)/2,(screen.height-jFrame.getSize().height)/2);
        jFrame.validate();
        jFrame.setLayout(new FlowLayout());
    }
}
