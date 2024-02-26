import java.util.Scanner;
import java.util.HashMap;

class TrieNode {
    HashMap<String, TrieNode> children;

    public TrieNode() {
        children = new HashMap<>();
    }
}

public class Lesson3Question5 {
    private TrieNode root; 

    public Lesson3Question5() {
        root = new TrieNode();
    }

    public void insert(String word) {
        TrieNode node = root;
        String prefix = "";
        for (char ch : word.toCharArray()) {
            prefix = prefix + ch;
            if (!node.children.containsKey(prefix)) {
                node.children.put(prefix, new TrieNode());
            }
            node = node.children.get(prefix);
        }
    }

    public String toString() {
        String result = toString(root, "");
        return result.isEmpty() ? "null" : result;
    }

    public String toString(TrieNode node, String prefix) {
        StringBuilder result = new StringBuilder();
        for (String str: node.children.keySet()) {
            TrieNode child = node.children.get(str);
            result.append(str).append("=");
            String childStr = toString(child, str);
            if (childStr.equals("null")) {
                result.append("null");
            } else {
                result.append(childStr);
            }
            result.append(", ");
        }
        return result.length() > 0 ? "{" + result.substring(0, result.length() - 2) + "}" : "null";
    }

    public static void main(String[] args) {
        Lesson3Question5 trie = new Lesson3Question5();
        Scanner scanner = new Scanner(System.in);
        String Word = scanner.nextLine();
        String[] words = Word.split(" ");

        if (words[0].isEmpty())  
        {
            System.out.println("{}");
            System.exit(0);
        }

        scanner.close();
        for (String word : words) {
            trie.insert(word);
        }
        System.out.println(trie);
        System.exit(0);
    }
}


