package keshe.projectpackage;

import keshe.leaderpackage.leader;
import keshe.template.Default_template;
import keshe.template.Output_list;
import keshe.template.connection;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import java.awt.*;
import java.sql.*;

public class update extends JFrame {
    keshe.template.connection c = new connection();
    Connection connection = c.getConnect();        //���������ݿ�
    JTextField jf1 = new JTextField(10);
    JTextField jf2 = new JTextField(10);
    JTextField jf3 = new JTextField(10);
    JTable jTable=null;

    JButton jButton_Certain, jButton_Back;

    update() {
        new Default_template(this);
        setSize(1000,400);
        init();
    }

    private void init() {

        jButton_Certain = new JButton("ȷ������");
        jButton_Back = new JButton("������һ��");
        JPanel pnorth = new JPanel();       //����JPanel��Ÿ�����ť��JLabel

        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("Ҫ���µ�������"));
        pnorth.add(jf1);
        pnorth.add(new JLabel("Ҫ���µ�id��"));
        pnorth.add(jf2);
        pnorth.add(new JLabel("����ֵΪ��"));
        pnorth.add(jf3);
        pnorth.add(jButton_Certain);
        pnorth.add(jButton_Back);
        add(pnorth, BorderLayout.NORTH);


        String sql="{call project_select()}";
        Output_list outputList=new Output_list();
        jTable=outputList.Output(sql);
        jTable.setPreferredScrollableViewportSize(new Dimension(700, 300));
        add(new JScrollPane(jTable), BorderLayout.SOUTH);

        jButton_Certain.addActionListener(e -> {
            ResultSet rs;
            try {
                String jfa1 = jf1.getText();//��ȡ����ĸ�������
                String jfa2 = jf2.getText();
                String jfa3 = jf3.getText();

                if (jfa1.equals("") || jfa2.equals("")||jfa3.equals("")){ //��һ������Ϊ������������������ȫ

                    JOptionPane.showMessageDialog(null,
                            "��������������Ϣ��", "����", JOptionPane.WARNING_MESSAGE);
                    return;
                }
                boolean flag = false;
                String sql1 = "select project_id from course_design.project";
                Statement statement = connection.createStatement();
                rs = statement.executeQuery(sql1);
                while (rs.next())
                {
                    String Mark = rs.getString(1);
                    if (jfa2.equals(Mark)) {
                        flag = true;
                    }
                }
                if (!flag) {
                    JOptionPane.showMessageDialog(null,
                            "����Ŀ������", "", JOptionPane.WARNING_MESSAGE);
                    jf1.setText(null);//����ı���
                    jf2.setText(null);
                    jf3.setText(null);

                } else {
                    sql1="{call project_update(?,?,?)}";
                    CallableStatement stmt=connection.prepareCall(sql1);
                    stmt.setString(1,jfa1);
                    stmt.setString(2,jfa2);
                    stmt.setString(3,jfa3);
                    flag= stmt.execute();
                    if (flag==false) {
                        JOptionPane.showMessageDialog(null, "���³ɹ�");
                        jf1.setText(null);
                        jf2.setText(null);
                    }
                }
            } catch (Exception ex) {
                System.out.println(ex);
                JOptionPane.showMessageDialog(null, "������ִ���,�����Ƿ�������ȷ");
            }

            //���¶�ȡһ�����ݿ������ʵ��ʵʱˢ��
            outputList.Output(sql);
            TableModel tableModel=new DefaultTableModel(outputList.table,outputList.arr);//ʵ��ʵʱˢ��
            jTable.setModel(tableModel);

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
