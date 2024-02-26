public class Dog
{
    public int WeightPounds;

    public Dog(int x)
    {
        WeightPounds = x;
    }

    public void makenoise()
    {
        if (WeightPounds < 10)
        {
            System.out.println("yip!");
        }
        else if (WeightPounds < 30)
        {
            System.out.println("bark!");
        }
        else
        {
            System.out.println("woooooof!");
        }
    }

    public static Dog maxDog(Dog d1, Dog d2)
    {
        if (d1.WeightPounds > d2.WeightPounds)
        {
            return d1;
        }
        return d2;
    }

    public Dog maxDog(Dog d2)
    {
        if (this.WeightPounds > d2.WeightPounds)
        {
            return this;
        }
        return d2;
    }
}
