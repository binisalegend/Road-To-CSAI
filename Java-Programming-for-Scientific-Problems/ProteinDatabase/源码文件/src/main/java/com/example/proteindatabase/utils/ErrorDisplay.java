package com.example.proteindatabase.utils;

import javafx.scene.control.Alert;

public class ErrorDisplay {

    public static void displayFileFormatError(String title, String header, String content)
    {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle(title);
        alert.setHeaderText(header);
        alert.setContentText(content);
        alert.showAndWait();
    }
}
