package keshe;
import java.sql.*;

public class connection {
    Connection con;
    public Connection getConnect() {//���ڼ��������ݿ�

        try {  //����JDBC-MySQL8.0������:
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            System.out.println(e);
            return null;
        }
        String uri = "jdbc:mysql://localhost:3306/course_expenditures?useSSL=false&characterEncoding=utf-8";//���ݿ�λ��
        //���뵽expenditures���ݿ��У�������bill֧���˵���account�û��˺�
        String user = "root";
        String password = "123456..";
        try {
            con = DriverManager.getConnection(uri, user, password);
            return con;//����
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }


    }
}



