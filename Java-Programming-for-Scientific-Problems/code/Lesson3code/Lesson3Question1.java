import java.util.Scanner;

public class Lesson3Question1 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        int len1 = scanner.nextInt();
        
        long num1[] = new long[205];

        int t = 1;
        scanner.nextLine();
        String[] inputLine = scanner.nextLine().split(" ");
        for (String numStr : inputLine) {
            if (!numStr.equals("")) {
                long loc = Long.parseLong(numStr);
                if (loc != 0) {
                    num1[t++] = loc;
                }
            }
        }

        int len2 = scanner.nextInt();
        long num2[] = new long[len2+2];
        for (int i = 1; i <= len2; i++)
        {
            num2[i] = scanner.nextLong();
        }
        scanner.close();

        long result[] = new long[len1 + len2 + 2];
        int p = 1, q = 1, r = 1;
        while (p <= len1 && q <= len2)
        {
            if (num1[p] < num2[q])
            {
                result[r++] = num1[p++];
            }
            else
            {
                result[r++] = num2[q++];
            }
        }
        while (p <= len1)
        {
            result[r++] = num1[p++];
        }
        while (q <= len2)
        {
            result[r++] = num2[q++];
        }
        
        for (int i = 1; i < len1 + len2; i++)
        {
            System.out.print(result[i] + " ");
        }

        System.out.println(result[len1+len2]);
    }
}
