package com.example.proteindatabase.utils;

import com.example.proteindatabase.database.DatabaseManager;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.sql.SQLException;
import java.util.Arrays;

public class FileHandle {

    public static String[] GetColumnNames(String str)
    {
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(str)))
        {
            return bufferedReader.readLine().split("\t");
        }
        catch (IOException e)
        {
            e.printStackTrace();
            ErrorDisplay.displayFileFormatError("文件读取错误", null, "文件读取错误，请检查文件是否出现问题");
            return null;
        }
    }

    public static String[] getLocalColumnNames(String TableName) throws SQLException
    {
//        return new String[]{"Protein_ID", "Protein_Name", "Protein_EntryName", "Protein_Length", "Protein_Mass", "Gene Names (primary)"};
        DatabaseManager databaseManager = new DatabaseManager();
        return databaseManager.getColumnNames(TableName);
    }

    public static String[] getTableNames()
    {
        DatabaseManager databaseManager = new DatabaseManager();
        return databaseManager.getTableNames();
    }

    public static String getInsertValuesPlaceholder(int columnCount)
    {
        String[] placeholders = new String[columnCount];
        Arrays.fill(placeholders, "?");
        for (String placeholder : placeholders) {
            System.out.println(placeholder);
        }
        return String.join(", ", placeholders);
    }

    public static BufferedReader getBufferedReader(String filePath)
    {
        try
        {
            return new BufferedReader(new FileReader(filePath));
        }
        catch (IOException e)
        {
            e.printStackTrace();
            ErrorDisplay.displayFileFormatError("错误", null, "无法打开文件：");
            return null;
        }
    }
}
