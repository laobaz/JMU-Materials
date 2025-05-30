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
    Connection connection = c.getConnect();        //���������ݿ�
    JTextField jf1 = new JTextField(10);

    JTable jTable=null;

    JButton jButton_Certain, jButton_Back;

    obscure() {
        new Default_template(this);
        setSize(600,400);
        init();
    }

    private void init() {

        jButton_Certain = new JButton("��ѯ");
        jButton_Back = new JButton("������һ��");
        JPanel pnorth = new JPanel();       //����JPanel��Ÿ�����ť��JLabel
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("֧����Ŀ����!"));
        pnorth.add(new JLabel("Ҫ��ѯ��ģ�����ۣ�"));
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
                String jfa1 = jf1.getText();//��ȡ����ĸ�������

                if (jfa1.equals("")) { //��һ������Ϊ������������������ȫ

                    JOptionPane.showMessageDialog(null,
                            "��������������Ϣ��", "����", JOptionPane.WARNING_MESSAGE);
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
                TableModel tableModel = new DefaultTableModel(table, arr);//ʵ��ʵʱˢ��
                jTable.setModel(tableModel);

                if (hasResult) {
                    JOptionPane.showMessageDialog(null, "��ѯ���");
                    jf1.setText(null);
                }
            } catch (Exception ex) {
                System.out.println(ex);
                JOptionPane.showMessageDialog(null, "������ִ���,�����Ƿ�������ȷ");
            }
            //���¶�ȡһ�����ݿ������ʵ��ʵʱˢ��
        });
        jButton_Back.addActionListener(e -> {
            new project().setVisible(true);//������һ������
            try {
                connection.close();

            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
            dispose();
        });

    }
}
