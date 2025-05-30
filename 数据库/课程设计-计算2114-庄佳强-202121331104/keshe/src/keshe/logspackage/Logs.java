package keshe.logspackage;


import keshe.template.Default_template;
import keshe.template.Output_list;
import keshe.template.connection;
import keshe.windowUI;
import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Logs extends JFrame {
    keshe.template.connection c = new connection();
    Connection connection = c.getConnect();        //连接上数据库

    JTable jTable = null;

    JButton jButton_IO, jButton_Back;


   public Logs() {
        new Default_template(this);
        setSize(700, 600);
        init();
    }

    private void init() {

        jButton_Back = new JButton("返回上一级");
        jButton_IO=new JButton("导出日志");
        JPanel pnorth = new JPanel();       //建立JPanel存放个个按钮和JLabel
        pnorth.setLayout(new FlowLayout());

        pnorth.add(jButton_IO);
        pnorth.add(jButton_Back);
        add(pnorth, BorderLayout.NORTH);


        String sql = "{call logs_select()}";
        Output_list outputList = new Output_list();
        jTable = outputList.Output(sql);
        jTable.setPreferredScrollableViewportSize(new Dimension(600, 400));
        add(new JScrollPane(jTable), BorderLayout.SOUTH);


        jButton_IO.addActionListener(e -> {
            Statement statement= null;
            try {
                statement = connection.createStatement();
                ResultSet resultSet=statement.executeQuery("select *from course_design.operation_record");
                File file=new File("database_info.txt");
                PrintWriter writer=new PrintWriter(file);
                while (resultSet.next())
                    writer.println(resultSet.getString(
                            1)+"\t"+resultSet.getString(2)+"\t" +
                            resultSet.getString(3)+"\t"+resultSet.getString(4)+"\t"
                    +resultSet.getString(5)+"\t"+resultSet.getString(6));
                JOptionPane.showMessageDialog(null,"导出成功","",JOptionPane.INFORMATION_MESSAGE);
                writer.close();
                statement.close();
                resultSet.close();

            } catch (Exception ex) {
                throw new RuntimeException(ex);
            }
        });
        jButton_Back.addActionListener(e -> {
            //new windowUI().setVisible(true);//返回上一个界面
            dispose();
            try {
                connection.close();
            } catch (SQLException ex) {
                throw new RuntimeException(ex);
            }
            dispose();
        });
    }
}
