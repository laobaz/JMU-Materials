package keshe;

import javax.swing.*;
import java.awt.*;

public class Search extends JFrame{//���ҽ���
    JButton jb1,jb2,jb3,jb4,jb5,jb6;
    Search(){
        setTitle("�����˵���Ϣ");
        init();
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    private void init(){
        this.setResizable(false);
        this.setSize(455,150);
        //������ʾ����
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        validate();
        jb1=new JButton("������һ��");
        jb2=new JButton("�鿴ȫ���˵���Ϣ");
        jb3=new JButton("����¼�Ų���");
        jb4=new JButton("��֧����Ŀ����");
        jb5=new JButton("��������");
        jb6=new JButton("ģ������");
        JPanel pnorth=new JPanel();
        pnorth.setLayout(new FlowLayout());
        pnorth.add(jb1);
        pnorth.add(jb2);
        pnorth.add(jb3);
        pnorth.add(jb4);
        pnorth.add(jb5);
        pnorth.add(jb6);
        add(pnorth, BorderLayout.CENTER);
        //��ťһһ��Ӧ��ת
        jb1.addActionListener(e -> {
            new windowUI().setVisible(true);
            dispose();

        });
        jb2.addActionListener(e -> {
            new All_Table();
            dispose();
        });
        jb3.addActionListener(e -> {
            new search_Mark();
            dispose();
        });
        jb4.addActionListener(e -> {
            new search_expend();
            dispose();
        });
        jb5.addActionListener(e -> {
            new search_type();
            dispose();
        });
        jb6.addActionListener(e -> {
            new Obscure();
            dispose();
        });
    }
}

