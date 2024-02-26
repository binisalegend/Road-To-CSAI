import java.math.BigInteger;
import java.util.Scanner;

public class Lesson2Question3 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        BigInteger n = scanner.nextBigInteger();
        scanner.close();

        BigInteger result = cubeRoot(n);

        System.out.println(result);
    }

    public static BigInteger cubeRoot(BigInteger n) {
        BigInteger two = BigInteger.valueOf(2);
        BigInteger three = BigInteger.valueOf(3);

        BigInteger x = n;
        while (true) {
            BigInteger prevX = x;
            x = x.multiply(two)
                 .add(n.divide(x.pow(2)))
                 .divide(three);

            if (x.equals(prevX) || x.subtract(prevX).abs().compareTo(BigInteger.ONE) <= 0) {
                break;
            }
        }
        return x;
    }
}

