/*
 * Modellierung dynamischer Systeme 
 * Praktikum 1
 * Teil 1
 * 
 * Lösung steifer Differentialgleichungen
 * 
 * 	y' = 10 - 500 * y + 5000 * x	y(0)=1
 */

#include <chplot.h>
#include <math.h>

#define h 0.005
#define x_End 0.2

double Ableitung(double x, double y){
	return 10 - (500*y) + (5000*x);
}
double AbleitungImplizitEuler(double xiplus1, double y){
	return ( y + (10*h) + (5000*xiplus1*h) )/( (500*h) + 1 );
}
double AbleitungAnalytisch(double x, double y){
	return 10 * x + pow(exp(1),(-500.0*x));
}

int main() {
	
	int steps = x_End/h;
	int i;
	double  k1, k2;
	double  xEulerExpl[steps],  yEulerExpl[steps],
			xRK2[steps], 		yRK2[steps],
			xEulerImpl[steps],  yEulerImpl[steps],
			xAnalytisch[steps], yAnalytisch[steps];

	class CPlot plot0, plot1;
	
	plot0.title("Praktikum 1 - Teil 1 (h=0.005 ; xEnd = 0.2)");
	plot1.title("Praktikum 1 - Teil 1 [Abweichungen] (h=0.005 ; xEnd = 0.2)");	
		
	// Init
	xEulerExpl[0]=0;
	yEulerExpl[0]=1; 
	
	xRK2[0]=0;
	yRK2[0]=1;

	xEulerImpl[0]=0;
	yEulerImpl[0]=1;

	xAnalytisch[0]=0;
	yAnalytisch[0]=1;
	
	//explizite EULER
	for(i=0; i<steps-1; i++){
		yEulerExpl[i+1] = yEulerExpl[i] + h * Ableitung(xEulerExpl[i],yEulerExpl[i]);
		xEulerExpl[i+1] = xEulerExpl[i] + h;
	}
	plot0.data2D(xEulerExpl,yEulerExpl);
	plot0.legend("explizite EULER", 0); 

	
	//RK2
	for(i=0; i<steps-1; i++){
		k1= h * Ableitung(xRK2[i], yRK2[i]);
		k2= h * Ableitung(xRK2[i]+h/2, yRK2[i]+k1/2);
		yRK2[i+1] = yRK2[i] + k2;
		xRK2[i+1] = xRK2[i] + h;
	}
	plot0.data2D(xRK2,yRK2);
	plot0.legend("RK2", 1); 
	

	//implizite EULER
	for(i=0; i<steps-1; i++){
		xEulerImpl[i+1] = xEulerImpl[i] + h; //X Muss zuerst gesetzt werden!
		yEulerImpl[i+1] = AbleitungImplizitEuler(xEulerImpl[i+1],yEulerImpl[i]);
	}
	plot0.data2D(xEulerImpl,yEulerImpl);
	plot0.legend("implizite EULER", 2); 
	

	//analytisch
	for(i=0; i<steps-1; i++){
		yAnalytisch[i+1] = AbleitungAnalytisch(xAnalytisch[i],yAnalytisch[i]);
		xAnalytisch[i+1] = xAnalytisch[i] + h;
	}
	plot0.data2D(xAnalytisch,yAnalytisch);
	plot0.legend("analytisch", 3); 
	plot0.plotting();
	
	
	double yEulerExplyAnalytisch[steps];
	double yRK2Analytisch[steps];	
	double yEulerImplAnalytisch[steps];
	for(i = 0; i < steps; i++) 
    {
      yEulerExplyAnalytisch[i]	= yEulerExpl[i]- yAnalytisch[i]; 
      yRK2Analytisch[i]			= yRK2[i]- yAnalytisch[i]; 
      yEulerImplAnalytisch[i]	= yEulerImpl[i]- yAnalytisch[i];  
	}  
	
	plot1.data2D(xEulerExpl,yEulerExplyAnalytisch);
	plot1.legend("explizite EULER",0);
	plot1.data2D(xRK2,yRK2Analytisch);
	plot1.legend("RK2",1);
	plot1.data2D(xEulerImpl,yEulerImplAnalytisch);
	plot1.legend("implizite EULER",2);
	plot1.plotting();
}

