package keshe.Backup_and_restorepackage;

import keshe.template.Default_template;
import keshe.windowUI;

import javax.swing.*;
import java.awt.*;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;

public class Backup_and_restore extends JFrame {
    //keshe.template.connection c = new connection();
    //Connection connection = c.getConnect();
    JButton jButton_backup, jButton_restore,jButton_back;

    public Backup_and_restore(){
        new Default_template(this);
        setSize(700, 200);
        init();
    }
    void init()  {
        jButton_backup=new JButton("备份数据库");
        jButton_restore=new JButton("还原数据库(存在bug)");
        jButton_back=new JButton("返回上一级");
        JPanel jPanel=new JPanel();
        jPanel.add(jButton_backup);
        jPanel.add(jButton_restore);
        jPanel.add(jButton_back);
        add(jPanel, BorderLayout.NORTH);

        jButton_backup.addActionListener(e -> {
            Runtime rt = Runtime.getRuntime();
            //String time = new SimpleDateFormat("yyyyMMdd").format(new Date()).toString();
            File file=new File("course_design"+"sql");
            try {
                Process pro = rt.exec
                        ("mysqldump -uroot -p123456..  -rcourse_design.sql course_design");
                BufferedReader br = new BufferedReader(new InputStreamReader(pro.getErrorStream()));
                String errorLine = null;
                while ((errorLine = br.readLine()) != null) {
                    System.out.println(errorLine);
                }
                int result = 0;
                result = pro.waitFor();
                if (result != 0) {
                    JOptionPane.showMessageDialog(null,"备份失败","警告",JOptionPane.WARNING_MESSAGE);
                }else {
                    JOptionPane.showMessageDialog(null,"备份成功","恭喜",JOptionPane.INFORMATION_MESSAGE);
                }
                br.close();
            } catch (IOException ex) {
                System.out.println(ex);
            } catch (InterruptedException ex) {
                throw new RuntimeException(ex);
            }
        });
        jButton_restore.addActionListener(e -> {
            Runtime rt = Runtime.getRuntime();
            try {

                Process pro=rt.exec("mysql -uroot -p123456.. course_design < course_design.sql");
            //  BufferedReader br = new BufferedReader(new InputStreamReader(pro.getErrorStream()));
             //   String errorLine = null;
             //    while ((errorLine = br.readLine()) != null) {
               //     System.out.println(errorLine);
               // }
               // br.close();
                int result ;
                    result = pro.waitFor();
                    if (result != 0) {
                        JOptionPane.showMessageDialog(null,"还原失败","警告",JOptionPane.WARNING_MESSAGE);
                    }else {
                        JOptionPane.showMessageDialog(null,"还原成功","恭喜",JOptionPane.INFORMATION_MESSAGE);
                    }


            } catch (IOException ex) {
                System.out.println(ex);
            } catch (InterruptedException ex) {
                throw new RuntimeException(ex);
            }

        });
        jButton_back.addActionListener(e -> {
            new windowUI().setVisible(true);//返回上一个界面
            dispose();
        });

    }

}
