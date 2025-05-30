package keshe;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import java.awt.*;
import java.sql.*;

public class Revise extends JFrame{
    connection c=new connection();
    Connection connection=c.getConnect();
    JTextField jTextField_Choice=new JTextField(10);   //选择Mark的文本框
    JTextField jTextField_Revise=new JTextField(10);   //要修改的内容的文本框
    JComboBox<String>jComboBox=new JComboBox<>();
    JButton jButton_Revise,jButton_back;
    JTable jTable;
    Revise(){
        setTitle("修改课程信息");
        init();
        setVisible(true);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
    }
    private void init(){
        this.setResizable(false);
        this.setSize(1000,400);
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width-this.getSize().width)/2,
                (screen.height-this.getSize().height)/2);
        validate();
        jButton_Revise=new JButton("确定修改");
        jButton_back=new JButton("返回上一级");
        Panel pnorth=new Panel();
        JLabel label=new JLabel("请输入待修改记录号:");
        label.setFont(new Font("宋体",Font.BOLD,12));
        pnorth.add(label);
        pnorth.add(new JLabel("记录号:"));
        pnorth.add(jTextField_Choice);
        JLabel label1=new JLabel("请选择你要修改的项目:");
        label1.setFont(new Font("宋体",Font.BOLD,12));
        pnorth.add(label1);
        String[]str={" ","expend","price","Date","type","Memo","Loan"};    //选择要修改的内容
        for(String s:str)
            jComboBox.addItem(s);
        pnorth.add(jComboBox);
        JLabel label2=new JLabel("请输入你要修改的内容:");
        label2.setFont(new Font("宋体",Font.BOLD,12));
        pnorth.add(label2);
        pnorth.add(jTextField_Revise);
        pnorth.add(jButton_Revise);
        pnorth.add(jButton_back);
        JLabel label3=new JLabel("expend:支出项目,price:价格,Date:日期,type:类别,Memo:批注,Loan：贷款");
        label3.setFont(new Font("宋体",Font.BOLD,12));
        pnorth.add(label3);
        add(pnorth);
        ResultSet rs;
        PreparedStatement ps;
        try {//将当前所有的内容读入到窗口中
            this.setTitle("修改信息");
            String sql = "select * from bills";
            ps = connection.prepareStatement(sql, ResultSet.TYPE_SCROLL_INSENSITIVE,
                    ResultSet.CONCUR_READ_ONLY);
            rs = ps.executeQuery();
            rs.last();
            int row = rs.getRow();
            rs.first();
            String arr[] = {"记录号", "支出项目", "价格", "日期", "类别", "备注", "贷款"};//
            String table[][] = new String[row][7];
            for (int i = 0; i < row; i++) {
                table[i][0] = rs.getString(1);
                table[i][1] = rs.getString(2);
                table[i][2] = rs.getString(3);
                table[i][3] = rs.getString(4);
                table[i][4] = rs.getString(5);
                table[i][5] = rs.getString(6);
                table[i][6] = rs.getString(7);
                rs.next();
            }
            jTable = new JTable(table, arr);
            jTable.setPreferredScrollableViewportSize(new Dimension(1000, 200));
            add(new JScrollPane(jTable), BorderLayout.SOUTH);

        }catch (Exception ex){}
        jButton_Revise.addActionListener(e -> {
            String Mark =jTextField_Choice.getText();
            String choice =jComboBox.getSelectedItem().toString();
            String Revise=jTextField_Revise.getText();
            String sql_update="update bills set "+choice+" ='"+Revise+"' where Mark='"+Mark+"'";//修改的字段
            Statement st;
            try {
                st = connection.createStatement();
                int ok =st.executeUpdate(sql_update);//修改
                st.close();
                String sql = "select * from bills";
                ResultSet rst;
                PreparedStatement pst;
                pst = connection.prepareStatement(sql, ResultSet.TYPE_SCROLL_SENSITIVE,
                        ResultSet.CONCUR_READ_ONLY);

                //重新读取一次数据库的内容实现实时刷新
                rst = pst.executeQuery();
                rst.last();
                int row = rst.getRow();
                rst.first();
                String arr[] = {"记录号", "支出项目", "价格", "日期", "类别", "备注", "贷款"};
                String table[][] = new String[row][7];
                for (int i = 0; i < row; i++) {
                    table[i][0] = rst.getString(1);
                    table[i][1] = rst.getString(2);
                    table[i][2] = rst.getString(3);
                    table[i][3] = rst.getString(4);
                    table[i][4] = rst.getString(5);
                    table[i][5] = rst.getString(6);
                    table[i][6] = rst.getString(7);
                    rst.next();
                }
                TableModel tableModel=new DefaultTableModel(table,arr);//实现实时刷新
                jTable.setModel(tableModel);
            }catch (Exception ex){}


        });
        jButton_back.addActionListener(e -> {

            new windowUI();
            try {
                connection.close();
            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
            dispose();
        });

    }
}
