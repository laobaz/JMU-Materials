package keshe.projectpackage;

import keshe.template.Default_template;
import keshe.windowUI;

import javax.swing.*;

public class project_create extends JFrame {
    JButton button1, button2, button3, button4, button5,button6,button7;

    public project_create() {
        Default_template defaultTemplate = new Default_template(this);
        setTitle("��ӭ����project_create�������");
        init();
    }

    void init() {

        button2 = new JButton("���и��²���");
        button3 = new JButton("����ɾ������");
        button4 = new JButton("�鿴��ǰ�����Ϣ");
        button5 = new JButton("������һ��");
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
            new project().setVisible(true);//������һ������
            dispose();
        });


    }

}
