package keshe;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import java.awt.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;


public class Obscure extends JFrame {   //模糊查找
    JTextField jTextField=new JTextField(10);
    connection c=new connection();
    Connection connection=c.getConnect();
    JTable jTable=null;
    JButton jButton_Obscures, jButton_back;
    JLabel jLabel=new JLabel("支持模糊查询选项");
    JComboBox<String>jComboBox=new JComboBox<>();
    Obscure() {
        setTitle("模糊查找");
        setVisible(true);
        init();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    private void init() {
        this.setResizable(false);
        jComboBox.addItem("记录号");
        jComboBox.addItem("支出项目");
        this.setSize(700,500 );//设置界面
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width - this.getSize().width) / 2,
                (screen.height - this.getSize().height) / 2);
        jButton_Obscures = new JButton("查找");
        jButton_back = new JButton("返回上一级");
        JPanel pnorth = new JPanel();
        pnorth.setLayout(new FlowLayout());
        pnorth.add(jTextField);
        pnorth.add(jButton_Obscures);
        pnorth.add(jButton_back);
        pnorth.add(jComboBox);
        pnorth.add(jLabel);
        add(pnorth, BorderLayout.NORTH);
        String arr[]={"记录号","支出项目","价格","日期","类别","备注","贷款"};//
        String tables[][]=new String[0][0];//初始化tables为null
        jTable=new JTable(tables,arr);//建立一个只有arr[]内容的table
        jTable.setPreferredScrollableViewportSize(new Dimension(700,300));
        add(new JScrollPane(jTable),BorderLayout.SOUTH);
        jButton_Obscures.addActionListener(e -> {
            try{
                ResultSet rs;
                PreparedStatement ps = null;
                String ob =jTextField.getText();
                String sql = "select * from bills where expend like '%"+ob+"%'";
                String sql1="select * from bills where Mark like '%"+ob+"%'";//模糊查询对于的内容
                String choice=jComboBox.getSelectedItem().toString();
                if(choice.equals("记录号"))
                {
                    ps=connection.prepareStatement(sql1,ResultSet.TYPE_SCROLL_INSENSITIVE,
                            ResultSet.CONCUR_READ_ONLY);
                }
                else if(choice.equals("支出项目")) {
                    ps = connection.prepareStatement(sql, ResultSet.TYPE_SCROLL_INSENSITIVE,
                            ResultSet.CONCUR_READ_ONLY);
                }
                rs=ps.executeQuery();
                rs.last();
                int row=rs.getRow();
                rs.first();
                String table[][] =new String[row][7];
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
                if(row==0)
                    JOptionPane.showMessageDialog(null,
                            "没有查询到相关信息", "抱歉", JOptionPane.PLAIN_MESSAGE);//不存在跳出提示

                TableModel tableModel=new DefaultTableModel(table,arr);//建立tableModel用于实时刷新JTable
                jTable.setModel(tableModel);
                jTextField.setText("");
                rs.close();
            } catch (Exception ignored) {
            }
        });

        jButton_back.addActionListener(e -> {
            new Search();
            dispose();
        });
    }

}


