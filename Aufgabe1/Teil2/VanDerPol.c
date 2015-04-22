/*
 * Modellierung dynamischer Systeme 
 * Praktikum 1
 * Teil 2
 * 
 * Lösung einer (nichtlinearen) DGL 2. Ordnung
 * 
 * 	y'' = 6 * (1 - y²) * y' - y		y(0)=0		y'(0)=1
 */

#include <math.h>
#include <chplot.h>

#define h 0.02
#define x_End 31

double Ableitung1(double y1, double y2){
	return ( 6 * (1 - pow(y2,2)) * y1 ) - y2;
}

double Ableitung2(double y1){
	return y1;
}


int main() {
	
	int steps = x_End/h;
	int i;
	double k1, k2, l1, l2;
	double x[steps], y1[steps], y2[steps];

	class CPlot plot;
	
	plot.title("Praktikum 1 - Teil 2 (h=0.02 ; xEnd = 31)");
		
		
	// Init
	x[0]=0;
	y1[0]=1; //Startwert
	y2[0]=0;

	
	//EULER
	for(i=0; i<steps-1; i++){
		y1[i+1] = y1[i] + h * Ableitung1(y1[i],y2[i]);
		y2[i+1] = y2[i] + h * Ableitung2(y1[i]);
		x[i+1] = x[i] + h;
	}
	plot.data2D(x,y2);
	plot.legend("EULER", 0); 

	
	//RK2
	for(i=0; i<steps-1; i++){
		k1= h * Ableitung1(y1[i],y2[i]);
		l1= h * Ableitung2(y1[i]);
		
		k2= h * Ableitung1(y1[i]+(k1/2), y2[i]+(l1/2));
		l2= h * Ableitung2(y1[i]+(k1/2));
		
		y1[i+1] = y1[i] + k2;
		y2[i+1] = y2[i] + l2;
		
		x[i+1] = x[i] + h;
	}
	plot.data2D(x,y2);
	plot.legend("RK2", 1); 
	
	plot.plotting();
}

