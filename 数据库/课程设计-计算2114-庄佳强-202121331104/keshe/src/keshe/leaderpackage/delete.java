package keshe.leaderpackage;

import keshe.collegepackage.college;
import keshe.template.Default_template;
import keshe.template.Output_list;
import keshe.template.connection;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import java.awt.*;
import java.sql.*;

public class delete extends JFrame {
    keshe.template.connection c = new connection();
    Connection connection = c.getConnect();        //���������ݿ�
    JTextField jf1 = new JTextField(10);

    JTable jTable = null;

    JButton jButton_Certain, jButton_Back;

    delete() {
        new Default_template(this);
        setSize(600, 400);
        init();
    }

    private void init() {

        jButton_Certain = new JButton("ȷ��ɾ��");
        jButton_Back = new JButton("������һ��");
        JPanel pnorth = new JPanel();       //����JPanel��Ÿ�����ť��JLabel
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("ɾ����id��"));
        pnorth.add(jf1);
        pnorth.add(jButton_Certain);
        pnorth.add(jButton_Back);
        add(pnorth, BorderLayout.NORTH);


        String sql = "{call leader_select()}";
        Output_list outputList = new Output_list();
        jTable = outputList.Output(sql);
        jTable.setPreferredScrollableViewportSize(new Dimension(500, 200));
        add(new JScrollPane(jTable), BorderLayout.SOUTH);

        jButton_Certain.addActionListener(e -> {
            PreparedStatement ps;
            ResultSet rs;
            try {
                String jfa1 = jf1.getText();//��ȡ����ĸ�������


                if (jfa1.equals("")) { //��һ������Ϊ������������������ȫ

                    JOptionPane.showMessageDialog(null,
                            "��������������Ϣ��", "����", JOptionPane.WARNING_MESSAGE);
                    return;
                }
                boolean flag = false;
                String sql1 = "select leader_id from course_design.leader";
                Statement statement = connection.createStatement();
                rs = statement.executeQuery(sql1);
                while (rs.next()) {
                    String Mark = rs.getString(1);
                    if (jfa1.equals(Mark)) {
                        flag = true;
                    }
                }
                if (!flag) {
                    JOptionPane.showMessageDialog(null,
                            "���˲�����", "", JOptionPane.WARNING_MESSAGE);
                    jf1.setText(null);//����ı���

                } else {
                    sql1 = "{call leader_delete(?)}";
                    CallableStatement stmt = connection.prepareCall(sql1);
                    stmt.setString(1, jfa1);
                    flag = stmt.execute();
                    if (!flag) {
                        JOptionPane.showMessageDialog(null, "ɾ���ɹ�");
                        jf1.setText(null);
                    }
                }
            } catch (Exception ex) {
                System.out.println(ex);
                JOptionPane.showMessageDialog(null, "������ִ���,�����Ƿ�������ȷ");
            }

            //���¶�ȡһ�����ݿ������ʵ��ʵʱˢ��
            outputList.Output(sql);
            TableModel tableModel = new DefaultTableModel(outputList.table, outputList.arr);//ʵ��ʵʱˢ��
            jTable.setModel(tableModel);

        });
        jButton_Back.addActionListener(e -> {
            new leader().setVisible(true);//������һ������
            try {
                connection.close();

            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
            dispose();
        });

    }
}
