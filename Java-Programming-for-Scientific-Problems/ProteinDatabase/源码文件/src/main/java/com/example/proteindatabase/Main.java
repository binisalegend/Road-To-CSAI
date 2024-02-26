package com.example.proteindatabase;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.Objects;

public class Main extends Application {
    private static Stage stage;

    public static void main(String[] args)
    {
        launch(args);
    }

    @Override
    public void start(Stage stage)
    {
        Main.stage = stage;
        stage.setTitle("蛋白质数据管理系统");
        changeView("fxml/MainWindow.fxml");
        stage.show();
    }

    public static void changeView(String fxml)
    {
        Parent root;
        try
        {
            root = FXMLLoader.load(Objects.requireNonNull(Main.class.getResource(fxml)));
            stage.setScene(new Scene(root));
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
