import java.util.Scanner;

public class Lesson4Question5 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        String string = scanner.nextLine();
        StringBuilder sb = new StringBuilder();
        sb.append(string);
        scanner.close();

        int length = string.length();
        if (sb.charAt(length-1) >= '0' && sb.charAt(length-1) <= '9')
        {
            int i = length - 1, carrybit = 0;
            int num = sb.charAt(i) - '0' + carrybit + 1;
            while (i >= 0 && sb.charAt(i) >= '0' && sb.charAt(i) <= '9')
            {
                if (num >= 10)
                {
                    carrybit = num / 10;
                    num %= 10;
                    sb.replace(i, i+1, Integer.toString(num));
                }
                else
                {
                    sb.replace(i, i+1, Integer.toString(num));
                    carrybit = 0;
                    break;
                }
                i--;
                num = sb.charAt(i) - '0' + carrybit;
            }

            if (carrybit != 0)
            {
                sb.insert(i+1, carrybit);
            }
        }
        else
        {
            sb.append("1");
        }

        System.out.println(sb);
    }
}
