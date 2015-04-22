/*
 * Modellierung dynamischer Systeme 
 * Praktikum 1
 * Teil 3
 * 
 * Lösung chaotischer Differentialgleichungen
 * 
 * 	x' = -10 *(x - y)		x(0)=0.01
 * 	y' = (40 - z)*x - y		y(0)=0.01
 * 	z' = x*y - 2.67*z		z(0)=0.0
 */

#include <math.h>
#include <chplot.h>

#define h 0.002
#define x_End 120

double AbleitungX(double x, double y){
	return -10 * (x-y);
}
double AbleitungY(double x, double y, double z){
	return ((40-z)*x) - y;
}
double AbleitungYAlternativ(double x, double y, double z){
	return ((40.000000001-z)*x) - y;
}
double AbleitungZ(double x, double y, double z){
	return (x*y) - (2.67*z);
}


int main() {
	
	int steps = x_End/h;
	int i;
	double kx1, kx2, ky1, ky2, kz1, kz2;
	double x[steps], y[steps], z[steps], t[steps];

	class CPlot plot0, plot1, plot2;
	
	plot0.title("Praktikum 1 - Teil 3 [Funktion x(t)] (h=0.002 ; xEnd = 120)");
	plot1.title("Praktikum 1 - Teil 3 [z(x)] (h=0.002 ; xEnd = 120)");
	plot2.title("Praktikum 1 - Teil 3 [Funktion x(t) / Vergleich 40 und 40.000000001] (h=0.002 ; xEnd = 120)");

		
	// Init
	x[0]=0.01;
	y[0]=0.01;
	z[0]=0.0; 
	t[0]=0;

	
	//RK2
	for(i=0; i<steps-1; i++){
		kx1= h * AbleitungX(x[i], y[i]);
		kx2= h * AbleitungX(x[i]+h/2, y[i]+kx1/2);
		x[i+1] = x[i] + kx2;
		
		ky1= h * AbleitungY(x[i], y[i], z[i]);
		ky2= h * AbleitungY(x[i]+ky1/2, y[i]+h/2, z[i]+ky1/2);		
		y[i+1] = y[i] + ky2;
		
		kz1= h * AbleitungZ(x[i], y[i], z[i]);
		kz2= h * AbleitungZ(x[i]+kz1/2, y[i]+kz1/2, z[i]+h/2);
		z[i+1] = z[i] + kz2;
		
		t[i+1]= t[i]+h;
	}
	plot0.data2D(t,x);
	plot2.data2D(t,x);
	plot0.legend("RK2", 0); 
	plot2.legend("RK2 (40)", 0); 
	plot0.plotting();
	
	plot1.data2D(x,z);
	plot1.legend("RK2", 0); 
	plot1.plotting();
	
	
	//Alternative Berechnung mit 40.000000001
	for(i=0; i<steps-1; i++){
		kx1= h * AbleitungX(x[i], y[i]);
		kx2= h * AbleitungX(x[i]+h/2, y[i]+kx1/2);
		x[i+1] = x[i] + kx2;
		
		ky1= h * AbleitungYAlternativ(x[i], y[i], z[i]);
		ky2= h * AbleitungYAlternativ(x[i]+ky1/2, y[i]+h/2, z[i]+ky1/2);		
		y[i+1] = y[i] + ky2;
		
		kz1= h * AbleitungZ(x[i], y[i], z[i]);
		kz2= h * AbleitungZ(x[i]+kz1/2, y[i]+kz1/2, z[i]+h/2);
		z[i+1] = z[i] + kz2;
		
		t[i+1]= t[i]+h;
	}
	
	plot2.data2D(t,x);
	plot2.legend("RK2 (40.000000001)", 1); 
	plot2.plotting();
}

