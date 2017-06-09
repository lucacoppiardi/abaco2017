/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package stringapalindromamain;


import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

/**
 *
 * @author simranjot
 */
public class StringaPalindromaMain {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        int BENCH_ITERATIONS = 10000;
        
        ArrayList<Integer> l = new ArrayList();
        
        l.add(2);
        l.add(3);
        l.add(44);
        
        System.out.println(l.get(0));
        System.out.println(l.get(1));
        System.out.println(l.get(2));
        
        HtmlPage.generaHead();
        
        for(int i=0;i<3;i++){
        
            if (i==1) {
			BENCH_ITERATIONS*=10;
		} else if (i==2) {
			BENCH_ITERATIONS*=2;
		}
            HtmlPage.generaTabella(l,BENCH_ITERATIONS);
            salva_dati_CSV(l,BENCH_ITERATIONS);
        }
        
        
        HtmlPage.chiudiHTML();
        
        genera_immagine_grafico();
        HtmlPage.generaCSS();
        Runtime commandPrompt = Runtime.getRuntime();
        
        try{
            
            commandPrompt.exec("gnuplot commandi_gnuplot.txt");
            System.out.printf("lanciato il commando gnuplot");
            
        }
        catch(IOException e){
            
        }
       // catch(InterruptedException e){
            
        //}
    }
    
    public static void salva_dati_CSV(ArrayList<Integer> l, int BENCH_ITERATIONS){
        System.out.println("Salvataggio tempi su file CSV...");
        
        BufferedWriter out = null;
         
        try{
            out = new BufferedWriter(new FileWriter("benchmark.csv",true));
            
            out.write(String.valueOf(BENCH_ITERATIONS)); 
            out.write(";");
            out.write(String.valueOf(l.get(0)));
            out.write(";"); 
            out.write(String.valueOf(l.get(1)));
            out.write(";"); 
            out.write(String.valueOf(l.get(2)));
            out.write("\n");
            out.close();
        
            out.close();
        }
        catch(FileNotFoundException e){
            System.out.println("FileNotFound");
        }
        catch(IOException e){
            System.out.println("IOException"+e);
        }
        finally{
            try{
                if(out!=null)
                    out.close();
            }
            catch(IOException e){
                System.out.println(e);
            }
        }
        
        System.out.println("Dati salvati  tempi su file CSV");
    }
    
    public static void genera_immagine_grafico(){
        
        System.out.println("Generazione grafico...");
        
        BufferedWriter out = null;
        
        try{
            out = new BufferedWriter(new FileWriter("commandi_gnuplot.txt"));
            
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
        }
        catch(FileNotFoundException e){
            System.out.println("FileNotFound");
        }
        catch(IOException e){
            System.out.println("IOException"+e);
        }
        finally{
            try{
                if(out!=null)
                    out.close();
            }
            catch(IOException e){
                System.out.println(e);
            }
        }
        
        System.out.println("Grafico completato");
    
    }
    
}
