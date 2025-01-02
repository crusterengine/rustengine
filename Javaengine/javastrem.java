import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.StringTokenizer;

public class javastrem {
    static long wordCount = 0;
    static int lineCount = 0;

      public static void fileProcessing(String filePath, HashMap<String, LinkedList<Integer>> wordIndex) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = reader.readLine()) != null) {
                lineCount++;
    
                StringTokenizer tokenizer = new StringTokenizer(line);
                while (tokenizer.hasMoreTokens()) {
                    String word = tokenizer.nextToken();
                    if (!word.isEmpty()) {
                        processWord(word, wordIndex);
                    }
                }
            }
        } catch (Exception e) {
            System.err.println("An exception was caught while reading");
        }
    }

    public static void processWord(String word, HashMap<String, LinkedList<Integer>> wordIndex) {
        wordCount++;
        int page = (lineCount - 1) / 50 + 1;  // Corrected page calculation
        String cleanedWord = word.replaceAll("^[^a-zA-Z]+|[^a-zA-Z]+$", "");  // Cleaning word

        // Use computeIfAbsent to ensure the LinkedList is created only if absent
        LinkedList<Integer> pageList = wordIndex.computeIfAbsent(cleanedWord, k -> new LinkedList<>());

        // Add page to the list if it's not already the last page
        if (pageList.isEmpty() || pageList.getLast() != page) {
            pageList.addLast(page);
        }
    }

    public static void query(HashMap<String, LinkedList<Integer>> wordIndex, String query) {
        LinkedList<Integer> pages = wordIndex.get(query);
        if (pages != null) {
            System.out.print(query + ": ");
            pages.forEach(page -> System.out.print(page + ", "));
            System.out.println();
        } else {
            System.out.println("Query not found");
        }
    }

    public static void printAll(HashMap<String, LinkedList<Integer>> wordIndex) {
        for (String word : wordIndex.keySet()) {
            query(wordIndex, word);
        }
    }

    public static void printstream(HashMap<String, LinkedList<Integer>> wordIndex) {
        wordIndex.forEach((key, value) -> query(wordIndex, key));
    }

    public static void main(String[] args) {
        if (args.length != 3) {
            System.out.println("Missing argument, check file or counter");
            return;
        }

        String filePath = args[0];
        int itr = Integer.parseInt(args[1]);
        String query = args[2];

        HashMap<String, LinkedList<Integer>> wordIndex = new HashMap<>();

        for (int i = 0; i < itr; i++) {
            fileProcessing(filePath, wordIndex);
        }

        // printAll(wordIndex);
        // printstream(wordIndex);
        System.out.println(wordCount);
        query(wordIndex, query);
    }
}
