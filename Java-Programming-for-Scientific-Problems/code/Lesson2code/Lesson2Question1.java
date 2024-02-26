import java.text.DecimalFormat;
import java.util.Scanner;

public class Lesson2Question1 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        double x = scanner.nextDouble();
        double n = scanner.nextDouble();
        scanner.close();

        DecimalFormat df = new DecimalFormat("0.00");
        double result = Calculate(x, n);
        
        System.out.println(df.format(result)); 
    }

    public static double Calculate(double x, double n)
    {
        if (n == 1)
        {
            return x / (1+x);
        }
        
        double loc = x / (1+x);
        for (int i = 2; i <= n; i++)
        {
            loc = x / (i + loc);
        }
        return loc;
    }
}