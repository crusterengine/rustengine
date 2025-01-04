import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;
import java.util.LinkedList;


public class hashmaplinkedtwo {
   private static long word_count;


   public static void print_query(HashMap<String, LinkedList<Integer>> word_index, String query) {


       System.out.print(query + ": ");


       LinkedList<Integer> page_list = word_index.get(query);


       if (page_list != null) {


           for (Integer page : page_list) {
               System.out.print(page + ", ");
           }


       } else {
           System.out.print("Not found.");
       }
       System.out.println("");
   }


   public static void print_word_index(HashMap<String, LinkedList<Integer>> word_index) {


       word_index.forEach((key, value) -> {
           System.out.print(key + ": ");
           for (Integer values : value) {
               System.out.print(values + ", ");
           }
           System.out.println("");
       });
   }


   public static void file_processing(String file, HashMap<String, LinkedList<Integer>> word_index) {


       try {
           BufferedReader reader = new BufferedReader(new FileReader(file));


           String line;
           int linecount = 0;


           while ((line = reader.readLine()) != null) {
               linecount++;


               int start = 0;
               int length = line.length();


               while (start < length) {
                   // Skip leading whitespace
                   while (start < length && Character.isWhitespace(line.charAt(start))) {
                       start++;
                   }


                   // Find the end of the word
                   int end = start;
                   while (end < length && !Character.isWhitespace(line.charAt(end))) {
                       end++;
                   }


                   // If a word is found, process it
                   if (start < end) {
                       process_word(line, start, end, word_index, linecount);
                   }


                   // Move to the next word
                   start = end + 1;
               }


           }


           reader.close();


       } catch (Exception e) {
           System.err.println("could not create buffered readder");
           return;
       }
   }


   public static void process_word(String line, int start, int end, HashMap<String, LinkedList<Integer>> word_index,
           int linecount) {
       word_count++;


       int page = linecount / 50 + 1;
       // Extract the raw word from the line
       String rawWord = line.substring(start, end);


       // Remove non-ASCII alphabetic characters from the start and end
       int newStart = 0;
       int newEnd = rawWord.length();


       while (newStart < newEnd && !isAsciiAlphabetic(rawWord.charAt(newStart))) {
           newStart++;
       }


       while (newEnd > newStart && !isAsciiAlphabetic(rawWord.charAt(newEnd - 1))) {
           newEnd--;
       }


       // Extract the trimmed word
       if (newStart < newEnd) {
           String word = rawWord.substring(newStart, newEnd);


           // Add the word and page to the HashMap
           word_index.computeIfAbsent(word, k -> new LinkedList<>());


           // Add the page only if it's not already in the LinkedList
           LinkedList<Integer> pages = word_index.get(word);
           if (!pages.contains(page)) {
               pages.add(page);
           }
       }
   }


   /**
    * Checks if a character is an ASCII alphabetic character (A-Z, a-z).
    *
    * @param c The character to check.
    * @return True if the character is ASCII alphabetic, false otherwise.
    */
   private static boolean isAsciiAlphabetic(char c) {
       return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
   }


   public static void main(String[] args) {


       if (args.length != 3) {
           System.out.print("Missing argument, check file or counter\n");
           return;
       }


       String file_path = args[0];


       // File file = new File(file_path);


       // if (!file.exists()) {
       // System.out.print("File not found: " + file_path + "\n");
       // return;
       // }


       int itr = Integer.parseInt(args[1]);


       String query = args[2];


       HashMap<String, LinkedList<Integer>> word_index = new HashMap<>();


       for (int i = 0; i < itr; i++) {
           file_processing(file_path, word_index);
           System.out.println(i);
       }


       System.out.println("Java found the file contains " + word_count + " words.");


       // print_query(word_index, query);
       // print_word_index(word_index);
   }
}

