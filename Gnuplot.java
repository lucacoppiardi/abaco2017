package stringapalindromamain;

import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;

public final class Gnuplot {

    public static void genera_immagine_grafico() {
        System.out.println("Generazione grafico...");
        BufferedWriter out = null;
        try {
            out = new BufferedWriter(new FileWriter("comandi_gnuplot.txt"));
            out.write("set datafile separator \";\"\n");
            out.write("set auto x\n");
            out.write("set auto y\n");
            out.write("set title \'Benchmark\'\n");
            out.write("set ylabel \'Tempo esec. (millisec)\'\n");
            out.write("set xlabel \'Iterazioni\'\n");
            out.write("set key left\n");
            out.write("color1 = \"#99ffff\"; color2 = \"#4671d5\"; color3 =\"#ff0000\";\n");
            out.write("set style data histogram\n");
            out.write("set style histogram cluster gap 1\n");
            out.write("set style fill solid border -1\n");
            out.write("set xtic scale 0\n");
            out.write("set term png\n");
            out.write("set output \'grafico.png\'\n");
            out.write("plot \'benchmark.csv\' using 2:xtic(1) ti col fc rgb color1, \'\' u 3 ti col fc rgb color2, \'\' u 4 ti col fc rgb color3\n");
            out.write("quit\n");
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
        Runtime commandPrompt = Runtime.getRuntime();
        try {
            commandPrompt.exec("gnuplot comandi_gnuplot.txt");
            System.out.println("Grafico completato.");
        } catch (IOException e) {
            System.out.println("Errore nel passare il file comandi a Gnuplot: " + e.getMessage());
        }
    }
}
