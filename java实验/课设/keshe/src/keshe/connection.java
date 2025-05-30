package keshe;
import java.sql.*;

public class connection {
    Connection con;
    public Connection getConnect() {//用于简化连接数据库

        try {  //加载JDBC-MySQL8.0连接器:
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            System.out.println(e);
            return null;
        }
        String uri = "jdbc:mysql://localhost:3306/course_expenditures?useSSL=false&characterEncoding=utf-8";//数据库位置
        //登入到expenditures数据库中，里面有bill支出账单和account用户账号
        String user = "root";
        String password = "123456..";
        try {
            con = DriverManager.getConnection(uri, user, password);
            return con;//连接
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }


    }
}



