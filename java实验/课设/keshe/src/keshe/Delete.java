package keshe;

import javax.swing.*;
import java.awt.*;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Locale;

public class Delete extends JFrame {//ɾ������
    connection c=new connection();
    Connection connection=c.getConnect();
    JTextField jTextField=new JTextField(10);
    JButton jButton_certain,jButton_back;
    Delete(){
        setTitle("ɾ���˵���Ϣ");
        init();
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    private void init(){
        this.setResizable(false);
        this.setSize(455,150);
        //������ʾ����
        Dimension screen = this.getToolkit().getScreenSize();//���ý���
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        validate();
        jButton_certain=new JButton("ȷ��ɾ��");
        jButton_back=new JButton("������һ��");
        JPanel pnorth=new JPanel();
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("��¼�ţ�"));
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
                    if(Mark.toLowerCase(Locale.ROOT).equals(jTextFieldText))//�ҳ����ݿ����Ƿ�����ͬ��Mark
                        flag=true;
                }
                if (flag) {
                    String sql1 = "delete from bills where Mark = '" + jTextFieldText + "'";
                    statement.executeUpdate(sql1);//ɾ������
                    JOptionPane.showMessageDialog(null, "ɾ���ɹ�");
                    jTextField.setText(null);
                } else {
                    JOptionPane.showMessageDialog(null, "�ü�¼�Ŷ�Ӧ�˵�������");
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
