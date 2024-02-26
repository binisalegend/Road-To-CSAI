import java.math.BigInteger;
import java.util.Scanner;

public class Lesson2Question4 {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        BigInteger a = scanner.nextBigInteger();
        BigInteger b = scanner.nextBigInteger();
        BigInteger p = scanner.nextBigInteger();

        BigInteger aloc = a;
        BigInteger bloc = b;
        BigInteger ploc = p;
        scanner.close();

        a.mod(p);
        BigInteger rem = BigInteger.valueOf(1);
        BigInteger one = BigInteger.valueOf(1);
        BigInteger two = BigInteger.valueOf(2);
        while (b.compareTo(BigInteger.ZERO) != 0)
        {
            if (b.mod(two).compareTo(one) == 0)
            {
                rem = rem.multiply(a).mod(p);
            }
            a = a.multiply(a).mod(p);
            b = b.divide(two);
        }
        System.out.println(aloc + "^" + bloc + " mod " + ploc + "=" + rem);
        System.exit(0);
    }
}
