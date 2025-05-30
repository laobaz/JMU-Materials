package keshe.template;

import javax.swing.*;
import java.sql.*;
import java.util.ArrayList;

public class Output_list {
    keshe.template.connection c = new connection();
    Connection connection = c.getConnect();

    CallableStatement stmt;
    boolean hasResult;
    ResultSet rs;
    ResultSetMetaData meta;
    int count = 0;
    public String arr[];
    public String table[][];
    JTable jTable;

    public JTable Output(String sql) {


        try {//将当前所有的内容读入到窗口中
            stmt = connection.prepareCall(sql);
            stmt.execute();
            rs = stmt.getResultSet();
            int row=0;
            while(rs.next()){
                row++;
            }
            stmt.close();
            rs.close();
            stmt = connection.prepareCall(sql);
            hasResult = stmt.execute();
            while (hasResult) {
                rs = stmt.getResultSet();
                meta = rs.getMetaData();
                int columns = meta.getColumnCount();
                arr = new String[columns];

                table = new String[row][columns];
                for (int i = 0; i < columns; i++) {
                    arr[i] = meta.getColumnName(i + 1);
                }

                int j = 0;
                while (rs.next()) {
                    for (int i = 0; i < columns; i++) {
                        table[j][i] = rs.getString(i + 1);
                    }
                    j++;
                }
                hasResult = stmt.getMoreResults();
            }
            jTable = new JTable(table, arr);
            rs.close();
            stmt.close();
            //connection.close();

        } catch (Exception ex) {
            System.out.println(ex);
        }
        return jTable;
    }


}

