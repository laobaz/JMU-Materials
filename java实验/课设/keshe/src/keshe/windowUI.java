package keshe;

import javax.swing.*;
import java.awt.*;

/*
1.��ѯ�����˵� 2.�����˵� 3.ɾ���˵� 4.�޸��˵�--�޸�ʲô������5.��ѯ����-->������ѯ/�������ѯ/����Ų���
 */
public class windowUI extends JFrame {//������UI
    JButton  button1,button2,button3,button4,button5,button6;

    public windowUI(){
        setTitle("��ӭ��������֧������ϵͳ");
        setBounds(100,100,200,400);
        init();
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    void init(){
        this.setResizable(false);
        this.setSize(600,100);
        //������ʾ����
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,(screen.height-this.getSize().height)/2);
        validate();
        setLayout(new FlowLayout());
        button1=new JButton("����˵�");//���˵��������
        button2=new JButton("ɾ���˵�");//���˵���������
        button3=new JButton("�鿴�˵���Ϣ");//���ڿν�ʦ����
        button4=new JButton("�޸��˵���Ϣ");//���ڿν�ʦ����
        button5=new JButton("�˳���¼");//���ڿν�ʦ����
        button6=new JButton("�˳�ϵͳ");//���ڿν�ʦ����
        add(button1);
        add(button2);
        add(button3);
        add(button4);
        add(button5);
        add(button6);
        validate();
        button1.addActionListener(e -> {
                new Add().setVisible(true);
                dispose();
        });
        button2.addActionListener(e -> {
                new Delete().setVisible(true);
                dispose();
        });
        button3.addActionListener(e -> {
                new Search().setVisible(true);
                dispose();
        });
        button4.addActionListener(e -> {
                new Revise().setVisible(true);
                dispose();
        });
        button5.addActionListener(e -> {
               new Start().setVisible(true);
                dispose();
        });
        button6.addActionListener(e -> System.exit(0));


    }
}
