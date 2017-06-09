package stringapalindromamain;

import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class StringaPalindromaMain {

    private static int BENCH_ITERATIONS = 10000;
    
    // controlla carattere per carattere con un ciclo for
    public static boolean checkPalindrome_v1(String theString) {
        int len = theString.length();
        boolean palindroma = false;
        for (int i = 0; i < len; i++) {
            if (theString.charAt(i) == theString.charAt(len - 1 - i)) {
                palindroma = true;
            } else {
                palindroma = false;
                return palindroma;
            }
        }
        return palindroma;
    }

    // crea una stringa inversa e la confronta con l'originale
    public static boolean checkPalindrome_v2(String theString) {
        boolean palindroma;
        StringBuilder buf = new StringBuilder(theString);
        String invertita = buf.reverse().toString();
        palindroma = theString.equals(invertita);
        return palindroma;
    }

    // confronta metà stringa
    public static boolean checkPalindrome_v3(String theString) {
        int n = theString.length();
        for (int i = 0; i < (n / 2); i++) {
            if (theString.charAt(i) != theString.charAt(n - i - 1)) {
                return false;
            }
        }
        return true;
    }

    // funzione Benchmark
    public static Integer doTest(ArrayList<String> toCheck, int numFunzione) {
        boolean test = true;
        boolean ritorno = false;
        int count = 0;
        long start = System.currentTimeMillis();
        for (int i = 0; i < BENCH_ITERATIONS; i++) {
            for (int j = 0; j < toCheck.size(); j++) {
                switch (numFunzione) {
                    case 1:
                        ritorno = checkPalindrome_v1(toCheck.get(j));
                        break;
                    case 2:
                        ritorno = checkPalindrome_v2(toCheck.get(j));
                        break;
                    case 3:
                        ritorno = checkPalindrome_v3(toCheck.get(j));
                        break;
                    default:
                        break;
                }
                if (ritorno == test) { // IL CICLO VIENE ESEGUITO
                    count++;
                }
            }
        }
        long stop = System.currentTimeMillis();
        long tempo = stop - start;
        System.out.println("contatore di prova: " + count); // CONTROLLIAMO CHE IL CICLO SIA STATO ESEGUITO
        System.out.println("Start: " + start + " Stop: " + stop);
        count = 0;
        return (int)tempo;
    }
    
    public static void salva_dati_CSV(int t1, int t2, int t3) {
        System.out.println("Salvataggio tempi su un file CSV...");
        BufferedWriter out = null;
        try {
            out = new BufferedWriter(new FileWriter("benchmark.csv", true));
            out.write(String.valueOf(BENCH_ITERATIONS));
            out.write(";");
            out.write(String.valueOf(t1));
            out.write(";");
            out.write(String.valueOf(t2));
            out.write(";");
            out.write(String.valueOf(t3));
            out.write("\n");
            out.close();
        } catch (FileNotFoundException e) {
            System.out.println("FileNotFound");
        } catch (IOException e) {
            System.out.println("IOException" + e);
        } finally {
            try {
                if (out != null) {
                    out.close();
                }
            } catch (IOException e) {
                System.out.println(e);
            }
        }
        System.out.println("Dati salvati su file CSV");
    }

    public static void main(String[] args) {
                
        ArrayList<String> v1 = new ArrayList<>();
        v1.add("ciao"); // corta
        v1.add("anna"); // corta palindroma
        v1.add("inipotinonavevanotopi"); // lunga
        v1.add("itopinonavevanonipoti"); // lunga palindroma

        HtmlPage.generaCSS();
        HtmlPage.generaHead();
        
        // Preparazione file CSV
        BufferedWriter out = null;
        try {
            out = new BufferedWriter(new FileWriter("benchmark.csv", false));
            out.write("BENCH_ITERATIONS;METODO1;METODO2;METODO3\n");
            out.close();
        } catch (FileNotFoundException e) {
            System.out.println("FileNotFound");
        } catch (IOException e) {
            System.out.println("IOException" + e);
        } finally {
            try {
                if (out != null) {
                    out.close();
                }
            } catch (IOException e) {
                System.out.println(e);
            }
        }
        
        for (int i = 0; i < 3; i++) {
            if (i == 1) {
                BENCH_ITERATIONS *= 10;
            } else if (i == 2) {
                BENCH_ITERATIONS *= 10;
            }
            System.out.println("BENCH_ITERATIONS: " + BENCH_ITERATIONS);
            Integer runTimeMillisec_1 = doTest(v1, 1);
            Integer runTimeMillisec_2 = doTest(v1, 2);
            Integer runTimeMillisec_3 = doTest(v1, 3);
            System.out.println("T1: " + runTimeMillisec_1);
            System.out.println("T2: " + runTimeMillisec_2);
            System.out.println("T3: " + runTimeMillisec_3);
            ArrayList<Integer> tempi = new ArrayList<>();
            tempi.add(runTimeMillisec_1);
            tempi.add(runTimeMillisec_2);
            tempi.add(runTimeMillisec_3);
            salva_dati_CSV(runTimeMillisec_1,runTimeMillisec_2,runTimeMillisec_3);
            HtmlPage.aggiungiInTabella(tempi, BENCH_ITERATIONS);
        }
        HtmlPage.chiudiHTML();
        Gnuplot.genera_immagine_grafico();
    }

}
