package keshe;

import keshe.template.connection;

import javax.swing.*;
import java.awt.*;
import java.sql.*;
import java.util.Locale;


public class Start extends JFrame {
   keshe.template.connection c=new connection();
   Connection connection=c.getConnect();
    JTextField jTextField;
    JTextField jTextField_code;
    JButton  buttonA,buttonB,buttonC;//��¼��ע��
    JLabel JLabel_1,JLabel_2;
    Start(){
        init();
        setTitle("��ӭʹ�ÿ�����Ŀ����ϵͳ");
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
        this.setSize(450,250);
        //������ʾ����
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        validate();
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //���õ��밴ť��Ӧ
        buttonA.addActionListener(e -> {
            ResultSet rs;
            try {
                String Account=jTextField.getText();
                String Code=jTextField_code.getText();
                //ʹ�����̴����¼�¼�
                String sql="{call Authentication_login(?,?)}";//����user���ݿ����Ƿ��и�����
                CallableStatement stmt=connection.prepareCall(sql);
                stmt.setString(1,Account);
                stmt.setString(2,Code);
                boolean hasResult=stmt.execute();
                System.out.println(hasResult);

                if(hasResult) {
                    rs = stmt.getResultSet();//��ý����
                    if(rs.next()) {
                        //connection.setCatalog(Account);
                        //keshe.template.connection.user=Account;
                        //keshe.template.connection.password=Code;
                        new windowUI().setVisible(true);
                        dispose();
                    }else{
                        JOptionPane.showMessageDialog(null,
                                "�û������������", "����", JOptionPane.WARNING_MESSAGE);//��������������
                        jTextField_code.setText("");
                    }
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
                        String str = "select * from course_design.user";
                        ps = connection.prepareStatement(str);
                        rs = ps.executeQuery(str);
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
                            String sql = "{call New_user_registration(?,?)}";
                            CallableStatement stmt=connection.prepareCall(sql);
                            stmt.setString(1,Account);
                            stmt.setString(2,Code);
                            boolean right= stmt.execute();//ִ�д洢����
                            //�����½�ɫ
                            //Statement  statement=connection.createStatement();
                            //statement.execute("create user '"+Account+"'@'localhost' Identified by'"+Code+"'");
                            //statement.execute("grant select,insert,update,delete on course_design.* to'"+Account+"'@'localhost'");

                            if (right==false) {
                                JOptionPane.showMessageDialog(null, "ע��ɹ�");
                                jTextField.setText(null);
                                jTextField_code.setText(null);
                            }
                            else{

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
               String update="{call update_login(?,?)}";//�����˺�����
               try {
                   CallableStatement stmt=connection.prepareCall(update);
                   stmt.setString(1,Account);
                   stmt.setString(2,Code);
                   boolean right=stmt.execute();
                   if(right==false){
                       JOptionPane.showMessageDialog
                               (null,"���³ɹ�","",JOptionPane.INFORMATION_MESSAGE);
                   }

               }catch (Exception ex)
               {System.out.println(ex);}
           }
           else {
               JOptionPane.showMessageDialog(null,
                       "�������"," ",JOptionPane.WARNING_MESSAGE);
           }
        });

    }
}
