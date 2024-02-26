package com.example.proteindatabase.controllers;

import com.example.proteindatabase.database.DatabaseManager;
import com.example.proteindatabase.models.DataInsertNotofication;
import com.example.proteindatabase.utils.StringUtil;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;

import java.sql.SQLException;

public class DataInsertController {

    @FXML
    public TextField Protein_ID;

    @FXML
    public TextField Protein_Name;

    @FXML
    public TextField Protein_EntryName;

    @FXML
    public TextField Protein_Length;

    @FXML
    public TextField Protein_Mass;

    @FXML
    public TextField Gene_Names;

    @FXML
    public Label Notification;

    @FXML
    public Button AddButton;

    public void onAddButtonClick() throws SQLException {
        String protein_ID = Protein_ID.getText();
        String protein_Name = Protein_Name.getText();
        String protein_EntryName = Protein_EntryName.getText();
        String protein_Length = Protein_Length.getText();
        String protein_Mass = Protein_Mass.getText();
        String gene_Names = Gene_Names.getText();

        if (StringUtil.isEmpty(protein_ID))
        {
            Notification.setText("请输入蛋白质ID");
            Notification.setVisible(true);
            return;
        }

        if (StringUtil.isEmpty(protein_Name))
        {
            Notification.setText("请输入蛋白质名称");
            Notification.setVisible(true);
            return;
        }

        if (StringUtil.isEmpty(protein_EntryName))
        {
            Notification.setText("请输入蛋白质搜索模糊名称");
            Notification.setVisible(true);
            return;
        }

        if (StringUtil.isEmpty(protein_Length))
        {
            Notification.setText("请输入蛋白质长度");
            Notification.setVisible(true);
            return;
        }

        if (StringUtil.isEmpty(protein_Mass))
        {
            Notification.setText("请输入蛋白质质量");
            Notification.setVisible(true);
            return;
        }

        DatabaseManager databaseManager = new DatabaseManager();
        if (databaseManager.DataExists(protein_ID))
        {
            Notification.setText("该蛋白质已存在，请输入新的蛋白质ID");
            Notification.setVisible(true);
        }
        else
        {
            databaseManager.InsertData(protein_ID, protein_Name, protein_EntryName, protein_Length, protein_Mass, gene_Names);
            Notification.setVisible(false);
            DataInsertNotofication.showNotification();
        }
    }
}
