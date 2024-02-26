import java.util.Scanner;

public class Lesson3Question2 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.close();

        int Z = 0;
        double k_max = Math.floor(Math.log(n) / Math.log(5));
        for (int i = 1; i <= k_max; i++)
        {
            Z += Math.floor(n / Math.pow(5, i));
        }
        System.out.println(Z);
    }
}
