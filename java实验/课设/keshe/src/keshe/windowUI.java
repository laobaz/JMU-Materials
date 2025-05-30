package keshe;

import javax.swing.*;
import java.awt.*;

/*
1.查询所有账单 2.增加账单 3.删除账单 4.修改账单--修改什么参数，5.查询功能-->按类别查询/按购买查询/按标号查找
 */
public class windowUI extends JFrame {//主界面UI
    JButton  button1,button2,button3,button4,button5,button6;

    public windowUI(){
        setTitle("欢迎来到个人支出管理系统");
        setBounds(100,100,200,400);
        init();
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    void init(){
        this.setResizable(false);
        this.setSize(600,100);
        //界面显示居中
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,(screen.height-this.getSize().height)/2);
        validate();
        setLayout(new FlowLayout());
        button1=new JButton("添加账单");//按账单标号搜索
        button2=new JButton("删除账单");//按账单名称搜索
        button3=new JButton("查看账单信息");//按授课教师搜索
        button4=new JButton("修改账单信息");//按授课教师搜索
        button5=new JButton("退出登录");//按授课教师搜索
        button6=new JButton("退出系统");//按授课教师搜索
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
