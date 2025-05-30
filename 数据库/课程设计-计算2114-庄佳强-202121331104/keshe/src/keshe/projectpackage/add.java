package keshe.projectpackage;

import keshe.leaderpackage.leader;
import keshe.template.Default_template;
import keshe.template.Output_list;
import keshe.template.connection;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import java.awt.*;
import java.sql.*;

public class add extends JFrame {
    keshe.template.connection c = new connection();
    Connection connection = c.getConnect();        //连接上数据库
    JTextField jf1 = new JTextField(10);
    JTextField jf2 = new JTextField(10);
    JTextField jf3 = new JTextField(10);
    JTextField jf4 = new JTextField(10);
    JTextField jf5 = new JTextField(10);
    JTextField jf6 = new JTextField(10);


    JFileChooser chooser;
    JTable jTable=null;

    JButton jButton_Certain, jButton_Back,File_choose;

    add() {
        new Default_template(this);
        setLocation((getSize().width)/2,(getSize().height)/2);
        setSize(1500,400);
        setTitle("protect表add例程");
        init();
    }

    private void init() {

        jButton_Certain = new JButton("确定添加");
        jButton_Back = new JButton("返回上一级");
        File_choose=new JButton("选择图片文件");
        JPanel pnorth = new JPanel();       //建立JPanel存放个个按钮和JLabel
        pnorth.setLayout(new FlowLayout());
        pnorth.add(new JLabel("项目名称："));
        pnorth.add(jf1);
        pnorth.add(new JLabel("项目等级："));
        pnorth.add(jf2);
        pnorth.add(new JLabel("领导人："));
        pnorth.add(jf3);
        pnorth.add(new JLabel("开始时间："));
        pnorth.add(jf4);
        pnorth.add(new JLabel("预算："));
        pnorth.add(jf5);
        pnorth.add(new JLabel("图片"));
        pnorth.add(jf6);
        pnorth.add(File_choose);
        pnorth.add(jButton_Certain);
        pnorth.add(jButton_Back);
        add(pnorth,BorderLayout.NORTH);
        ;


        String sql="{call project_select()}";
        Output_list outputList=new Output_list();
        jTable=outputList.Output(sql);
        jTable.setPreferredScrollableViewportSize(new Dimension(900, 300));
        add(new JScrollPane(jTable), BorderLayout.SOUTH);

        File_choose.addActionListener(e -> {
            chooser=new JFileChooser();
            int result =chooser.showOpenDialog(null);
            if(result==JFileChooser.APPROVE_OPTION){
                String filePath=chooser.getSelectedFile().getAbsolutePath();
                jf6.setText(filePath);
            }
        });

        jButton_Certain.addActionListener(e -> {
            ResultSet rs;
            try {
                String jfa1 = jf1.getText();//获取输入的个个内容
                String jfa2 = jf2.getText();
                String jfa3 = jf3.getText();
                String jfa4 = jf4.getText();
                String jfa5 = jf5.getText();
                String jfa6 = jf6.getText();

                if (jfa1.equals("") || jfa2.equals("")||
                        jfa3.equals("")||jfa4.equals("")||jfa5.equals("")||jfa6.equals("")){ //有一个内容为不存在提醒他输入完全

                    JOptionPane.showMessageDialog(null,
                            "请输入完整的信息！", "警告", JOptionPane.WARNING_MESSAGE);
                    return;
                }
                boolean flag = false;
                String sql1 = "select project_name from course_design.project";
                Statement statement = connection.createStatement();
                rs = statement.executeQuery(sql1);
                while (rs.next())
                {
                    String Mark = rs.getString(1);
                    if (jfa1.equals(Mark)) {
                        flag = true;
                    }
                }
                if (flag) {
                    JOptionPane.showMessageDialog(null,
                            "该项目已经存在", "", JOptionPane.WARNING_MESSAGE);
                    jf1.setText(null);//清空文本框
                    jf2.setText(null);
                    jf3.setText(null);
                    jf4.setText(null);
                    jf5.setText(null);
                    jf6.setText(null);
                } else {
                    sql1="{call project_insert(?,?,?,?,?,?)}";
                    CallableStatement stmt=connection.prepareCall(sql1);
                    stmt.setString(1,jfa1);
                    stmt.setString(2,jfa2);
                    stmt.setString(3,jfa3);
                    stmt.setString(4,jfa4);
                    stmt.setString(5,jfa5);
                    stmt.setString(6,jfa6);
                    flag= stmt.execute();
                    if (flag==false) {
                        JOptionPane.showMessageDialog(null, "添加成功");
                        jf1.setText(null);
                        jf2.setText(null);
                        jf3.setText(null);
                        jf4.setText(null);
                        jf5.setText(null);
                        jf6.setText(null);
                    }
                }
            } catch (Exception ex) {
                System.out.println(ex);
                JOptionPane.showMessageDialog(null, "输入出现错误,请检查是否存在领导人和时间是否正确");

            }

            //重新读取一次数据库的内容实现实时刷新
            outputList.Output(sql);
            TableModel tableModel=new DefaultTableModel(outputList.table,outputList.arr);//实现实时刷新
            jTable.setModel(tableModel);

        });
        jButton_Back.addActionListener(e -> {
            new project().setVisible(true);//返回上一个界面
            try {
                connection.close();

            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
            dispose();
        });

    }
}
