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
    Connection connection = c.getConnect();        //���������ݿ�
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
        jButton_Certain = new JButton("ȷ�����");
        jButton_Back = new JButton("������һ��");
        JPanel pnorth = new JPanel();       //����JPanel��Ÿ�����ť��JLabel
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("ѧԺ���ƣ�"));
        pnorth.add(jf1);
        pnorth.add(new JLabel("��ַ��"));
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
                String jfa1 = jf1.getText();//��ȡ����ĸ�������
                String jfa2 = jf2.getText();

                if (jfa1.equals("") || jfa2.equals("")){ //��һ������Ϊ������������������ȫ

                    JOptionPane.showMessageDialog(null,
                            "��������������Ϣ��", "����", JOptionPane.WARNING_MESSAGE);
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
                            "��ѧԺ�Ѿ�����", "", JOptionPane.WARNING_MESSAGE);
                    jf1.setText(null);//����ı���
                    jf2.setText(null);

                } else {
                    sql1="{call college_insert(?,?)}";
                    CallableStatement stmt=connection.prepareCall(sql1);
                    stmt.setString(1,jfa1);
                    stmt.setString(2,jfa2);
                    flag= stmt.execute();
                    if (flag==false) {
                        JOptionPane.showMessageDialog(null, "��ӳɹ�");
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
            new college().setVisible(true);//������һ������
            try {
                connection.close();

            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
            dispose();
        });

    }
}
