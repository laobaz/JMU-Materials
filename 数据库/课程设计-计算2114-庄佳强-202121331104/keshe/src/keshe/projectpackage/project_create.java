package keshe.projectpackage;

import keshe.template.Default_template;
import keshe.windowUI;

import javax.swing.*;

public class project_create extends JFrame {
    JButton button1, button2, button3, button4, button5,button6,button7;

    public project_create() {
        Default_template defaultTemplate = new Default_template(this);
        setTitle("欢迎来到project_create表管理部分");
        init();
    }

    void init() {

        button2 = new JButton("进行更新操作");
        button3 = new JButton("进行删除操作");
        button4 = new JButton("查看当前表格信息");
        button5 = new JButton("返回上一级");
        add(button2);
        add(button3);
        add(button4);
        add(button5);
        validate();
        button2.addActionListener(e -> {
            new project_create_update().setVisible(true);
            dispose();
        });
        button3.addActionListener(e -> {
            new project_create_delete().setVisible(true);
            dispose();
        });
        button4.addActionListener(e -> {
            new project_create_select().setVisible(true);
            dispose();
        });
        button5.addActionListener(e -> {
            new project().setVisible(true);//返回上一个界面
            dispose();
        });


    }

}
