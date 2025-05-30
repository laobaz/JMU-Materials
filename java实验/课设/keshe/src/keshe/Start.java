package keshe;

import javax.swing.*;
import java.awt.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Locale;


public class Start extends JFrame {
   connection c=new connection();
   Connection connection=c.getConnect();
    JTextField jTextField;
    JTextField jTextField_code;
    JButton  buttonA,buttonB,buttonC;//��¼��ע��
    JLabel JLabel_1,JLabel_2;
    Start(){
        init();
        setTitle("��ӭ��ʹ�ñ�ϵͳ");
    }
    void init() {//�����UI�������
        JLabel_1=new JLabel("�û���:",JLabel.LEFT);   //�û���
        JLabel_2=new JLabel("����:    ",JLabel.LEFT);
        jTextField=new JTextField(15);                //���벿��
        jTextField_code=new JTextField(15);
        buttonA=new JButton("��¼");
        buttonB=new JButton("ע��");
        buttonC=new JButton("��������");
        Container c=this.getContentPane();
        c.setLayout(new FlowLayout());
        c.add(JLabel_1);
        c.add(jTextField);
        c.add(JLabel_2);
        c.add(jTextField_code);
        c.add(buttonA);
        c.add(buttonB);
        c.add(buttonC);

        this.setResizable(false);
        this.setSize(250,150);
        //������ʾ����
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        validate();
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //���õ��밴ť��Ӧ
        buttonA.addActionListener(e -> {
            PreparedStatement ps;
            ResultSet rs;
            try {
                String Account=jTextField.getText();
                String Code=jTextField_code.getText();
                String sql="select * from admin where Account = ? and Code = ?";//����admin���ݿ����Ƿ��и�����
                ps=connection.prepareStatement(sql);
                ps.setString(1,Account);
                ps.setString(2,Code);
                rs=ps.executeQuery();
                if(rs.next()){
                    new windowUI().setVisible(true);
                    dispose();
                }else{
                    JOptionPane.showMessageDialog(null,
                            "�û������������","����",JOptionPane.WARNING_MESSAGE);//��������������
                    jTextField_code.setText("");
                }
            }catch (Exception ex){
                System.out.println(e);

            }
        }
        );
        buttonB.addActionListener(e -> {
                    PreparedStatement ps;
                    ResultSet rs;
                    boolean flag = false;
                    try {
                        String Account = jTextField.getText();
                        String Code = jTextField_code.getText();
                        if (Account.isEmpty() || Code.isEmpty()) {//����˺Ż��������Ƿ�Ϊ��
                            JOptionPane.showMessageDialog(null,
                                    "�˺����벻��Ϊ��", " ", JOptionPane.WARNING_MESSAGE);
                            jTextField.setText("");
                            jTextField_code.setText("");
                            return;
                        }
                        String sql2 = "select * from admin";
                        Statement sql = connection.createStatement();
                        rs = sql.executeQuery(sql2);
                        while (rs.next()) {//����˺��Ƿ��Ѿ�ӵ��
                            String Acc = rs.getString(1);
                            String co = rs.getString(2);
                            if (Acc.equals(Account)) {
                                flag = true;
                            }
                        }
                        if (flag) {
                            JOptionPane.showMessageDialog(null,//��ʱ��������
                                    "�˺��Ѵ���,����������", "����", JOptionPane.WARNING_MESSAGE);
                            jTextField.setText(null);
                            jTextField_code.setText(null);
                        } else {//�������
                            String sql3 = "insert into admin(Account,Code) values(?,?)";
                            ps = connection.prepareStatement(sql3);
                            ps.setString(1, Account);
                            ps.setString(2, Code);
                            int count = ps.executeUpdate();
                            if (count > 0) {
                                JOptionPane.showMessageDialog(null, "ע��ɹ�");
                                jTextField.setText(null);
                                jTextField_code.setText(null);
                            }
                        }
                    } catch (Exception ex) {
                        System.out.println(e);

                    }
                }
        );
        buttonC.addActionListener(e -> {//��������
            String Account =JOptionPane.showInputDialog(null,
                    "�������õ��˺�","",JOptionPane.PLAIN_MESSAGE);

           String str= JOptionPane.showInputDialog(null,
                   "�������Ա��������","��ʾ",JOptionPane.PLAIN_MESSAGE);
           if(str.toLowerCase(Locale.ROOT).equals("laoba"))//�������Ա����
           {
               String Code=JOptionPane.showInputDialog(null,
                       "�������õ�����","",JOptionPane.PLAIN_MESSAGE);
               String update="update admin set Code='"+Code+"'where Account='"+Account+"'";//�����˺�����
               try {
                   Statement sql = connection.createStatement();
                   int ok = sql.executeUpdate(update);

               }catch (Exception ex){System.out.println(ex);}
           }
           else {
               JOptionPane.showMessageDialog(null,
                       "�������"," ",JOptionPane.WARNING_MESSAGE);
           }
        });

    }
}
