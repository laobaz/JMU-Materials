package keshe;

import javax.swing.*;
import java.awt.*;

public class search_type extends JFrame {//类型查找
     JTextField jTextField = new JTextField(10);
     JButton jButton_back,jButton_search;

    search_type() {
        setTitle("按类别查找");
        init();
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private void init() {
        this.setResizable(false);
        this.setSize(455,150);
        //界面显示居中
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        this.show();
        validate();
        jButton_search = new JButton("查找");
        jButton_back = new JButton("返回上一级");
        JPanel pnorth = new JPanel();
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("类别名称："));
        pnorth.add(jTextField);
        pnorth.add(jButton_search);
        pnorth.add(jButton_back);
        add(pnorth, BorderLayout.CENTER);
        jButton_search.addActionListener(e -> {
            try {
                String type=jTextField.getText();
                new type_table(type);
                dispose();
            } catch (Exception ex) {
            }


        });
        jButton_back.addActionListener(e -> {
            new Search();
            dispose();
        });
    }
}

