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
    JButton  buttonA,buttonB,buttonC;//登录，注册
    JLabel JLabel_1,JLabel_2;
    Start(){
        init();
        setTitle("欢迎你使用本系统");
    }
    void init() {//登入的UI界面出现
        JLabel_1=new JLabel("用户名:",JLabel.LEFT);   //用户名
        JLabel_2=new JLabel("密码:    ",JLabel.LEFT);
        jTextField=new JTextField(15);                //输入部分
        jTextField_code=new JTextField(15);
        buttonA=new JButton("登录");
        buttonB=new JButton("注册");
        buttonC=new JButton("忘记密码");
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
        //界面显示居中
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        validate();
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //设置登入按钮相应
        buttonA.addActionListener(e -> {
            PreparedStatement ps;
            ResultSet rs;
            try {
                String Account=jTextField.getText();
                String Code=jTextField_code.getText();
                String sql="select * from admin where Account = ? and Code = ?";//查找admin数据库中是否有该数据
                ps=connection.prepareStatement(sql);
                ps.setString(1,Account);
                ps.setString(2,Code);
                rs=ps.executeQuery();
                if(rs.next()){
                    new windowUI().setVisible(true);
                    dispose();
                }else{
                    JOptionPane.showMessageDialog(null,
                            "用户名或密码错误","错误",JOptionPane.WARNING_MESSAGE);//不存在跳出警告
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
                        if (Account.isEmpty() || Code.isEmpty()) {//检查账号或者密码是否为空
                            JOptionPane.showMessageDialog(null,
                                    "账号密码不能为空", " ", JOptionPane.WARNING_MESSAGE);
                            jTextField.setText("");
                            jTextField_code.setText("");
                            return;
                        }
                        String sql2 = "select * from admin";
                        Statement sql = connection.createStatement();
                        rs = sql.executeQuery(sql2);
                        while (rs.next()) {//检查账号是否已经拥有
                            String Acc = rs.getString(1);
                            String co = rs.getString(2);
                            if (Acc.equals(Account)) {
                                flag = true;
                            }
                        }
                        if (flag) {
                            JOptionPane.showMessageDialog(null,//有时发出警告
                                    "账号已存在,请重新输入", "警告", JOptionPane.WARNING_MESSAGE);
                            jTextField.setText(null);
                            jTextField_code.setText(null);
                        } else {//否则存入
                            String sql3 = "insert into admin(Account,Code) values(?,?)";
                            ps = connection.prepareStatement(sql3);
                            ps.setString(1, Account);
                            ps.setString(2, Code);
                            int count = ps.executeUpdate();
                            if (count > 0) {
                                JOptionPane.showMessageDialog(null, "注册成功");
                                jTextField.setText(null);
                                jTextField_code.setText(null);
                            }
                        }
                    } catch (Exception ex) {
                        System.out.println(e);

                    }
                }
        );
        buttonC.addActionListener(e -> {//重置密码
            String Account =JOptionPane.showInputDialog(null,
                    "输入重置的账号","",JOptionPane.PLAIN_MESSAGE);

           String str= JOptionPane.showInputDialog(null,
                   "输入管理员密码重置","提示",JOptionPane.PLAIN_MESSAGE);
           if(str.toLowerCase(Locale.ROOT).equals("laoba"))//输入管理员密码
           {
               String Code=JOptionPane.showInputDialog(null,
                       "输入重置的密码","",JOptionPane.PLAIN_MESSAGE);
               String update="update admin set Code='"+Code+"'where Account='"+Account+"'";//重置账号密码
               try {
                   Statement sql = connection.createStatement();
                   int ok = sql.executeUpdate(update);

               }catch (Exception ex){System.out.println(ex);}
           }
           else {
               JOptionPane.showMessageDialog(null,
                       "输入错误"," ",JOptionPane.WARNING_MESSAGE);
           }
        });

    }
}
