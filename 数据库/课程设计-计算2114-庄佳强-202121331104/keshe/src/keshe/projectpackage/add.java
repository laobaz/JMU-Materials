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

public class add extends JFrame {
    keshe.template.connection c = new connection();
    Connection connection = c.getConnect();        //���������ݿ�
    JTextField jf1 = new JTextField(10);
    JTextField jf2 = new JTextField(10);
    JTextField jf3 = new JTextField(10);
    JTextField jf4 = new JTextField(10);
    JTextField jf5 = new JTextField(10);
    JTextField jf6 = new JTextField(10);


    JFileChooser chooser;
    JTable jTable=null;

    JButton jButton_Certain, jButton_Back,File_choose;

    add() {
        new Default_template(this);
        setLocation((getSize().width)/2,(getSize().height)/2);
        setSize(1500,400);
        setTitle("protect��add����");
        init();
    }

    private void init() {

        jButton_Certain = new JButton("ȷ�����");
        jButton_Back = new JButton("������һ��");
        File_choose=new JButton("ѡ��ͼƬ�ļ�");
        JPanel pnorth = new JPanel();       //����JPanel��Ÿ�����ť��JLabel
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("��Ŀ���ƣ�"));
        pnorth.add(jf1);
        pnorth.add(new JLabel("��Ŀ�ȼ���"));
        pnorth.add(jf2);
        pnorth.add(new JLabel("�쵼�ˣ�"));
        pnorth.add(jf3);
        pnorth.add(new JLabel("��ʼʱ�䣺"));
        pnorth.add(jf4);
        pnorth.add(new JLabel("Ԥ�㣺"));
        pnorth.add(jf5);
        pnorth.add(new JLabel("ͼƬ"));
        pnorth.add(jf6);
        pnorth.add(File_choose);
        pnorth.add(jButton_Certain);
        pnorth.add(jButton_Back);
        add(pnorth,BorderLayout.NORTH);
        ;


        String sql="{call project_select()}";
        Output_list outputList=new Output_list();
        jTable=outputList.Output(sql);
        jTable.setPreferredScrollableViewportSize(new Dimension(900, 300));
        add(new JScrollPane(jTable), BorderLayout.SOUTH);

        File_choose.addActionListener(e -> {
            chooser=new JFileChooser();
            int result =chooser.showOpenDialog(null);
            if(result==JFileChooser.APPROVE_OPTION){
                String filePath=chooser.getSelectedFile().getAbsolutePath();
                jf6.setText(filePath);
            }
        });

        jButton_Certain.addActionListener(e -> {
            ResultSet rs;
            try {
                String jfa1 = jf1.getText();//��ȡ����ĸ�������
                String jfa2 = jf2.getText();
                String jfa3 = jf3.getText();
                String jfa4 = jf4.getText();
                String jfa5 = jf5.getText();
                String jfa6 = jf6.getText();

                if (jfa1.equals("") || jfa2.equals("")||
                        jfa3.equals("")||jfa4.equals("")||jfa5.equals("")||jfa6.equals("")){ //��һ������Ϊ������������������ȫ

                    JOptionPane.showMessageDialog(null,
                            "��������������Ϣ��", "����", JOptionPane.WARNING_MESSAGE);
                    return;
                }
                boolean flag = false;
                String sql1 = "select project_name from course_design.project";
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
                            "����Ŀ�Ѿ�����", "", JOptionPane.WARNING_MESSAGE);
                    jf1.setText(null);//����ı���
                    jf2.setText(null);
                    jf3.setText(null);
                    jf4.setText(null);
                    jf5.setText(null);
                    jf6.setText(null);
                } else {
                    sql1="{call project_insert(?,?,?,?,?,?)}";
                    CallableStatement stmt=connection.prepareCall(sql1);
                    stmt.setString(1,jfa1);
                    stmt.setString(2,jfa2);
                    stmt.setString(3,jfa3);
                    stmt.setString(4,jfa4);
                    stmt.setString(5,jfa5);
                    stmt.setString(6,jfa6);
                    flag= stmt.execute();
                    if (flag==false) {
                        JOptionPane.showMessageDialog(null, "��ӳɹ�");
                        jf1.setText(null);
                        jf2.setText(null);
                        jf3.setText(null);
                        jf4.setText(null);
                        jf5.setText(null);
                        jf6.setText(null);
                    }
                }
            } catch (Exception ex) {
                System.out.println(ex);
                JOptionPane.showMessageDialog(null, "������ִ���,�����Ƿ�����쵼�˺�ʱ���Ƿ���ȷ");

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
