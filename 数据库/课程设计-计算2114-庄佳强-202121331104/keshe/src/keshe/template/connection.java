package keshe.template;
import java.sql.*;

public class connection {
    Connection con;
    public static String user="root";
    public static String password="123456..";
    public  Connection getConnect() {//用于简化连接数据库

        try {  //加载JDBC-MySQL8.0连接器:
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            System.out.println(e);
            return null;
        }
        String uri = "jdbc:mysql://localhost:3306/course_design?";//数据库位置
        //登入到course_design数据库中，里面个个表
        try {
            con = DriverManager.getConnection(uri, user, password);
            return con;//连接
        } catch (SQLException e) {
            e.printStackTrace();
            return null;
        }


    }
}



