package keshe;

import javax.swing.*;
import java.awt.*;
import java.sql.*;

public class Add extends JFrame {   //添加操作
    connection c=new connection();
    Connection connection=c.getConnect();        //连接上数据库
    JTextField jf1=new JTextField(10);   //添加个个按键
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
        jf7.addItem("是");
        jf7.addItem("否");
        setTitle("添加账单信息");
        this.setResizable(false);
        this.setSize(550,150);
        //界面显示居中
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        validate();
        init();
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
   private void init(){
        jButton_Certain=new JButton("确定添加");
        jButton_Back=new JButton("返回上一级");
        JPanel pnorth=new JPanel();       //建立JPanel存放个个按钮和JLabel
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("记录号："));
        pnorth.add(jf1);
        pnorth.add(new JLabel("支出项目："));
        pnorth.add(jf2);
        pnorth.add(new JLabel("支出金额："));
        pnorth.add(jf3);
        pnorth.add(new JLabel("日期："));
        pnorth.add(jf4);
        pnorth.add(new JLabel("年"));
        pnorth.add(jf44);
        pnorth.add(new JLabel("月"));
        pnorth.add(jf444);
        pnorth.add(new JLabel("日"));
        pnorth.add(new JLabel("类型："));
        pnorth.add(jf5);
        pnorth.add(new JLabel("备忘："));
        pnorth.add(jf6);
        pnorth.add(new JLabel("是否贷款："));
        pnorth.add(jf7);
        pnorth.add(jButton_Certain);
        pnorth.add(jButton_Back);
        add(pnorth, BorderLayout.CENTER);
        jButton_Certain.addActionListener(e -> {
            PreparedStatement ps;
            ResultSet rs;
            try {
                String jfa1=jf1.getText();//获取输入的个个内容
                String jfa2=jf2.getText();
                String jfa3=jf3.getText();
                String jfa4=jf4.getText();
                String jfa44=jf44.getText();
                String jfa444=jf444.getText();
                String jfa5=jf5.getText();
                String jfa6=jf6.getText();
                String jfa7=jf7.getSelectedItem().toString();
                if (jfa1.equals("")||jfa2.equals("")||  //有一个内容为不存在提醒他输入完全
                        jfa3.equals("")||jfa4.equals("")||jfa44.equals("")||jfa444.equals("")||
                        jfa5.equals("")||jfa6.equals("")||
                        jfa7.equals("")){
                    JOptionPane.showMessageDialog(null,
                            "请输入完整的信息！","警告",JOptionPane.WARNING_MESSAGE);
                    return;
                }
                boolean flag=false;
                String sql="select Mark from bills";
                Statement statement =connection.createStatement();
                rs=statement.executeQuery(sql);
                while(rs.next())//检查Mark记录号是否存在  ，记录号不能相同
                {
                    String Mark=rs.getString(1);
                    if(jfa1.equals(Mark)){
                        flag=true;
                    }
                }
                if(flag)
                {
                    JOptionPane.showMessageDialog(null,
                            "该账单编号已经存在","",JOptionPane.WARNING_MESSAGE);
                    jf1.setText(null);//清空文本框
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
                    ps.setString(2,jfa2);//写入到数据库中
                    ps.setString(3,jfa3);
                    ps.setString(4,jfa4);
                    ps.setString(5,jfa5);
                    ps.setString(6,jfa6);
                    ps.setString(7,jfa7);
                    int count=ps.executeUpdate();
                    if (count>0){
                        JOptionPane.showMessageDialog(null,"添加成功");
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
                JOptionPane.showMessageDialog(null,"输入出现错误,请检查日期格式");
            }


        });
        jButton_Back.addActionListener(e -> {
            new windowUI().setVisible(true);//返回上一个界面
            try {
                connection.close();
            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
            dispose();
        });

}
}
