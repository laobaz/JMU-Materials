package keshe.template;
import java.sql.*;

public class connection {
    Connection con;
    public static String user="root";
    public static String password="123456..";
    public  Connection getConnect() {//���ڼ��������ݿ�

        try {  //����JDBC-MySQL8.0������:
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            System.out.println(e);
            return null;
        }
        String uri = "jdbc:mysql://localhost:3306/course_design?";//���ݿ�λ��
        //���뵽course_design���ݿ��У����������
        try {
            con = DriverManager.getConnection(uri, user, password);
            return con;//����
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }


    }
}



