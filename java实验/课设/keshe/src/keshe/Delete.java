package keshe;

import javax.swing.*;
import java.awt.*;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Locale;

public class Delete extends JFrame {//删除操作
    connection c=new connection();
    Connection connection=c.getConnect();
    JTextField jTextField=new JTextField(10);
    JButton jButton_certain,jButton_back;
    Delete(){
        setTitle("删除账单信息");
        init();
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    private void init(){
        this.setResizable(false);
        this.setSize(455,150);
        //界面显示居中
        Dimension screen = this.getToolkit().getScreenSize();//设置界面
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        validate();
        jButton_certain=new JButton("确定删除");
        jButton_back=new JButton("返回上一级");
        JPanel pnorth=new JPanel();
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("记录号："));
        pnorth.add(jTextField);
        pnorth.add(jButton_certain);
        pnorth.add(jButton_back);
        add(pnorth, BorderLayout.CENTER);
        jButton_certain.addActionListener(e -> {
            try {
                Statement statement;
                statement = connection.createStatement();
                String jTextFieldText = jTextField.getText();
                String sql = "select Mark from bills";
                ResultSet rs = statement.executeQuery(sql);
                boolean flag=false;
                while (rs.next()){
                    String Mark =rs.getString(1);
                    if(Mark.toLowerCase(Locale.ROOT).equals(jTextFieldText))//找出数据库中是否有相同的Mark
                        flag=true;
                }
                if (flag) {
                    String sql1 = "delete from bills where Mark = '" + jTextFieldText + "'";
                    statement.executeUpdate(sql1);//删除操作
                    JOptionPane.showMessageDialog(null, "删除成功");
                    jTextField.setText(null);
                } else {
                    JOptionPane.showMessageDialog(null, "该记录号对应账单不存在");
                    jTextField.setText(null);
                }
            }catch (Exception ignored){
            }
        });
        jButton_back.addActionListener(e -> {
            new windowUI().setVisible(true);
            dispose();
        });
    }
}
