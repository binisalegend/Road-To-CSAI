module com.example.proteindatabase {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;

    exports com.example.proteindatabase;
    exports com.example.proteindatabase.models;
    exports com.example.proteindatabase.controllers;
    exports com.example.proteindatabase.utils;
    exports com.example.proteindatabase.database;

    opens com.example.proteindatabase to javafx.fxml;
    opens com.example.proteindatabase.controllers to javafx.fxml;
    opens com.example.proteindatabase.models to javafx.fxml;
    opens com.example.proteindatabase.utils to javafx.fxml;
    opens com.example.proteindatabase.database to javafx.fxml;
}