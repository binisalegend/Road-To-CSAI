package com.example.proteindatabase.models;

import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class DataInsertNotofication {

    public static void showNotification() {
        Stage notificationStage = new Stage();
        VBox root = new VBox();
        Label label = new Label("数据添加成功！");
        label.setStyle("-fx-font-size: 40");
        label.setStyle("-fx-text-fill: #ff0000");

        // 设置 VBox 的属性，使其子元素在纵向上居中，并且填满整个窗口
        root.setAlignment(Pos.CENTER);
        root.setFillWidth(true);

        // 设置 Label 在 VBox 中的居中对齐
        VBox.setVgrow(label, javafx.scene.layout.Priority.ALWAYS);

        root.getChildren().add(label);

        Scene scene = new Scene(root, 299, 100);
        notificationStage.setScene(scene);
        notificationStage.setTitle("数据添加完成");
        notificationStage.show();
    }
}