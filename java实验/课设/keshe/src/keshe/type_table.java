package keshe;

import javax.swing.*;
import java.awt.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class type_table extends JFrame {//������Table
    connection c = new connection();
    Connection connection = c.getConnect();
    JButton jButton_back = new JButton("�ر�");

    type_table(String type) {
        this.setVisible(true);
        this.setSize(700, 500);
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width - this.getSize().width) / 2,
                (screen.height - this.getSize().height) / 2);
        ResultSet rs;
        PreparedStatement ps;
        try {
            this.setTitle("ȫ���˵���Ϣ");
            String sql = "select * from bills where type='"+type+"'";
            ps=connection.prepareStatement(sql,ResultSet.TYPE_SCROLL_INSENSITIVE,
                    ResultSet.CONCUR_READ_ONLY);
            rs=ps.executeQuery();
            rs.last();
            int row=rs.getRow();
            rs.first();
            String arr[]={"��¼��","֧����Ŀ","�۸�","����","���","��ע","����"};
            String table[][] =new String[row][7];
            //��ȡ��Ӧtype�����ݵ�row��
            for (int i=0;i<row;i++){
                table[i][0]=rs.getString(1);
                table[i][1]=rs.getString(2);
                table[i][2]=rs.getString(3);
                table[i][3]=rs.getString(4);
                table[i][4]=rs.getString(5);
                table[i][5]=rs.getString(6);
                table[i][6]=rs.getString(7);
                rs.next();
            }
            if(row==0) {
                JOptionPane.showMessageDialog(null,
                        "û�в�ѯ�������Ϣ", "", JOptionPane.PLAIN_MESSAGE);//������������ʾ
                new Search();
                connection.close();
                dispose();
            }
            JTable jTable=new JTable(table,arr);
            jTable.setPreferredScrollableViewportSize(new Dimension(700,300));
            add(new JScrollPane(jTable),BorderLayout.CENTER);
            add(jButton_back,BorderLayout.SOUTH);


            pack();
            rs.close();
            connection.close();

        }catch (Exception ex){
            System.out.println(ex);
        }
        jButton_back.addActionListener(e -> {
            try {
                new Search();
                connection.close();
                dispose();
            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }


        });
    }
}