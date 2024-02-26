package com.example.proteindatabase.controllers;

import com.example.proteindatabase.database.DataTransformer;
import com.example.proteindatabase.utils.FileHandle;
import com.example.proteindatabase.utils.SearchResultHandle;
import javafx.beans.binding.Bindings;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;

import java.net.URL;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Arrays;
import java.util.ResourceBundle;


public class DataSearchController implements Initializable {
    private final DataTransformer dataController = new DataTransformer();

    public Button ResultDownload;
    @FXML
    public Button SearchButton;
    @FXML
    public ChoiceBox<String> SelectDatabase;

    @FXML
    public Button refreshButton;

    @FXML
    public TextField PageSelectTextField;

    @FXML
    public Button PageJumpButton;

    @FXML
    public Label PageSelectNotification;

    @FXML
    private TextField PagesFromTextField;

    @FXML
    private TextField PagesToTextField;

    @FXML
    private ChoiceBox<Integer> ViewPages;

    @FXML
    private TextField SearchTextField;

    @FXML
    private Label SearchResultNotification;

    @FXML
    private Pagination SearchResult;

    @FXML
    private ChoiceBox<String> SearchColumn;

    public static String[] ColumnName;

    private void setColumnName() throws SQLException {
        ColumnName = FileHandle.getLocalColumnNames(SelectDatabase.getValue());
    }

    @Override
    public void initialize(URL location, ResourceBundle resources)
    {
        try {
            totalItems = SearchResultHandle.getTotalItems();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        SearchResultHandle searchResultHandle = new SearchResultHandle();
        Integer[] PageNumber = {10, 25, 50, 100, 200};
        ObservableList<String> ColumnList;
        try {
            ColumnList = FXCollections.observableArrayList(FileHandle.getLocalColumnNames("localproteindatabase"));
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        // 监听 SelectDatabase 值的变化，并在变化时更新 ColumnName
        SelectDatabase.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            try {
                setColumnName();
                searchResultHandle.setColumnNames(ColumnName);
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        });

        SelectDatabase.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                try {
                    updateSearchColumn(newValue);
                    setInitialPages();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        });

        refreshButton.setOnAction(event -> {
            try {
                refreshDatabaseOptions();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        });

        ViewPages.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                try {
                    onSearchButtonClick(); // 触发搜索以更新页数
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

        ObservableList<String> TableList = FXCollections.observableArrayList(FileHandle.getTableNames());
        ObservableList<Integer> PageList = FXCollections.observableArrayList(PageNumber);

        SelectDatabase.setItems(TableList);
        SelectDatabase.setValue("localproteindatabase");
        try {
            setColumnName();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        SearchColumn.setItems(ColumnList);
        SearchColumn.setValue(ColumnName[2]);
        ViewPages.setItems(PageList);
        ViewPages.setValue(100);
        setInitialPages();


        // Temporarily unbind the pageCount
        SearchResult.pageCountProperty().unbind();

        // Set the new pageCount
        try {
            SearchResult.setPageCount(getPageCount());
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

        // Rebind the pageCount after setting the new count
        SearchResult.pageCountProperty().bind(Bindings.createIntegerBinding(this::getPageCount, SearchResult.currentPageIndexProperty(), ViewPages.valueProperty()));

        PageJumpButton.setOnAction(event -> {
            try
            {
                int pageNumber = Integer.parseInt(PageSelectTextField.getText());
                if (pageNumber >= 1 && pageNumber <= SearchResult.getPageCount()) {
                    SearchResult.setCurrentPageIndex(pageNumber - 1); // 跳转到用户输入的页数（从0开始）
                    PageSelectNotification.setVisible(false);
                } else {
                    // 处理页数超出范围的情况，可以给出提示信息
                    PageSelectNotification.setText("请输入正确的页码");
                    PageSelectNotification.setVisible(true);
                }
            }
            catch (NumberFormatException e)
            {
                PageSelectNotification.setText("请输入正确的页码");
                PageSelectNotification.setVisible(true);
            }
        });
    }

    private void updateSearchColumn(String selectedDatabase) throws SQLException {
        ObservableList<String> columnList = FXCollections.observableArrayList(FileHandle.getLocalColumnNames(selectedDatabase));
        SearchColumn.setItems(columnList);
        SearchColumn.setValue(columnList.get(0)); // 设置默认选择项
    }

    private void refreshDatabaseOptions() throws SQLException {
        ObservableList<String> tableList = FXCollections.observableArrayList(FileHandle.getTableNames());
        SelectDatabase.setItems(tableList);
        SelectDatabase.setValue("localproteindatabase"); // 设置默认选择项
    }

    private void setInitialPages()
    {
        if (ColumnName == null) return;
        SearchResult.setPageFactory((Integer PageIndex) -> {
            try
            {
                return SearchResultHandle.CreateInitialPage(PageIndex, dataController.GetAllData(), ViewPages.getValue(), SearchResultHandle.getTotalItems());
            }
            catch (Exception e)
            {
                throw new RuntimeException(e);
            }
        });
        try {
            int TotalItems = SearchResultHandle.getTotalItems();
            SearchResultNotification.setText("数据库内共有" + TotalItems + "条数据");
            SearchResultNotification.setVisible(true);
        }
        catch (Exception e)
        {
            throw new RuntimeException(e);
        }
    }

    private int totalItems;
    boolean flag = false;

    public void onSearchButtonClick() throws Exception
    {
        String SearchValue = SearchTextField.getText();
        String Column = SearchColumn.getValue();

        if (SearchValue.isEmpty())
        {
            setInitialPages();
            return;
        }

        ResultSet resultSet = dataController.SearchData(SearchValue, Column, SelectDatabase.getValue());
        flag = true;

        totalItems = SearchResultHandle.getTotalItems(SearchValue, Column, SelectDatabase.getValue());

        // Temporarily unbind the pageCount
        SearchResult.pageCountProperty().unbind();

        // Set the new pageCount
        SearchResult.setPageCount(getPageCount());

        // Rebind the pageCount after setting the new count
        SearchResult.pageCountProperty().bind(Bindings.createIntegerBinding(this::getPageCount, SearchResult.currentPageIndexProperty(), ViewPages.valueProperty()));

        SearchResult.setPageFactory((Integer PageIndex) ->
        {
            try
            {

                return SearchResultHandle.CreatePage(PageIndex, resultSet, ViewPages.getValue(), totalItems, flag);
            }
            catch (SQLException e)
            {
                throw new RuntimeException(e);
            }
        });
        flag = false;

        SearchResultNotification.setVisible(true);
        SearchResultNotification.setText("搜索完成，共有" + totalItems + "条结果");
    }

    public void onDownloadButtonClick() throws Exception
    {
        if (PagesFromTextField.getText().isEmpty() || PagesToTextField.getText().isEmpty())
        {
            SearchResultNotification.setText("请输入下载起始终止页码");
            SearchResultNotification.setVisible(true);
            return;
        }
        try
        {
            Integer.parseInt(PagesFromTextField.getText());
            Integer.parseInt(PagesToTextField.getText());
        }
        catch (NumberFormatException e)
        {
            SearchResultNotification.setText("请输入正确的页码");
            SearchResultNotification.setVisible(true);
            return;
        }

        if (Integer.parseInt(PagesFromTextField.getText()) > Integer.parseInt(PagesToTextField.getText()))
        {
            SearchResultNotification.setText("起始页码不能大于终止页码");
            SearchResultNotification.setVisible(true);
            return;
        }

        if (Integer.parseInt(PagesFromTextField.getText()) < 1 || Integer.parseInt(PagesToTextField.getText()) > getPageCount())
        {
            SearchResultNotification.setText("页码超出范围");
            SearchResultNotification.setVisible(true);
            return;
        }
        SearchResultNotification.setVisible(false);
        SearchResultHandle.DownloadFile(Integer.parseInt(PagesFromTextField.getText()), Integer.parseInt(PagesToTextField.getText()), ViewPages.getValue(), SearchTextField.getText().isEmpty());
    }

    public int getPageCount() throws Exception
    {
        if (SearchTextField != null)
        {
            if (ViewPages != null)
            {
                if (SearchColumn != null)
                {
                    return (totalItems / ViewPages.getValue()) + 1;
                }
            }
        }
        return SearchResultHandle.getTotalItems() / 100 + 1;
    }
}