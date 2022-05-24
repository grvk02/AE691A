#include <acado_toolkit.hpp>
#include <acado_optimal_control.hpp>
#include <acado_gnuplot.hpp>
int main( ){

    USING_NAMESPACE_ACADO

    // INTRODUCE THE VARIABLES:
    // -------------------------
    DifferentialState     x,y,v_x,v_y;
    Control               a_x,a_y  ;
    DifferentialEquation  f   ;
// Constant variables
    const double au = 1.5e8;
    const double G = 1.4761e-34;
    const double M_sun = 2.0e30; 
    // DEFINE A DIFFERENTIAL EQUATION:
    // -------------------------------
    
    f << dot(x) == v_x;
    f << dot(y) == v_y;
    f << dot(v_x) ==(-(G*M_sun*x)/pow(x*x+y*y,(3/2))) + a_x ;
    f<< dot(v_y) == (-(G*M_sun*y)/pow(x*x+y*y,(3/2))) + a_y;

    // DEFINE AN OPTIMAL CONTROL PROBLEM:
    // ----------------------------------
    OCP ocp( 0.0, 473,1000); 
    ocp.minimizeLagrangeTerm( a_x*a_x + a_y*a_y  );  // weight this with the physical cost!!!
    ocp.subjectTo( f );

    ocp.subjectTo( AT_START, x ==  0.0 );
    ocp.subjectTo( AT_START, y == -1.0 );
    ocp.subjectTo( AT_START, v_x == 0.01728 );
    ocp.subjectTo( AT_START, v_y == 0.0 );
    ocp.subjectTo( AT_END, x ==  0.0 );
    ocp.subjectTo( AT_END, y == 2.77 );
    ocp.subjectTo( AT_END, v_x == -0.010368 );
    ocp.subjectTo( AT_END, v_y == 0.0 );
    
//ocp.subjectTo( Sfmin <= Sf <= Sfmax );


    // DEFINE A PLOT WINDOW:
    // ---------------------
    GnuplotWindow window;
        window.addSubplot( x ,"x"  );
        window.addSubplot( y ,"y"  );
        window.addSubplot( v_x ,"v_x"  );
        window.addSubplot( v_y,"v_y" );
        window.addSubplot( a_x,"a_x" );
        window.addSubplot(a_y,"a_y");


    // DEFINE AN OPTIMIZATION ALGORITHM AND SOLVE THE OCP:
    // ---------------------------------------------------
    OptimizationAlgorithm algorithm(ocp);
    algorithm.set( KKT_TOLERANCE, 1e-8 );
    algorithm << window;
    
    algorithm.solve();
    
    return 0;
}