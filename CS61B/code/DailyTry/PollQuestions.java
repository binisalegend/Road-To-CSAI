public class PollQuestions {
    public static void main(String[] args)
    {
        Walrus a = new Walrus(1000, 8.3);
        Walrus b;
        b = a;
        b.weight = 5;
        System.out.println(a);
        System.out.println(b);

        int x = 5;
        int y;
        y = x;
        x = 2;
        System.out.println(x);
        System.out.println(y);
    }

    public static class Walrus
    {
        public int weight;
        public double tucksize;

        public Walrus(int w, double ts)
        {
            weight = w;
            tucksize = ts;
        }

        public String toString()
        {
            return String.format("weight: %d, tuck size: %.2f", weight, tucksize);
        }
    }
}
