package keshe.projectpackage;


import keshe.template.Default_template;
import keshe.windowUI;

import javax.swing.*;

public class project extends JFrame {
    JButton button1, button2, button3, button4, button5,button6,button7;

    public project() {
        Default_template defaultTemplate = new Default_template(this);
        setTitle("��ӭ����project�������");
        init();
    }

    void init() {
        button1 = new JButton("������Ӳ���");
        button2 = new JButton("���и��²���");
        button3 = new JButton("����ɾ������");
        button4 = new JButton("�鿴��ǰ�����Ϣ");
        button5 = new JButton("������һ��");
        button7 = new JButton("ģ����ѯ");
        add(button1);
        add(button2);
        add(button3);
        add(button4);
        add(button7);
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

        button7.addActionListener(e -> {
            new obscure().setVisible(true);
            dispose();
        });

    }
}
