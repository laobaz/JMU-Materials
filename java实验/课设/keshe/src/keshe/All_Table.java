package keshe;

import javax.swing.*;
import java.awt.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class All_Table extends JFrame {//显示数据库所以内容的table
    connection c=new connection();
    Connection connection=c.getConnect();//连接数据库
    JButton jButton_back=new JButton("关闭");
    public All_Table(){
        this.setVisible(true);
        this.setSize(700,500);//设置界面
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        ResultSet rs;
        PreparedStatement ps;
        try {
            this.setTitle("全部账单信息");
            String sql = "select * from bills";
            ps=connection.prepareStatement(sql,ResultSet.TYPE_SCROLL_INSENSITIVE,
                    ResultSet.CONCUR_READ_ONLY);
            rs=ps.executeQuery();
            rs.last();
            int row=rs.getRow();
            rs.first();
            String arr[]={"记录号","支出项目","价格","日期","类别","备注","贷款"};
            String table[][] =new String[row][7];//把数据库中所有的内容写入到table数组中
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
            JTable jTable=new JTable(table,arr);//建立JTable组件
            jTable.setPreferredScrollableViewportSize(new Dimension(700,300));
            add(new JScrollPane(jTable),BorderLayout.CENTER);
            add(jButton_back,BorderLayout.SOUTH);
            pack();
            rs.close();
            connection.close();//关闭连接

        }catch (Exception ignored){
        }
        jButton_back.addActionListener(e -> {
            try {
                new Search();
                connection.close();//返回上一个界面
                dispose();
            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }


        });
    }
}
