import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class CodeLineCounterWithStream {
    public static boolean isSingleLineComment(String line) {
        line = line.trim();
        return line.startsWith("//");
    }

    public static boolean isStartOfMultiLineComment(String line) {
        line = line.trim();
        return line.startsWith("/*");
    }

    public static boolean isEndOfMultiLineComment(String line) {
        line = line.trim();
        return line.endsWith("*/");
    }

    public static boolean isInsideMultiLineComment(String line, int insideMultiLineComment) {
        line = line.trim();
        return insideMultiLineComment == 1 || line.startsWith("/*") || line.endsWith("*/") || line.contains("*/");
    }

    // 判断是否是注释行的函数
    public static boolean isCommentLine(String line, int insideMultiLineComment) {
        return isSingleLineComment(line) || isInsideMultiLineComment(line, insideMultiLineComment);
    }

    // 统计有效代码行数
    public static int countValidCodeLines(File file) {
        int[] insideMultiLineComment = {0}; // 用数组包装以在lambda中修改

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            return (int) reader.lines()
                    .map(String::trim)
                    .filter(line -> !line.isEmpty() && !isCommentLine(line, insideMultiLineComment[0]))
                    .peek(line -> {
                        if (isStartOfMultiLineComment(line)) {
                            insideMultiLineComment[0] = 1;
                        } else if (isEndOfMultiLineComment(line)) {
                            insideMultiLineComment[0] = 0;
                        }
                    })
                    .count();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return 0;
    }

    public static void main(String[] args) {
        String folderPath = "D:\\大学资料\\Road-To-CSAI\\Java-Programming-for-Scientific-Problems\\code"; // 替换成你要搜索的文件夹路径

        try {
            List<File> javaFiles = getJavaFiles(folderPath);
            Map<String, Integer> fileLinesMap = new HashMap<>();

            for (File file : javaFiles) {
                int lines = countValidCodeLines(file);
                System.out.println("FileName: " + file.getName() + ", LineValid: " + lines);
                fileLinesMap.put(file.getName(), lines);
            }

            // 按有效代码行数降序排序
            List<Map.Entry<String, Integer>> sortedList = fileLinesMap.entrySet()
                    .stream()
                    .sorted((entry1, entry2) -> entry2.getValue().compareTo(entry1.getValue()))
                    .collect(Collectors.toList());

            // 输出有效代码行数最多的前3个文件名及其行数
            int count = 0;
            for (Map.Entry<String, Integer> entry : sortedList) {
                if (count >= 3) {
                    break;
                }
                System.out.println(entry.getKey() + " - " + entry.getValue() + " lines");
                count++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static List<File> getAllJavaFiles(File folder) {
        List<File> javaFiles = new ArrayList<>();

        File[] files = folder.listFiles();
        if (files != null) {
            for (File file : files) {
                if (file.isFile() && file.getName().endsWith(".java")) {
                    javaFiles.add(file);
                } else if (file.isDirectory()) {
                    javaFiles.addAll(getAllJavaFiles(file));
                }
            }
        }

        return javaFiles;
    }

    public static List<File> getJavaFiles(String folderPath) throws IOException {
        File folder = new File(folderPath);

        if (!folder.exists() || !folder.isDirectory()) {
            throw new IOException("路径无效");
        }

        return getAllJavaFiles(folder);
    }
}
