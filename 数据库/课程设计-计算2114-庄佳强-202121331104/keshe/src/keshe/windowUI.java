package keshe;

import keshe.Backup_and_restorepackage.Backup_and_restore;
import keshe.collegepackage.college;
import keshe.template.Default_template;
import keshe.leaderpackage.leader;
import keshe.logspackage.Logs;
import keshe.projectpackage.project;


import javax.swing.*;


public class windowUI extends JFrame {//������UI
    JButton  button1,button2,button3,button4,button5,button6,button7;
    public windowUI(){
        Default_template defaultTemplate=new Default_template(this);
        setTitle("��ӭ����������Ŀ����ϵͳ");
        init();

    }
    void init(){
        //������ʾ����
        button1=new JButton("��college����в���");
        button2=new JButton("��leader����в���");
        button3=new JButton("��project����в���");
        button4=new JButton("�鿴��ǰ��־��Ϣ");
        button7=new JButton("�����ݿ���б��ݻ��߻�ԭ");
        button5=new JButton("�˳���¼");
        button6=new JButton("�˳�ϵͳ");
        add(button1);
        add(button2);
        add(button3);
        add(button4);
        add(button7);
        add(button5);
        add(button6);
        validate();
        button1.addActionListener(e -> {
                new college().setVisible(true);
                dispose();
        });
        button2.addActionListener(e -> {
                new leader().setVisible(true);
                dispose();
        });
        button3.addActionListener(e -> {
                new project().setVisible(true);
                dispose();
        });
        button4.addActionListener(e -> {
                new Logs().setVisible(true);

        });
        button5.addActionListener(e -> {
               new Start().setVisible(true);
                dispose();
        });
        button6.addActionListener(e -> System.exit(0));
        button7.addActionListener(e -> {
            new Backup_and_restore().setVisible(true);
            dispose();
        });


    }
}
