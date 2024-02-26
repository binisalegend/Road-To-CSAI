import java.util.Scanner;

public class Lesson2Question5 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.close();

        if (n <= 0)
        {
            System.out.println(0);
        }
        else
        {
            int sum = 0;
            for (int i = 1; i < n; i++)
            {
                if (i % 3 == 0 || i % 5 == 0)
                {
                    sum += i;
                }
            }
            System.out.println(sum);
        }
        System.exit(0);
    }
}