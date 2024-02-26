package com.example.proteindatabase.database;

import com.example.proteindatabase.utils.ErrorDisplay;
import com.example.proteindatabase.utils.FileHandle;

import java.io.BufferedReader;
import java.sql.*;
import java.util.ArrayList;

import java.io.IOException;
import java.util.List;

public class DatabaseManager extends Database{
    private static final String DATABASE_URL = "jdbc:sqlite:ProteinDatabase.sqlite";

    private Connection connection;

    public DatabaseManager()
    {
        try
        {
            connection = DriverManager.getConnection(DATABASE_URL);
        }
        catch (SQLException e)
        {
            e.printStackTrace();
            ErrorDisplay.displayFileFormatError("数据库连接错误", null, "数据库连接错误，请检查数据库文件是否出现问题");
        }
    }

    public void closeConnection()
    {
        try
        {
            if (connection != null && !connection.isClosed())
            {
                connection.close();
            }
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
    }
//
    @Override
    public void CreateTable(String TableName, String[] ColumnNames)
    {
        try
        {
            if (connection.isClosed()) connection = DriverManager.getConnection(DATABASE_URL);
            String tablename = "'" + TableName + "'";
            StringBuilder createTableQuery = new StringBuilder("CREATE TABLE " + tablename + " (");

            for (String columnName : ColumnNames)
            {
                createTableQuery.append("`").append(columnName).append("` TEXT, ");
            }

            createTableQuery.delete(createTableQuery.length() - 2, createTableQuery.length()); // 移除最后的逗号和空格
            createTableQuery.append(")");

            try
            {
                connection.createStatement().executeUpdate(createTableQuery.toString());
                System.out.println("Table created successfully");
            }
            catch (SQLException e)
            {
                e.printStackTrace();
                System.out.println("Error creating table: " + e.getMessage());
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        } finally {
            closeConnection();
       }
    }

    @Override
    public boolean tableExists(String TableName) throws SQLException
    {
        try {
            if (connection.isClosed()) connection = DriverManager.getConnection(DATABASE_URL);
            return connection.getMetaData().getTables(null, null, TableName, null).next();
        }
        finally {
            closeConnection();
        }
    }

    @Override
    public void InsertData(String TableName, String[] ColumnNames, BufferedReader reader) throws SQLException, IOException
    {
        try
        {
            if (connection.isClosed()) connection = DriverManager.getConnection(DATABASE_URL);
            String insertQuery = "INSERT INTO " + TableName + " VALUES (" + FileHandle.getInsertValuesPlaceholder(ColumnNames.length) + ")";

            PreparedStatement preparedStatement = connection.prepareStatement(insertQuery);

            reader.readLine();
            while (true)
            {
                String line = reader.readLine();
                if (line == null)
                {
                    break;
                }

                String[] values = line.split("\t");
                for (int i = 0; i < ColumnNames.length; i++)
                {
                    if (i >= values.length) preparedStatement.setString(i+1, "");
                    else preparedStatement.setString(i + 1, values[i]);
                }
                preparedStatement.executeUpdate();
            }
            preparedStatement.close();
        }
        finally {
            closeConnection();
        }
    }

    public boolean DataExists(String values) throws SQLException
    {
        try
        {
            String query = "SELECT EXISTS(SELECT * FROM localproteindatabase WHERE Protein_ID = '" + values + "')";
            PreparedStatement preparedStatement = connection.prepareStatement(query);
            return preparedStatement.executeQuery().getBoolean(1);
        }
        finally {
            closeConnection();
        }
    }

    public void InsertData(String Protein_ID, String Protein_Name, String Protein_EntryName, String Protein_Length, String Protein_Mass, String Gene_Names) throws SQLException
    {
        if (connection.isClosed()) connection = DriverManager.getConnection(DATABASE_URL);
        String insertQuery = "INSERT INTO localproteindatabase VALUES (?, ?, ?, ?, ?, ?)";
        PreparedStatement preparedStatement = connection.prepareStatement(insertQuery);
        preparedStatement.setString(1, Protein_ID);
        preparedStatement.setString(2, Protein_Name);
        preparedStatement.setString(3, Protein_EntryName);
        preparedStatement.setString(4, Protein_Length);
        preparedStatement.setString(5, Protein_Mass);
        preparedStatement.setString(6, Gene_Names);
        preparedStatement.executeUpdate();
        preparedStatement.close();
    }

    @Override
    public ResultSet SearchData(String SearchValues, String SearchColumn, String TableName) throws SQLException
    {
        String column = "\"" + SearchColumn + "\"";
        if (SearchColumn.equals("Protein_ID") || SearchColumn.equals("Protein_Length") || SearchColumn.equals("Protein_Mass"))
        {
            String query = "SELECT * FROM " + TableName + " WHERE " + column + " = '" + SearchValues + "'";
            PreparedStatement statement = connection.prepareStatement(query);
            return statement.executeQuery();
        }
        String query = "SELECT * FROM " + TableName + " WHERE " + column + " LIKE '%" + SearchValues + "%'";
        PreparedStatement statement = connection.prepareStatement(query);
        return statement.executeQuery();
    }


    public ResultSet InitialData() throws SQLException
    {
        String query = "SELECT * FROM  localproteindatabase";
        PreparedStatement statement = connection.prepareStatement(query);
        return statement.executeQuery();
    }


    public int getTotalItems(String SearchValues, String SearchColumn, String TableName) throws Exception
    {
        try
        {
            String column = "\"" + SearchColumn + "\"";
            if (SearchColumn.equals("Protein_ID") || SearchColumn.equals("Protein_Length") || SearchColumn.equals("Protein_Mass") || SearchColumn.equals("index") || SearchColumn.equals("Length") || SearchColumn.equals("Mass") || SearchColumn.equals("orgs"))
            {
                ResultSet resultSet = connection.prepareStatement("SELECT COUNT(*) FROM " + TableName + " WHERE " + column + " = '" + SearchValues + "'").executeQuery();
                return resultSet.getInt("COUNT(*)");
            }
            ResultSet resultSet = connection.prepareStatement("SELECT COUNT(*) FROM " + TableName + " WHERE " + column + " LIKE '%" + SearchValues + "%'").executeQuery();
            return resultSet.getInt("COUNT(*)");
        }
        finally {
            closeConnection();
        }
    }

    public String[] getColumnNames(String TableName) throws SQLException
    {
        try
        {
            String query = "SELECT * FROM " + TableName;
            PreparedStatement statement = connection.prepareStatement(query);
            ResultSet resultSet = statement.executeQuery();
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            String[] columnNames = new String[columnCount];
            for (int i = 0; i < columnCount; i++)
            {
                columnNames[i] = metaData.getColumnName(i + 1);
            }
            return columnNames;
        }
        finally {
            closeConnection();
        }
    }

    public String[] getTableNames()
    {
        List<String> tableNames = new ArrayList<>();
        try
        {
            DatabaseMetaData metaData = connection.getMetaData();
            ResultSet resultSet = metaData.getTables(null, null, "%", new String[]{"TABLE"});

            while (resultSet.next())
            {
                String tableName = resultSet.getString("TABLE_NAME");
                tableNames.add(tableName);
            }

            resultSet.close();
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
        finally {
            closeConnection();
        }
        return tableNames.toArray(new String[0]);
    }

    public int getTotalItems() throws Exception
    {
        try
        {
            ResultSet resultSet = connection.prepareStatement("SELECT COUNT(*) FROM  localproteindatabase").executeQuery();
            return resultSet.getInt("COUNT(*)");
        }
        finally {
            closeConnection();
        }
    }
}
