/*
 * @Description: 
 * @version: 
 * @Author: binisalegend
 * @Date: 2023-10-31 15:59:59
 * @LastEditors: binisalegend
 * @LastEditTime: 2023-10-31 17:35:55
 */
import java.math.BigInteger;
import java.util.Scanner;
import java.util.regex.Pattern;
import java.util.List;
import java.util.ArrayList;

public class Lesson6Question1 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        scanner.close();

        Judging(input);
    }

    private static void Judging(String str)
    {
        Pattern pattern = Pattern.compile("^[+-]?\\d+$");
        String[] strings = str.split("[\\[\\]]");
        List<String> validNumbers = new ArrayList<>();
        for (int i = 1; i < strings.length; i += 2)
        {
            if (pattern.matcher(strings[i]).matches())
            {
                BigInteger test = new BigInteger(strings[i]);
                if ((test.mod(BigInteger.valueOf(4))).equals(BigInteger.valueOf(0)))
                {
                    validNumbers.add(strings[i]);
                }
            }
        }
        
        if (!validNumbers.isEmpty())
        {
            System.err.print(String.join(", ", validNumbers));
        }

        System.out.println();
    }
}
// 傻逼乐学用不了String.join(),换下面这个。。。
// import java.math.BigInteger;
// import java.util.ArrayList;
// import java.util.List;
// import java.util.Scanner;
// import java.util.regex.Pattern;

// public class Lesson6Question1 {
//     public static void main(String[] args) {
//         Scanner scanner = new Scanner(System.in);
//         String input = scanner.nextLine();
//         scanner.close();

//         Judging(input);
//     }

//     private static void Judging(String str) {
//         Pattern pattern = Pattern.compile("^[+-]?\\d+$");
//         String[] strings = str.split("[\\[\\]]");
//         List<String> validNumbers = new ArrayList<>();
//         boolean isFirst = true;

//         for (int i = 1; i < strings.length; i += 2) {
//             if (pattern.matcher(strings[i]).matches()) {
//                 BigInteger test = new BigInteger(strings[i]);
//                 if (test.mod(BigInteger.valueOf(4)).equals(BigInteger.valueOf(0)) && i != strings.length - 1) {
//                     if (!isFirst) {
//                         System.out.print(", ");
//                     }
//                     System.out.print(strings[i]);
//                     isFirst = false;
//                 }
//             }
//         }

//         System.out.println();
//     }
// }
