import java.math.BigInteger;
import java.util.Scanner;

public class Lesson6Question5 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String loc = scanner.nextLine();
        int sqrt = Integer.parseInt(loc);
        BigInteger num = scanner.nextBigInteger();
        scanner.close();

        BigInteger result = nthRoot(num, sqrt);
        if (sqrt == 1)
        {
            System.out.println(num);
            System.exit(0);
        }
        else if (num.equals(BigInteger.ONE))
        {
            System.out.println(1);
            System.exit(0);
        }
        else if (num.equals(BigInteger.ZERO))
        {
            System.out.println(0);
            System.exit(0);
        }
        System.out.println(result);
    }

    private static int JudgingScope(BigInteger num, int sqrt)
    {
        int count = 0;
        while (num.compareTo(BigInteger.ZERO) > 0)
        {
            num = num.divide(BigInteger.valueOf(10));
            count++;
        }
        // System.out.println((count-1)/sqrt);
        return (count-1) / sqrt;
    }

    private static BigInteger nthRoot(BigInteger num, int sqrt) {
        BigInteger left = FastNthRoot(BigInteger.valueOf(10), JudgingScope(num, sqrt));
        BigInteger right = left.multiply(BigInteger.valueOf(10));

        while (left.compareTo(right) < 0) {
            BigInteger mid = left.add(right).divide(BigInteger.valueOf(2));
            BigInteger midToPowerOfSqrt = FastNthRoot(mid, sqrt);

            if (midToPowerOfSqrt.compareTo(num) == 0) {
                return mid;
            } else if (midToPowerOfSqrt.compareTo(num) < 0) {
                left = mid.add(BigInteger.ONE);
            } else {
                right = mid;
            }
        }
        return left.subtract(BigInteger.ONE);
    }

    private static BigInteger FastNthRoot(BigInteger num, int sqrt)
    {
        BigInteger base = num;
        BigInteger result = BigInteger.ONE;
        while (sqrt > 0) {
            if ((sqrt&1) == 1)
            {
                result = result.multiply(base);
            }
            base = base.multiply(base);
            sqrt = sqrt >> 1;
        }
        return result;
    }
}