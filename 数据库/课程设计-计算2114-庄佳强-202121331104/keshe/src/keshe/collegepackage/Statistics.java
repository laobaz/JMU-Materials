package keshe.collegepackage;

import keshe.template.Default_template;
import keshe.template.Output_list;
import keshe.template.connection;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import javax.swing.*;
import java.awt.*;
import java.sql.*;
public class Statistics extends JFrame {

    keshe.template.connection c = new connection();
    Connection connection = c.getConnect();        //���������ݿ�
    JTextField jf1 = new JTextField(10);

    JTable jTable=null;

    JButton jButton_Certain, jButton_Back;

    Statistics() {
        new Default_template(this);
        setSize(600,400);
        init();
    }

    private void init() {

        jButton_Certain = new JButton("ȷ����ѯ");
        jButton_Back = new JButton("������һ��");
        JPanel pnorth = new JPanel();       //����JPanel��Ÿ�����ť��JLabel
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("Ҫ��ѯ������"));
        pnorth.add(jf1);

        pnorth.add(jButton_Certain);
        pnorth.add(jButton_Back);
        add(pnorth, BorderLayout.NORTH);


        String sql = "{call college_select()}";
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

                String sql1 = "{call college_Statistics(?)}";
                CallableStatement stmt = connection.prepareCall(sql1);
                stmt.setString(1, jfa1);
               boolean hasResult=stmt.execute();
               if(hasResult) {
                   rs=stmt.getResultSet();
                   String str="�ó��Ľ��Ϊ";
                   if(rs.next()) {
                       str = str + rs.getString(2);
                   }
                   else{
                       str = str +"0";
                   }
                   JOptionPane.showMessageDialog
                           (null,str,"���",JOptionPane.INFORMATION_MESSAGE);
                   jf1.setText(null);
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
