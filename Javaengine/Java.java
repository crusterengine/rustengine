//Package Rustengine;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

public class Java {
    static long wordCount = 0; 
    static int lineCount = 0; 
        
        public static void fileProcessing(String filePath, HashMap<String, LinkedList<Integer>> wordIndex){
    
            try {
                BufferedReader reader = new BufferedReader(new FileReader(filePath));
    
                String line;
    
                while (reader.ready()) {
                    line = reader.readLine();
                    lineCount++;
                    String[] words = line.split("\\s+");
                    for (String word : words) {
                        if (!word.isEmpty()){
                        processWord(word, wordIndex);
                    }

                }

            }
            reader.close();
        } catch (Exception e) {
            System.err.println("An exception was caught while reading");        
        }
        //System.out.println(wordIndex.size());
}

    public static void processWord(String word, HashMap<String, LinkedList<Integer>> wordIndex){
        wordCount++;
        int page = lineCount/50+1;
        //String output = word.trim();
        String output = word.replaceAll("^[^a-zA-Z]+|[^a-zA-Z]+$", "");
        LinkedList<Integer> pageList = wordIndex.get(output);

        if (pageList == null){
            LinkedList<Integer> pg = new LinkedList<Integer>();
            pg.add(page);
            wordIndex.put(output,pg);
        } else if (!pageList.getLast().equals(page)) {
            pageList.addLast(page);
            wordIndex.put(output,pageList);
        }
    }

    public static void query (HashMap<String,LinkedList<Integer>> wordIndex, String Query){
        LinkedList<Integer> pg = wordIndex.get(Query);
        if (pg != null){
            System.out.print(Query + ": ");
            for (Integer integer : pg) {
                System.out.print(integer + ", ");
            } 
        } else {
            System.out.println("Query not found");
        }
        System.out.println();
    }

    public static void printAll(HashMap<String,LinkedList<Integer>> wordIndex){
        for (String word : wordIndex.keySet()) {
                query(wordIndex, word);
        }
    }

    public static void printstream(HashMap<String,LinkedList<Integer>> wordIndex){
        wordIndex.forEach((key, value) -> {
            //System.out.println(key + ": " );
            query(wordIndex, key);
        });
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
            System.out.println(i);
        }
        //printAll(wordIndex);
        //printstream(wordIndex);
        System.out.println(wordCount);
        //query(wordIndex,query);
    }
    
}
