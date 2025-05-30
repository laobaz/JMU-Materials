package keshe.collegepackage;

import keshe.template.Default_template;
import keshe.template.Output_list;
import keshe.template.connection;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import javax.swing.*;
import java.awt.*;
import java.sql.*;

public class add extends JFrame{
    keshe.template.connection c = new connection();
    Connection connection = c.getConnect();        //连接上数据库
    JTextField jf1 = new JTextField(10);
    JTextField jf2 = new JTextField(10);
    JTable jTable=null;

    JButton jButton_Certain, jButton_Back;

    add() {
        new Default_template(this);
        setSize(600,400);
        init();
    }

    private void init() {
        System.out.println(keshe.template.connection.user);
        jButton_Certain = new JButton("确定添加");
        jButton_Back = new JButton("返回上一级");
        JPanel pnorth = new JPanel();       //建立JPanel存放个个按钮和JLabel
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("学院名称："));
        pnorth.add(jf1);
        pnorth.add(new JLabel("地址："));
        pnorth.add(jf2);
        pnorth.add(jButton_Certain);
        pnorth.add(jButton_Back);
        add(pnorth, BorderLayout.NORTH);


        String sql="{call college_select()}";
        Output_list outputList=new Output_list();
        jTable=outputList.Output(sql);
        jTable.setPreferredScrollableViewportSize(new Dimension(500, 200));
        add(new JScrollPane(jTable), BorderLayout.SOUTH);

        jButton_Certain.addActionListener(e -> {
            PreparedStatement ps;
            ResultSet rs;
            try {
                String jfa1 = jf1.getText();//获取输入的个个内容
                String jfa2 = jf2.getText();

                if (jfa1.equals("") || jfa2.equals("")){ //有一个内容为不存在提醒他输入完全

                    JOptionPane.showMessageDialog(null,
                            "请输入完整的信息！", "警告", JOptionPane.WARNING_MESSAGE);
                    return;
                }
                boolean flag = false;
                String sql1 = "select college_name from course_design.college";
                Statement statement = connection.createStatement();
                rs = statement.executeQuery(sql1);
                while (rs.next())
                {
                    String Mark = rs.getString(1);
                    if (jfa1.equals(Mark)) {
                        flag = true;
                    }
                }
                if (flag) {
                    JOptionPane.showMessageDialog(null,
                            "该学院已经存在", "", JOptionPane.WARNING_MESSAGE);
                    jf1.setText(null);//清空文本框
                    jf2.setText(null);

                } else {
                    sql1="{call college_insert(?,?)}";
                    CallableStatement stmt=connection.prepareCall(sql1);
                    stmt.setString(1,jfa1);
                    stmt.setString(2,jfa2);
                    flag= stmt.execute();
                    if (flag==false) {
                        JOptionPane.showMessageDialog(null, "添加成功");
                        jf1.setText(null);
                        jf2.setText(null);
                    }
                }
            } catch (Exception ex) {
                System.out.println(ex);
                JOptionPane.showMessageDialog(null, "输入出现错误,请检查是否输入正确");
            }

            //重新读取一次数据库的内容实现实时刷新
            outputList.Output(sql);
            TableModel tableModel=new DefaultTableModel(outputList.table,outputList.arr);//实现实时刷新
            jTable.setModel(tableModel);

        });
        jButton_Back.addActionListener(e -> {
            new college().setVisible(true);//返回上一个界面
            try {
                connection.close();

            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
            dispose();
        });

    }
}
