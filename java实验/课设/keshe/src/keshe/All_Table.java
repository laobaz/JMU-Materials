package keshe;

import javax.swing.*;
import java.awt.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class All_Table extends JFrame {//��ʾ���ݿ��������ݵ�table
    connection c=new connection();
    Connection connection=c.getConnect();//�������ݿ�
    JButton jButton_back=new JButton("�ر�");
    public All_Table(){
        this.setVisible(true);
        this.setSize(700,500);//���ý���
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        ResultSet rs;
        PreparedStatement ps;
        try {
            this.setTitle("ȫ���˵���Ϣ");
            String sql = "select * from bills";
            ps=connection.prepareStatement(sql,ResultSet.TYPE_SCROLL_INSENSITIVE,
                    ResultSet.CONCUR_READ_ONLY);
            rs=ps.executeQuery();
            rs.last();
            int row=rs.getRow();
            rs.first();
            String arr[]={"��¼��","֧����Ŀ","�۸�","����","���","��ע","����"};
            String table[][] =new String[row][7];//�����ݿ������е�����д�뵽table������
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
            JTable jTable=new JTable(table,arr);//����JTable���
            jTable.setPreferredScrollableViewportSize(new Dimension(700,300));
            add(new JScrollPane(jTable),BorderLayout.CENTER);
            add(jButton_back,BorderLayout.SOUTH);
            pack();
            rs.close();
            connection.close();//�ر�����

        }catch (Exception ignored){
        }
        jButton_back.addActionListener(e -> {
            try {
                new Search();
                connection.close();//������һ������
                dispose();
            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }


        });
    }
}
