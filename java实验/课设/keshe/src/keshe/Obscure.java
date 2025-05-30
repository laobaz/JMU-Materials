package keshe;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import java.awt.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;


public class Obscure extends JFrame {   //ģ������
    JTextField jTextField=new JTextField(10);
    connection c=new connection();
    Connection connection=c.getConnect();
    JTable jTable=null;
    JButton jButton_Obscures, jButton_back;
    JLabel jLabel=new JLabel("֧��ģ����ѯѡ��");
    JComboBox<String>jComboBox=new JComboBox<>();
    Obscure() {
        setTitle("ģ������");
        setVisible(true);
        init();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    private void init() {
        this.setResizable(false);
        jComboBox.addItem("��¼��");
        jComboBox.addItem("֧����Ŀ");
        this.setSize(700,500 );//���ý���
        Dimension screen = this.getToolkit().getScreenSize();
        this.setLocation((screen.width - this.getSize().width) / 2,
                (screen.height - this.getSize().height) / 2);
        jButton_Obscures = new JButton("����");
        jButton_back = new JButton("������һ��");
        JPanel pnorth = new JPanel();
        pnorth.setLayout(new FlowLayout());
        pnorth.add(jTextField);
        pnorth.add(jButton_Obscures);
        pnorth.add(jButton_back);
        pnorth.add(jComboBox);
        pnorth.add(jLabel);
        add(pnorth, BorderLayout.NORTH);
        String arr[]={"��¼��","֧����Ŀ","�۸�","����","���","��ע","����"};//
        String tables[][]=new String[0][0];//��ʼ��tablesΪnull
        jTable=new JTable(tables,arr);//����һ��ֻ��arr[]���ݵ�table
        jTable.setPreferredScrollableViewportSize(new Dimension(700,300));
        add(new JScrollPane(jTable),BorderLayout.SOUTH);
        jButton_Obscures.addActionListener(e -> {
            try{
                ResultSet rs;
                PreparedStatement ps = null;
                String ob =jTextField.getText();
                String sql = "select * from bills where expend like '%"+ob+"%'";
                String sql1="select * from bills where Mark like '%"+ob+"%'";//ģ����ѯ���ڵ�����
                String choice=jComboBox.getSelectedItem().toString();
                if(choice.equals("��¼��"))
                {
                    ps=connection.prepareStatement(sql1,ResultSet.TYPE_SCROLL_INSENSITIVE,
                            ResultSet.CONCUR_READ_ONLY);
                }
                else if(choice.equals("֧����Ŀ")) {
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
                            "û�в�ѯ�������Ϣ", "��Ǹ", JOptionPane.PLAIN_MESSAGE);//������������ʾ

                TableModel tableModel=new DefaultTableModel(table,arr);//����tableModel����ʵʱˢ��JTable
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


