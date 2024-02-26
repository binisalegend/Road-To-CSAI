import java.util.Scanner;

public class Lesson3Question3 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String str1 = scanner.next();
        String str2 = scanner.next();
        scanner.close();

        String result = longestCommonSubsequence(str1, str2);
        System.out.println(result);
    }

    public static String longestCommonSubsequence(String str1, String str2) {
        int m = str1.length();
        int n = str2.length();

        int[][] dp = new int[m + 1][n + 1];

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (str1.charAt(i - 1) == str2.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        int i = m, j = n;
        StringBuilder result = new StringBuilder();
        while (i > 0 && j > 0) {
            if (str1.charAt(i - 1) == str2.charAt(j - 1)) {
                result.insert(0, str1.charAt(i - 1));
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }

        return result.toString();
    }
}
/**
一开始改了好几次的代码，从分并排序到后来问完老师按第二个的顺序输出就行
然后改了n遍，发现只能找出来第一个序列，不一定是最长的
例如 abcdefghijk jkabcdefg 就只能输出jk而不是abcdefg
于是被迫动态规划，重写（睡....)   
*/
// import java.util.Scanner;
// public class Lesson3Question3 {
//     public static void main(String[] args)
//     {
//         Scanner scanner = new Scanner(System.in);
//         String str1 = scanner.next();
//         String str2 = scanner.next();
//         char Str1[] = str1.toCharArray();
//         char Str2[] = str2.toCharArray();
//         scanner.close();

//         int i = 0, j = 0, flag = 0;
//         String result = "";
//         for (i = 0; i < str2.length(); i++)
//         {
//             if (j == str1.length())
//             {
//                 j = flag;
//             }
//             while (j < str1.length())
//             {
//                 if (Str2[i] == Str1[j])
//                 {
//                     result += Str2[i];
//                     flag = ++j; 
//                     break;
//                 }
//                 j++;
//             }
//             if (flag == str1.length())
//             {
//                 break;
//             }
//         }
//         System.out.println(result);
//     }
// }

// public static void Qsort(char s[], int left, int right)
// {
//     if (left < right)
//     {
//         int mid = (left + right) / 2;
//         Qsort(s, mid+1, right);
//         Qsort(s, left, mid);
//         Merge(s, left, right, mid);
//     }
// }

// public static void Merge(char a[], int left, int right, int mid)
// {
//     char[] b = new char[a.length+1];
//     int l = left, r = mid + 1, tem = left;
//     while (l <= mid && r <= right)
//     {
//         if (a[l] <= a[r])
//         {
//             b[tem++] = a[l++];
//         }
//         else
//         {
//             b[tem++] = a[r++];
//         }
//     }
//     while (l <= mid)
//     {
//         b[tem++] = a[l++];
//     }
//     while (r <= right)
//     {
//         b[tem++] = a[r++];
//     }
//     for (int i = left; i <= right; i++)
//     {
//         a[i] = b[i];
//     }
// }

