package keshe;

import javax.swing.*;
import java.awt.*;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Locale;

public class search_Mark extends JFrame {//记录号查找
    connection c = new connection();
    Connection connection = c.getConnect();
     JTextField jTextField = new JTextField(10);
     JButton jButton_search, jButton_back;

    search_Mark() {
        init();
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private void init() {
        this.setResizable(false);
        this.setSize(455,150);
        //界面显示居中
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        validate();
        setTitle("按记录号查找");
        jButton_search = new JButton("查找");
        jButton_back = new JButton("返回上一级");
        JPanel pnorth = new JPanel();
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("记录号:"));
        pnorth.add(jTextField);
        pnorth.add(jButton_search);
        pnorth.add(jButton_back);
        add(pnorth, BorderLayout.CENTER);
        jButton_search.addActionListener(e -> {
            try {
                Statement ps;
                ResultSet rs;
                String Marks = null,expend = null,price = null,Date = null,
                        type = null,Memo = null,Loan = null;
                String Mark = jTextField.getText();
                String sql = "select * from bills";
                ps = connection.createStatement();
                rs = ps.executeQuery(sql);
                boolean flag = false;
                while (rs.next()) {
                    Marks = rs.getString(1);
                    expend = rs.getString(2);
                    price = rs.getString(3);
                    Date = rs.getString(4);
                    type = rs.getString(5);
                    Memo = rs.getString(6);
                    Loan = rs.getString(7);
                    if (Mark.toLowerCase(Locale.ROOT).equals(Marks.toLowerCase(Locale.ROOT)))
                    {
                        flag = true;
                        break;
                    }
                }
                jTextField.setText("");
                if (flag) {
                    JOptionPane.showMessageDialog(null, "查找成功"+"\n\t"+"记录号:" + Marks + "\n\t" + "支出项目:" + expend + "\n\t" + "价格:" + price + "\n\t"+ "日期:" + Date + "\n\t" + "类型:" + type + "\n\t" + "备忘:" + Memo + "\n\t" + "贷款:" + Loan + "\n\t"  );

                } else {
                    JOptionPane.showMessageDialog(null, "该记录号不存在");
                }
            } catch (Exception ignored) {
            }


        });
        jButton_back.addActionListener(e -> {
            new Search();
            try {
                connection.close();
            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
            dispose();
        });

    }
}
