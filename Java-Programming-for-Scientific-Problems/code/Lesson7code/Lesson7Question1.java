import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Lesson7Question1 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        scanner.close();

        int result = convertEnglishToNumber(input);
        System.out.println(result);
    }

    public static int convertEnglishToNumber(String input) 
    {
        Map<String, Integer> wordToNumber = ConvertionTable();

        String[] words = input.split("\\s+");
        int currentNumber = 0;
        int totalNumber = 0;
        int partialTotal = 0; 

        for (String word : words) 
        {
            Integer number = wordToNumber.get(word);
            if (number != null) 
            {
                currentNumber += number;
            } 
            else if (word.equals("hundred")) 
            {
                currentNumber *= 100;
            } 
            else if (word.equals("thousand")) 
            {
                partialTotal += currentNumber * 1000;
                currentNumber = 0;
            } 
            else if (word.equals("million")) 
            {
                totalNumber += currentNumber * 1000000;
                currentNumber = 0;
            } 
            else if (word.equals("billion"))
            {
                totalNumber += currentNumber * 1000000000;
                currentNumber = 0;
            }
            else if (word.equals("and"))  continue;
            else 
            {
                String[] parts = word.split("-");
                if (parts.length == 2) 
                {
                    int tens = wordToNumber.get(parts[0]);
                    int ones = wordToNumber.get(parts[1]);
                    currentNumber += tens + ones;
                }
            }
        }

        totalNumber += partialTotal + currentNumber;
        return totalNumber;
    }

    private static Map<String, Integer> ConvertionTable()
    {
        Map<String, Integer> wordToNumber = new HashMap<>();
        wordToNumber.put("zero", 0);
        wordToNumber.put("one", 1);
        wordToNumber.put("two", 2);
        wordToNumber.put("three", 3);
        wordToNumber.put("four", 4);
        wordToNumber.put("five", 5);
        wordToNumber.put("six", 6);
        wordToNumber.put("seven", 7);
        wordToNumber.put("eight", 8);
        wordToNumber.put("nine", 9);
        wordToNumber.put("ten", 10);
        wordToNumber.put("eleven", 11);
        wordToNumber.put("twelve", 12);
        wordToNumber.put("thirteen", 13);
        wordToNumber.put("fourteen", 14);
        wordToNumber.put("fifteen", 15);
        wordToNumber.put("sixteen", 16);
        wordToNumber.put("seventeen", 17);
        wordToNumber.put("eighteen", 18);
        wordToNumber.put("nineteen", 19);
        wordToNumber.put("twenty", 20);
        wordToNumber.put("thirty", 30);
        wordToNumber.put("forty", 40);
        wordToNumber.put("fifty", 50);
        wordToNumber.put("sixty", 60);
        wordToNumber.put("seventy", 70);
        wordToNumber.put("eighty", 80);
        wordToNumber.put("ninety", 90);
        return wordToNumber;
    }
}
