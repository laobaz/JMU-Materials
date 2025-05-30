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
        jButton_backup=new JButton("�������ݿ�");
        jButton_restore=new JButton("��ԭ���ݿ�(����bug)");
        jButton_back=new JButton("������һ��");
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
                    JOptionPane.showMessageDialog(null,"����ʧ��","����",JOptionPane.WARNING_MESSAGE);
                }else {
                    JOptionPane.showMessageDialog(null,"���ݳɹ�","��ϲ",JOptionPane.INFORMATION_MESSAGE);
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
                        JOptionPane.showMessageDialog(null,"��ԭʧ��","����",JOptionPane.WARNING_MESSAGE);
                    }else {
                        JOptionPane.showMessageDialog(null,"��ԭ�ɹ�","��ϲ",JOptionPane.INFORMATION_MESSAGE);
                    }


            } catch (IOException ex) {
                System.out.println(ex);
            } catch (InterruptedException ex) {
                throw new RuntimeException(ex);
            }

        });
        jButton_back.addActionListener(e -> {
            new windowUI().setVisible(true);//������һ������
            dispose();
        });

    }

}
