package keshe;

import javax.swing.*;
import java.awt.*;

public class Search extends JFrame{//查找界面
    JButton jb1,jb2,jb3,jb4,jb5,jb6;
    Search(){
        setTitle("查找账单信息");
        init();
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    private void init(){
        this.setResizable(false);
        this.setSize(455,150);
        //界面显示居中
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        validate();
        jb1=new JButton("返回上一级");
        jb2=new JButton("查看全部账单信息");
        jb3=new JButton("按记录号查找");
        jb4=new JButton("按支出项目查找");
        jb5=new JButton("按类别查找");
        jb6=new JButton("模糊查找");
        JPanel pnorth=new JPanel();
        pnorth.setLayout(new FlowLayout());
        pnorth.add(jb1);
        pnorth.add(jb2);
        pnorth.add(jb3);
        pnorth.add(jb4);
        pnorth.add(jb5);
        pnorth.add(jb6);
        add(pnorth, BorderLayout.CENTER);
        //按钮一一对应跳转
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

