package com.example.proteindatabase.controllers;

import com.example.proteindatabase.database.DatabaseManager;
import com.example.proteindatabase.models.TableCreatedNotification;
import com.example.proteindatabase.utils.ErrorDisplay;
import com.example.proteindatabase.utils.FileHandle;
import com.example.proteindatabase.utils.StringUtil;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;
import java.sql.SQLException;
import java.util.Objects;

public class DataImportController {

    public Button FileChooseButton;

    @FXML
    public Button AddDataButton;

    @FXML
    private TextField FilePathTextField;

    @FXML
    private TextField LabelNameTextField;

    @FXML
    private Label ErrorInfo;

    public void onImportButtonClick() throws SQLException, IOException
    {
        String filePath = FilePathTextField.getText();
        String labelName = LabelNameTextField.getText();

        if (StringUtil.isEmpty(filePath))
        {
            ErrorInfo.setText("请输入文件的路径或选择文件");
            ErrorInfo.setVisible(true);
            return;
        }

        if (StringUtil.isEmpty(labelName))
        {
            ErrorInfo.setText("请输入新建存储数据表名称");
            ErrorInfo.setVisible(true);
            return;
        }

        DatabaseManager databaseManager = new DatabaseManager();
        if (databaseManager.tableExists(labelName))
        {
            ErrorInfo.setText("该表已存在，请输入新的表名");
            ErrorInfo.setVisible(true);
        }
        else
        {
            String[] columnNames = FileHandle.GetColumnNames(filePath);
            if (columnNames != null) {
                System.out.println("columnnames " + columnNames[columnNames.length-1]);
                databaseManager.CreateTable(labelName, columnNames);
                databaseManager.InsertData(labelName, columnNames, Objects.requireNonNull(FileHandle.getBufferedReader(filePath)));
                TableCreatedNotification.showNotification();
            }
        }
    }

    public void onFileChooseButtonClick() {
        FileChooser fileChooser = new FileChooser();

        fileChooser.setTitle("选择文件");

        Stage stage = (Stage) FilePathTextField.getScene().getWindow();
        File file = fileChooser.showOpenDialog(stage);

        if (file != null && !file.getName().toLowerCase().endsWith(".tsv"))
        {
            ErrorDisplay.displayFileFormatError("文件格式错误", null, "请选择 TSV 格式的文件");
        }
        else
        {
            if (file != null) {
                FilePathTextField.setText(file.getAbsolutePath());
            }
        }
    }

    public void onAddDataButtonClick()
    {
        try {
            // 加载新的 FXML 文件和对应的 Controller
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/com/example/proteindatabase/fxml/DataInsert.fxml"));
            Parent root = loader.load();

            // 创建新的场景和舞台
            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("添加数据");

            // 显示新窗口
            stage.show();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
