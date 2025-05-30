package keshe;

import javax.swing.*;
import java.awt.*;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Locale;

public class search_expend extends JFrame {//֧����Ŀ����
    connection c = new connection();
    Connection connection = c.getConnect();
    JTextField jTextField = new JTextField(10);
    JButton jButton_Search, jButton_back;

    search_expend() {
        setTitle("��֧����Ŀ����");
        init();
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private void init() {
        this.setResizable(false);
        this.setSize(455,150);
        //������ʾ����
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        validate();
        jButton_Search = new JButton("����");
        jButton_back = new JButton("������һ��");
        JPanel pnorth = new JPanel();
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("֧����Ŀ��"));
        pnorth.add(jTextField);
        pnorth.add(jButton_Search);
        pnorth.add(jButton_back);
        add(pnorth, BorderLayout.CENTER);
        jButton_Search.addActionListener(e -> {
            try {
                Statement ps;
                ResultSet rs;
                String Mark = null,expend = null,price = null,Date = null,
                        type = null,Memo = null,Loan = null;
                String Expend = jTextField.getText();
                String sql = "select * from bills";
                ps = connection.createStatement();
                rs = ps.executeQuery(sql);
                boolean flag = false;
                while (rs.next()) {
                    Mark = rs.getString(1);
                    expend = rs.getString(2);
                    price = rs.getString(3);
                    Date = rs.getString(4);
                    type = rs.getString(5);
                    Memo = rs.getString(6);
                    Loan = rs.getString(7);
                    if (Expend.toLowerCase(Locale.ROOT).equals(expend.toLowerCase(Locale.ROOT)))//���Ҷ�Ӧ��֧����Ŀ
                    {
                        flag = true;
                        break;
                    }
                }
                jTextField.setText("");
                if (flag) {
                    JOptionPane.showMessageDialog(null, "���ҳɹ�"+"\n\t"+"��¼��:" + Mark + "\n\t" + "֧����Ŀ:" + expend + "\n\t" + "�۸�:" + price + "\n\t"+ "����:" + Date + "\n\t" + "����:" + type + "\n\t" + "����:" + Memo + "\n\t" + "����:" + Loan + "\n\t"  );
                } else {
                    JOptionPane.showMessageDialog(null, "��֧����Ŀ������","",JOptionPane.WARNING_MESSAGE);
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
