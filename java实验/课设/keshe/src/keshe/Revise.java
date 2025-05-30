package keshe;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableModel;
import java.awt.*;
import java.sql.*;

public class Revise extends JFrame{
    connection c=new connection();
    Connection connection=c.getConnect();
    JTextField jTextField_Choice=new JTextField(10);   //ѡ��Mark���ı���
    JTextField jTextField_Revise=new JTextField(10);   //Ҫ�޸ĵ����ݵ��ı���
    JComboBox<String>jComboBox=new JComboBox<>();
    JButton jButton_Revise,jButton_back;
    JTable jTable;
    Revise(){
        setTitle("�޸Ŀγ���Ϣ");
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
        jButton_Revise=new JButton("ȷ���޸�");
        jButton_back=new JButton("������һ��");
        Panel pnorth=new Panel();
        JLabel label=new JLabel("��������޸ļ�¼��:");
        label.setFont(new Font("����",Font.BOLD,12));
        pnorth.add(label);
        pnorth.add(new JLabel("��¼��:"));
        pnorth.add(jTextField_Choice);
        JLabel label1=new JLabel("��ѡ����Ҫ�޸ĵ���Ŀ:");
        label1.setFont(new Font("����",Font.BOLD,12));
        pnorth.add(label1);
        String[]str={" ","expend","price","Date","type","Memo","Loan"};    //ѡ��Ҫ�޸ĵ�����
        for(String s:str)
            jComboBox.addItem(s);
        pnorth.add(jComboBox);
        JLabel label2=new JLabel("��������Ҫ�޸ĵ�����:");
        label2.setFont(new Font("����",Font.BOLD,12));
        pnorth.add(label2);
        pnorth.add(jTextField_Revise);
        pnorth.add(jButton_Revise);
        pnorth.add(jButton_back);
        JLabel label3=new JLabel("expend:֧����Ŀ,price:�۸�,Date:����,type:���,Memo:��ע,Loan������");
        label3.setFont(new Font("����",Font.BOLD,12));
        pnorth.add(label3);
        add(pnorth);
        ResultSet rs;
        PreparedStatement ps;
        try {//����ǰ���е����ݶ��뵽������
            this.setTitle("�޸���Ϣ");
            String sql = "select * from bills";
            ps = connection.prepareStatement(sql, ResultSet.TYPE_SCROLL_INSENSITIVE,
                    ResultSet.CONCUR_READ_ONLY);
            rs = ps.executeQuery();
            rs.last();
            int row = rs.getRow();
            rs.first();
            String arr[] = {"��¼��", "֧����Ŀ", "�۸�", "����", "���", "��ע", "����"};//
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
            String sql_update="update bills set "+choice+" ='"+Revise+"' where Mark='"+Mark+"'";//�޸ĵ��ֶ�
            Statement st;
            try {
                st = connection.createStatement();
                int ok =st.executeUpdate(sql_update);//�޸�
                st.close();
                String sql = "select * from bills";
                ResultSet rst;
                PreparedStatement pst;
                pst = connection.prepareStatement(sql, ResultSet.TYPE_SCROLL_SENSITIVE,
                        ResultSet.CONCUR_READ_ONLY);

                //���¶�ȡһ�����ݿ������ʵ��ʵʱˢ��
                rst = pst.executeQuery();
                rst.last();
                int row = rst.getRow();
                rst.first();
                String arr[] = {"��¼��", "֧����Ŀ", "�۸�", "����", "���", "��ע", "����"};
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
                TableModel tableModel=new DefaultTableModel(table,arr);//ʵ��ʵʱˢ��
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
