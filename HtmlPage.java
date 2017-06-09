package stringapalindromamain;

import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public final class HtmlPage {

    public static void generaHead() {
        System.out.println("Generazione prima parte pagina HTML...");
        BufferedWriter out = null;
        try {
            out = new BufferedWriter(new FileWriter("benchmark.html"));
            out.write("<html>\n");
            out.write("<head>\n");
            out.write("\t<title>Benchmark</title>\n");
            out.write("\t<link href=\"benchmark.css\" rel=\"stylesheet\" type=\"text/css\"></link>\n");
            out.write("</head>\n");
            out.write("<body>\n");
            out.write("\t<h2>Benchmark</h2>\n");
            out.write("\t<table>\n");
            out.write("\t\t<tr>\n");
            out.write("\t\t\t<th>Iterazioni</th>\n");
            out.write("\t\t\t<th>T1</th>\n");
            out.write("\t\t\t<th>T2</th>\n");
            out.write("\t\t\t<th>T3</th>\n");
            out.write("\t\t</tr>\n");
            out.write("\t\t<tr>\n");
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
        System.out.println("Prima parte pagina HTML generata.");
    }

    public static void aggiungiInTabella(ArrayList<Integer> tempi, int BENCH_ITERATIONS) {
        System.out.println("Inserimento dati in tabella...");
        BufferedWriter out = null;
        try {
            out = new BufferedWriter(new FileWriter("benchmark.html", true));
            out.write("\t\t<tr>\n");
            out.write("\t\t\t<td>");
            out.write(String.valueOf(BENCH_ITERATIONS));
            out.write("</td>\n");
            for (int i = 0; i < 3; i++) {
                out.write("\t\t\t<td>");
                out.write(tempi.get(i).toString());
                out.write("</td>\n");
            }
            out.write("\t\t</tr>\n");
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
        System.out.println("Tabella aggiornata.");
    }

    public static void chiudiHTML() {
        System.out.println("Conclusione pagina HTML...");
        BufferedWriter out = null;
        try {
            out = new BufferedWriter(new FileWriter("benchmark.html", true));
            out.write("\t</table>\n");
            out.write("\t<img src=\"grafico.png\" alt=\"gnuplot\">\n");
            out.write("</body>\n");
            out.write("</html>\n");
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
        System.out.println("Pagina HTML terminata.");
    }

    public static void generaCSS() {
        System.out.println("Creazione CSS...");
        BufferedWriter out = null;
        try {
            out = new BufferedWriter(new FileWriter("benchmark.css"));
            out.write("h2 {\n");
            out.write("\ttext-align:center\n");
            out.write("}\n");
            out.write("table {\n");
            out.write("\tborder-collapse: collapse;\n");
            out.write("\ttext-align:center;\n");
            out.write("\tmargin-left: auto;\n");
            out.write("\tmargin-right: auto;\n");
            out.write("}\n");
            out.write("table, th, td {\n");
            out.write("\tborder: 1px solid black;\n");
            out.write("}\n");
            out.write("th, td {\n");
            out.write("\tpadding: 15px;\n");
            out.write("}\n");
            out.write("img {\n");
            out.write("\tdisplay: block;\n");
            out.write("\tmargin: auto;\n");
            out.write("}\n");
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
        System.out.println("Creato CSS.");
    }
}
