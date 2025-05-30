package keshe.projectpackage;

import keshe.template.Default_template;
import keshe.template.Output_list;
import keshe.template.connection;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import java.awt.*;
import java.sql.*;

public class obscure extends JFrame{
    keshe.template.connection c = new connection();
    Connection connection = c.getConnect();        //连接上数据库
    JTextField jf1 = new JTextField(10);

    JTable jTable=null;

    JButton jButton_Certain, jButton_Back;

    obscure() {
        new Default_template(this);
        setSize(600,400);
        init();
    }

    private void init() {

        jButton_Certain = new JButton("查询");
        jButton_Back = new JButton("返回上一级");
        JPanel pnorth = new JPanel();       //建立JPanel存放个个按钮和JLabel
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("支持项目名称!"));
        pnorth.add(new JLabel("要查询的模糊字眼："));
        pnorth.add(jf1);
        pnorth.add(jButton_Certain);
        pnorth.add(jButton_Back);
        add(pnorth, BorderLayout.NORTH);

        String sql = "{call project_select()}";
        Output_list outputList = new Output_list();
        jTable = outputList.Output(sql);
        jTable.setPreferredScrollableViewportSize(new Dimension(500, 300));
        add(new JScrollPane(jTable), BorderLayout.SOUTH);

        jButton_Certain.addActionListener(e -> {
            ResultSet rs;
            try {
                String jfa1 = jf1.getText();//获取输入的个个内容

                if (jfa1.equals("")) { //有一个内容为不存在提醒他输入完全

                    JOptionPane.showMessageDialog(null,
                            "请输入完整的信息！", "警告", JOptionPane.WARNING_MESSAGE);
                    return;
                }


                String sql1 = "{call project_select_obscure(?)}";
                CallableStatement stmt = connection.prepareCall(sql1);
                stmt.setString(1, jfa1);
                String arr[]=null;
                String table[][]=null;
                boolean hasResult = stmt.execute();
                while (hasResult) {
                    rs = stmt.getResultSet();
                    ResultSetMetaData meta = rs.getMetaData();
                    int columns = meta.getColumnCount();
                    arr = new String[columns];

                    table = new String[100][columns];
                    for (int i = 0; i < columns; i++) {
                        arr[i] = meta.getColumnName(i + 1);
                    }

                    int j = 0;
                    while (rs.next()) {
                        for (int i = 0; i < columns; i++) {
                            table[j][i] = rs.getString(i + 1);
                        }
                        j++;
                    }
                    hasResult = stmt.getMoreResults();
                }
                TableModel tableModel = new DefaultTableModel(table, arr);//实现实时刷新
                jTable.setModel(tableModel);

                if (hasResult) {
                    JOptionPane.showMessageDialog(null, "查询完成");
                    jf1.setText(null);
                }
            } catch (Exception ex) {
                System.out.println(ex);
                JOptionPane.showMessageDialog(null, "输入出现错误,请检查是否输入正确");
            }
            //重新读取一次数据库的内容实现实时刷新
        });
        jButton_Back.addActionListener(e -> {
            new project().setVisible(true);//返回上一个界面
            try {
                connection.close();

            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
            dispose();
        });

    }
}
