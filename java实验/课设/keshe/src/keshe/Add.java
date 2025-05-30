package keshe;

import javax.swing.*;
import java.awt.*;
import java.sql.*;

public class Add extends JFrame {   //��Ӳ���
    connection c=new connection();
    Connection connection=c.getConnect();        //���������ݿ�
    JTextField jf1=new JTextField(10);   //��Ӹ�������
    JTextField jf2=new JTextField(10);
    JTextField jf3=new JTextField(10);
    JTextField jf4=new JTextField(5);
    JTextField jf44=new JTextField(5);
    JTextField jf444=new JTextField(5);

    JTextField jf5=new JTextField(10);
    JTextField jf6=new JTextField(20);
    JComboBox<String> jf7=new JComboBox<>();

    JButton jButton_Certain,jButton_Back;
    Add(){
        jf7.addItem("��");
        jf7.addItem("��");
        setTitle("����˵���Ϣ");
        this.setResizable(false);
        this.setSize(550,150);
        //������ʾ����
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        validate();
        init();
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
   private void init(){
        jButton_Certain=new JButton("ȷ�����");
        jButton_Back=new JButton("������һ��");
        JPanel pnorth=new JPanel();       //����JPanel��Ÿ�����ť��JLabel
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("��¼�ţ�"));
        pnorth.add(jf1);
        pnorth.add(new JLabel("֧����Ŀ��"));
        pnorth.add(jf2);
        pnorth.add(new JLabel("֧����"));
        pnorth.add(jf3);
        pnorth.add(new JLabel("���ڣ�"));
        pnorth.add(jf4);
        pnorth.add(new JLabel("��"));
        pnorth.add(jf44);
        pnorth.add(new JLabel("��"));
        pnorth.add(jf444);
        pnorth.add(new JLabel("��"));
        pnorth.add(new JLabel("���ͣ�"));
        pnorth.add(jf5);
        pnorth.add(new JLabel("������"));
        pnorth.add(jf6);
        pnorth.add(new JLabel("�Ƿ���"));
        pnorth.add(jf7);
        pnorth.add(jButton_Certain);
        pnorth.add(jButton_Back);
        add(pnorth, BorderLayout.CENTER);
        jButton_Certain.addActionListener(e -> {
            PreparedStatement ps;
            ResultSet rs;
            try {
                String jfa1=jf1.getText();//��ȡ����ĸ�������
                String jfa2=jf2.getText();
                String jfa3=jf3.getText();
                String jfa4=jf4.getText();
                String jfa44=jf44.getText();
                String jfa444=jf444.getText();
                String jfa5=jf5.getText();
                String jfa6=jf6.getText();
                String jfa7=jf7.getSelectedItem().toString();
                if (jfa1.equals("")||jfa2.equals("")||  //��һ������Ϊ������������������ȫ
                        jfa3.equals("")||jfa4.equals("")||jfa44.equals("")||jfa444.equals("")||
                        jfa5.equals("")||jfa6.equals("")||
                        jfa7.equals("")){
                    JOptionPane.showMessageDialog(null,
                            "��������������Ϣ��","����",JOptionPane.WARNING_MESSAGE);
                    return;
                }
                boolean flag=false;
                String sql="select Mark from bills";
                Statement statement =connection.createStatement();
                rs=statement.executeQuery(sql);
                while(rs.next())//���Mark��¼���Ƿ����  ����¼�Ų�����ͬ
                {
                    String Mark=rs.getString(1);
                    if(jfa1.equals(Mark)){
                        flag=true;
                    }
                }
                if(flag)
                {
                    JOptionPane.showMessageDialog(null,
                            "���˵�����Ѿ�����","",JOptionPane.WARNING_MESSAGE);
                    jf1.setText(null);//����ı���
                    jf2.setText(null);
                    jf3.setText(null);
                    jf4.setText(null);
                    jf44.setText(null);
                    jf444.setText(null);
                    jf5.setText(null);
                    jf6.setText(null);
                }

                else{
                    jfa4=jfa4+"-"+jfa44+"-"+jfa444;
                    String sql3="insert into bills(Mark,expend,price,Date,type, Memo,Loan)" +
                            " values(?,?,?,?,?,?,?)";
                    ps=connection.prepareStatement(sql3);
                    ps.setString(1,jfa1);
                    ps.setString(2,jfa2);//д�뵽���ݿ���
                    ps.setString(3,jfa3);
                    ps.setString(4,jfa4);
                    ps.setString(5,jfa5);
                    ps.setString(6,jfa6);
                    ps.setString(7,jfa7);
                    int count=ps.executeUpdate();
                    if (count>0){
                        JOptionPane.showMessageDialog(null,"��ӳɹ�");
                        jf1.setText(null);
                        jf2.setText(null);
                        jf3.setText(null);
                        jf4.setText(null);
                        jf44.setText(null);
                        jf444.setText(null);
                        jf5.setText(null);
                        jf6.setText(null);
                    }
                }
            }catch (Exception ex){
                JOptionPane.showMessageDialog(null,"������ִ���,�������ڸ�ʽ");
            }


        });
        jButton_Back.addActionListener(e -> {
            new windowUI().setVisible(true);//������һ������
            try {
                connection.close();
            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
            dispose();
        });

}
}
