package keshe.leaderpackage;


import keshe.template.Default_template;
import keshe.windowUI;

import javax.swing.*;

public class leader extends JFrame {
    JButton button1, button2, button3, button4, button5;

    public leader() {
        Default_template defaultTemplate = new Default_template(this);
        setTitle("��ӭ����leader�������");
        init();
    }

    void init() {
        button1 = new JButton("������Ӳ���");
        button2 = new JButton("���и��²���");
        button3 = new JButton("����ɾ������");
        button4 = new JButton("�鿴��ǰ�����Ϣ");
        button5 = new JButton("������һ��");
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
            new windowUI().setVisible(true);//������һ������
            dispose();
        });


    }
}
