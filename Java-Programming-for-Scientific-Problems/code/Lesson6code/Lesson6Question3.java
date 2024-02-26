// 矩阵快速幂算法
import java.util.Scanner;

public class Lesson6Question3 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long n = scanner.nextLong();
        scanner.close();

        System.out.println(fib(n-1));
    }

    static long ModNumber = (long) Math.pow(10, 9) + 7;

    private static long fib(long n) {
        if (n <= 1) {
            return n;
        }

        long[][] fibMatrix = {{1, 1}, {1, 0}};
        matrixPower(fibMatrix, n - 1);

        return fibMatrix[0][0] % ModNumber;
    }

    private static void matrixPower(long[][] matrix, long n) {
        long[][] result = {{1, 1}, {1, 0}};

        while (n > 0) {
            if (n % 2 == 1) {
                multiplyMatrix(result, matrix);
            }
            n /= 2;
            multiplyMatrix(matrix, matrix);
        }

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                matrix[i][j] = result[i][j];
            }
        }
    }

    private static void multiplyMatrix(long[][] matrix1, long[][] matrix2) {
        long a = (matrix1[0][0] * matrix2[0][0] + matrix1[0][1] * matrix2[1][0]) % ModNumber;
        long b = (matrix1[0][0] * matrix2[0][1] + matrix1[0][1] * matrix2[1][1]) % ModNumber;
        long c = (matrix1[1][0] * matrix2[0][0] + matrix1[1][1] * matrix2[1][0]) % ModNumber;
        long d = (matrix1[1][0] * matrix2[0][1] + matrix1[1][1] * matrix2[1][1]) % ModNumber;

        matrix1[0][0] = a;
        matrix1[0][1] = b;
        matrix1[1][0] = c;
        matrix1[1][1] = d;
    }
}

// 普通迭代做法
// import java.util.Scanner;

// public class Main {
//     public static void main(String[] args) {
//         Scanner scanner = new Scanner(System.in);
//         long n = scanner.nextLong();
//         scanner.close();

//         System.out.println(fib(n-1));
//     }

//     static long ModNumber = (long)Math.pow(10, 9);

//     private static long fib(long n)
//     {
//         return F(1, 0, n);
//     }

//     private static long F(long a, long b, long n)
//     {
//         while (n > 0)
//         {
//             long tmp = b % ModNumber;
//             b = a % ModNumber + b % ModNumber;
//             a = tmp;
//             n--;
//         }
//         return a % ModNumber + b % ModNumber;
//     }
// }

