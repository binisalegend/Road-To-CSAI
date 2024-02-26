import java.util.Scanner;

public class Lesson3Question4 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        String FunctionClass = scanner.next();
        long[] InputArray = new long[1000000];

        int t = 0;
        scanner.nextLine();
        String[] inputLine = scanner.nextLine().split(" ");
        for (String numStr : inputLine) {
            if (!numStr.equals("")) {
                long loc = Long.parseLong(numStr);
                InputArray[t++] = loc;
            }
        }
        long init = scanner.nextLong();
        scanner.close();

        long[] result = operArray(FunctionClass, InputArray, init, t);
        for (int i = 0; i < t-1; i++)
        {
            System.out.print(result[i] + " ");
        }
        System.out.println(result[t-1]);
    }

    public static long[] operArray(String fct, long arr[], long init, int len)
    {
        long[] OutArray = new long[len];
        Lesson3Question4 main = new Lesson3Question4();

        switch (fct) {
            case "som":
                for (int i = 0; i < len; i++) {
                    OutArray[i] = main.som(init, arr[i]);
                    init = OutArray[i];
                }
                break;
            case "mini":
                for (int i = 0; i < len; i++) {
                    OutArray[i] = main.mini(init, arr[i]);
                    init = OutArray[i];
                }
                break;
            case "maxi":
                for (int i = 0; i < len; i++) {
                    OutArray[i] = main.maxi(init, arr[i]);
                    init = OutArray[i];
                }
                break;
            case "lcmu":
                for (int i = 0; i < len; i++) {
                    OutArray[i] = main.lcmu(Math.abs(init), Math.abs(arr[i]));
                    init = OutArray[i];
                }
                break;
            case "gcdi":
                for (int i = 0; i < len; i++) {
                    OutArray[i] = main.gcdi(Math.abs(init), Math.abs(arr[i]));
                    init = OutArray[i];
                }
                break;
        }
        return OutArray;
    }

    public long som(long x, long y)
    {
        return x + y;
    }

    public long mini(long x, long y)
    {
        return x > y ? y : x;
    }

    public long maxi(long x, long y)
    {
        return x > y ? x : y;
    }

    public long lcmu(long x, long y)
    {
        long HelpNum = CalculateMethod(x, y);
        if (HelpNum == 0)
        {
            return 0;
        }
        return x * (y / HelpNum);
    }

    public long gcdi(long x, long y)
    {
        return CalculateMethod(x, y);
    }

    public long CalculateMethod(long x, long y)
    {
        long loc = 0;
        if (x < y)
        {
            loc = x;
            x = y;
            y = loc;
        }
        if (y == 0)
        {
            return 0;
        }
        if (x % y == 0)
        {
            return y;
        }
        while (x % y != 0)
        {
            loc = x % y;
            x = y;
            y = loc;
        }
        return loc;
    }
}
