package com.example.proteindatabase.database;

import java.sql.ResultSet;
import java.sql.SQLException;


public class DataTransformer {
    public ResultSet SearchData(String SearchValues, String SearchColumn, String TableName) throws SQLException
    {
        DatabaseManager databaseManager = new DatabaseManager();
        return databaseManager.SearchData(SearchValues, SearchColumn, TableName);
    }

    public ResultSet GetAllData() throws SQLException
    {
        DatabaseManager databaseManager = new DatabaseManager();
        return databaseManager.InitialData();
    }
}
