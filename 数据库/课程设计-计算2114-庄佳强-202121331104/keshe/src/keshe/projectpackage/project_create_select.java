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
    Connection connection = c.getConnect();        //���������ݿ�

    JTable jTable=null;

    JButton jButton_Certain, jButton_Back;

    project_create_select() {
        new Default_template(this);
        setSize(600,400);
        init();
    }

    private void init() {

        jButton_Back = new JButton("������һ��");
        JPanel pnorth = new JPanel();       //����JPanel��Ÿ�����ť��JLabel
        pnorth.setLayout(new FlowLayout());

        pnorth.add(jButton_Back);
        add(pnorth, BorderLayout.NORTH);


        String sql="{call project_create_select()}";
        Output_list outputList=new Output_list();
        jTable=outputList.Output(sql);
        jTable.setPreferredScrollableViewportSize(new Dimension(500, 200));
        add(new JScrollPane(jTable), BorderLayout.SOUTH);


        jButton_Back.addActionListener(e -> {
            new project_create().setVisible(true);//������һ������
            try {
                connection.close();

            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
            dispose();
        });

    }
}
