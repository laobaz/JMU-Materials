package keshe.projectpackage;

import keshe.template.Default_template;
import keshe.template.Output_list;
import keshe.template.connection;

import javax.swing.*;
import java.awt.*;
import java.sql.Connection;
import java.sql.SQLException;

public class project_create_select extends JFrame {
    keshe.template.connection c = new connection();
    Connection connection = c.getConnect();        //连接上数据库

    JTable jTable=null;

    JButton jButton_Certain, jButton_Back;

    project_create_select() {
        new Default_template(this);
        setSize(600,400);
        init();
    }

    private void init() {

        jButton_Back = new JButton("返回上一级");
        JPanel pnorth = new JPanel();       //建立JPanel存放个个按钮和JLabel
        pnorth.setLayout(new FlowLayout());

        pnorth.add(jButton_Back);
        add(pnorth, BorderLayout.NORTH);


        String sql="{call project_create_select()}";
        Output_list outputList=new Output_list();
        jTable=outputList.Output(sql);
        jTable.setPreferredScrollableViewportSize(new Dimension(500, 200));
        add(new JScrollPane(jTable), BorderLayout.SOUTH);


        jButton_Back.addActionListener(e -> {
            new project_create().setVisible(true);//返回上一个界面
            try {
                connection.close();

            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
            dispose();
        });

    }
}
