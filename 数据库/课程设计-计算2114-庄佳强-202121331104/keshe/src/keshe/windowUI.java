package keshe;

import keshe.Backup_and_restorepackage.Backup_and_restore;
import keshe.collegepackage.college;
import keshe.template.Default_template;
import keshe.leaderpackage.leader;
import keshe.logspackage.Logs;
import keshe.projectpackage.project;


import javax.swing.*;


public class windowUI extends JFrame {//主界面UI
    JButton  button1,button2,button3,button4,button5,button6,button7;
    public windowUI(){
        Default_template defaultTemplate=new Default_template(this);
        setTitle("欢迎来到科研项目管理系统");
        init();

    }
    void init(){
        //界面显示居中
        button1=new JButton("对college表进行操作");
        button2=new JButton("对leader表进行操作");
        button3=new JButton("对project表进行操作");
        button4=new JButton("查看当前日志信息");
        button7=new JButton("对数据库进行备份或者还原");
        button5=new JButton("退出登录");
        button6=new JButton("退出系统");
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
