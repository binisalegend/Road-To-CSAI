import java.util.Scanner;

public class Lesson4Question1 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        String str = scanner.nextLine();
        scanner.close();

        if (str.length() == 0)
        {
            System.out.println(0);
            System.exit(0);
        }

        int Depth = Vps(str);
        System.out.println(Depth);
        System.exit(0);
    }

    private static int Vps(String str)
    {
        int depth = 0, left = 0, right = 0;
        char[] StrChar = str.toCharArray();
        for (char i : StrChar)
        {
            if (i == '(')
            {
                left++;
            }
            else if (i == ')')
            {
                right++;
            }
            depth = depth > (left - right) ? depth : (left - right);
        }
        return depth;
    }
}
