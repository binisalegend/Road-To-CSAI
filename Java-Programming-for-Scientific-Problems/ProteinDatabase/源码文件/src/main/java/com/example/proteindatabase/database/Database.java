package com.example.proteindatabase.database;

import java.io.IOException;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.io.BufferedReader;

public abstract class Database {
    public abstract void CreateTable(String tableName, String[] columnNames) throws SQLException;
    public abstract boolean tableExists(String tableName) throws SQLException;
    public abstract void InsertData(String tableName, String[] columnNames, BufferedReader reader) throws SQLException, IOException;
    public abstract ResultSet SearchData(String searchValues, String SearchColumn, String TableName) throws SQLException;
}
