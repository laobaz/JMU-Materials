package keshe.leaderpackage;


import keshe.template.Default_template;
import keshe.windowUI;

import javax.swing.*;

public class leader extends JFrame {
    JButton button1, button2, button3, button4, button5;

    public leader() {
        Default_template defaultTemplate = new Default_template(this);
        setTitle("欢迎来到leader表管理部分");
        init();
    }

    void init() {
        button1 = new JButton("进行添加操作");
        button2 = new JButton("进行更新操作");
        button3 = new JButton("进行删除操作");
        button4 = new JButton("查看当前表格信息");
        button5 = new JButton("返回上一级");
        add(button1);
        add(button2);
        add(button3);
        add(button4);
        add(button5);
        validate();
        button1.addActionListener(e -> {
            new add().setVisible(true);
            dispose();
        });
        button2.addActionListener(e -> {
            new update().setVisible(true);
            dispose();
        });
        button3.addActionListener(e -> {
            new delete().setVisible(true);
            dispose();
        });
        button4.addActionListener(e -> {
            new select().setVisible(true);
            dispose();
        });


        button5.addActionListener(e -> {
            new windowUI().setVisible(true);//返回上一个界面
            dispose();
        });


    }
}
