// import javax.swing.JOptionPane;

public class Doglauncher {
    public static void main(String[] args)
    {
        Dog d = new Dog(51);
        // d.WeightPounds = 25;
        Dog d2 = new Dog(100);

        // Dog bigger = Dog.maxDog(d, d2);
        Dog bigger = d.maxDog(d2);

        bigger.makenoise();
        // JOptionPane.showMessageDialog(null, "Welcome to Java Programming!");
        // System.exit(0);
    }
}
