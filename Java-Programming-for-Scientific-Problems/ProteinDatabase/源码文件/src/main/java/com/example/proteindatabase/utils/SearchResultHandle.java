package com.example.proteindatabase.utils;

import java.io.File;
import java.io.IOException;
import java.sql.ResultSet;

import com.example.proteindatabase.database.DatabaseManager;
import com.example.proteindatabase.models.DownloadCompleteNotification;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.stage.FileChooser;

import java.sql.SQLException;
import java.util.List;
import java.io.BufferedWriter;
import java.io.FileWriter;

public class SearchResultHandle {
    public static int getTotalItems(String SearchValue, String SearchColumn, String TableName) throws Exception {
        DatabaseManager databaseManager = new DatabaseManager();
        return databaseManager.getTotalItems(SearchValue, SearchColumn, TableName);
    }

    public static int getTotalItems() throws Exception
    {
        DatabaseManager databaseManager = new DatabaseManager();
        return databaseManager.getTotalItems();
    }

    static String[] ColumnNames;

    public void setColumnNames(String[] ColumnNames)
    {
        SearchResultHandle.ColumnNames = ColumnNames;
    }

    protected static ObservableList<String> data = FXCollections.observableArrayList();
    protected static ObservableList<String> InitialData = FXCollections.observableArrayList();

    private static int getData(ResultSet resultSet) throws SQLException
    {
        int columncount = resultSet.getMetaData().getColumnCount();
        int count = 0;
        while (resultSet.next())
        {
            StringBuilder rowData = new StringBuilder();
            for (int i = 1; i <= columncount;i++)
            {
                String columnValue = resultSet.getString(i);
                rowData.append(columnValue != null ? columnValue : "").append("\t");
            }
            count++;
            data.add(rowData.toString());
        }
        return count;
    }

    private static void getInitialData(ResultSet resultSet) throws SQLException
    {
        int columncount = resultSet.getMetaData().getColumnCount();
        while (resultSet.next())
        {
            StringBuilder rowData = new StringBuilder();
            for (int i = 1; i <= columncount; i++)
            {
                String columnValue = resultSet.getString(i);
                rowData.append(columnValue != null ? columnValue : "").append("\t");
            }
            InitialData.add(rowData.toString());
        }
    }

    private static void setColumnNames(TableView<String> tableView)
    {
        for (int i = 0; i < ColumnNames.length; i++)
        {
            TableColumn<String, String> column = new TableColumn<>(ColumnNames[i]);
            final int index = i;
            column.setCellValueFactory(data -> {
                String value = data.getValue();
                if (value != null)
                {
                    String[] rowData = value.split("\t");
                    return new SimpleStringProperty(index < rowData.length ? rowData[index] : "");
                }
                else
                {
                    return new SimpleStringProperty("");
                }
            });
            tableView.getColumns().add(column);
        }
    }

    public static TableView<String> CreateInitialPage(int pageIndex, ResultSet resultSet, int rowsPerPage, int total) throws Exception
    {
        if (total == 0) return null;
        TableView<String> tableView = new TableView<>();

        setColumnNames(tableView);
        getInitialData(resultSet);

        // Calculate start and end row index
        int startRow = Math.min(pageIndex * rowsPerPage, total);
        int endRow = Math.min(startRow + rowsPerPage, total);

        // Clear items and add rows to TableView
        tableView.getItems().clear();
        List<String> page = InitialData.subList(startRow, endRow);
        ObservableList<String> Page = FXCollections.observableArrayList(page);
        tableView.setItems(Page);

        return tableView;
    }

    public static TableView<String> CreatePage(int pageIndex, ResultSet resultSet, int rowsPerPage, int total, boolean flag) throws SQLException
    {
        if (total == 0) return null;
        TableView<String> tableView = new TableView<>();

        setColumnNames(tableView);
        if (flag)
        {
            if (!data.isEmpty()) data.clear();
            int count = getData(resultSet);
            if (count == 0) return null;
        }

        // Calculate start and end row index
        int startRow = Math.min(pageIndex * rowsPerPage, total);
        int endRow = Math.min(startRow + rowsPerPage, total);

        // Clear items and add rows to TableView
        tableView.getItems().clear();
        List<String> page = data.subList(startRow, endRow);
        ObservableList<String> Page = FXCollections.observableArrayList(page);
        tableView.setItems(Page);

        return tableView;
    }

    public static void DownloadFile(Integer from, Integer to, int PAGE_SIZE, boolean isEmpty) throws IOException
    {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("保存文件");
        fileChooser.setInitialFileName("SearchResult");
        fileChooser.getExtensionFilters().addAll(new FileChooser.ExtensionFilter("TSV", "*.tsv"), new FileChooser.ExtensionFilter("CSV", "*.csv"));
        File file = fileChooser.showSaveDialog(null);

        ObservableList<String> Data;
        if (isEmpty) Data = InitialData;
        else Data = data;

        if (file != null)
        {
            BufferedWriter writer = new BufferedWriter(new FileWriter(file));

            int startRow = Math.min((from - 1) * PAGE_SIZE, Data.size());
            int endRow = Math.min(to * PAGE_SIZE, Data.size());

            boolean isTSV = file.getAbsolutePath().endsWith(".tsv");

            // Write column headers
            for (int i = 0; i < ColumnNames.length; i++)
            {
                if (i > 0)
                {
                    writer.write(isTSV ? "\t" : ",");
                }
                writer.write(ColumnNames[i]);
            }
            writer.newLine();

            // Write data rows
            for (int i = startRow; i < endRow; i++)
            {
                String[] rowData = Data.get(i).split("\t");
                System.out.println(rowData[0] + ":" + rowData.length);

                for (int j = 0; j < ColumnNames.length; j++)
                {
                    if (j > 0)
                    {
                        writer.write(isTSV ? "\t" : ",");
                    }
                    if (j == ColumnNames.length - 1 && rowData.length == ColumnNames.length - 1) writer.write("");
                    else writer.write(rowData[j]);
                }
                writer.newLine();
            }

            DownloadCompleteNotification.showNotification();
            writer.close();
        }
    }
}