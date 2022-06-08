
friction_fit = 0.02;
sliding_fit  = 0.2;
loose_fit    = 2.0;

$fn=50; //crank up for final render

/* ******************************* */

hinge_new();

/* ******************************* */

module hinge_new()
{
    hinge_outline(22.51);
    
    
    //hinge_outline(-22.51);
}

module hinge_outline(x_pos)
{
    translate([x_pos,6.5,19.8]) rotate([0,90,0]) 
    {
        difference()
        {
            //main cyl
            cylinder(d=8.06-sliding_fit, h=21.43, center=true);
            translate([0,0,0]) cylinder(d=9, h=9, center=true);
            
            //slots
            translate([0,0,-8.2]) cube([10,10,0.6], center=true);
            translate([0,0,4.2])  cube([10,10,0.6], center=true);
            translate([0,0,8.2])  cube([10,10,0.6], center=true);
            
            //post
            posts();
        }
        
        //pegs
        //TBD, ypos of pegs may need adjustment
        translate([5,0.5,6.2]) cube([4,3+friction_fit,3+friction_fit], center=true);
        translate([5,0.5,-6.2]) cube([4,3+friction_fit,3+friction_fit], center=true);
        
        //connect the cyls
        difference()
        {
            cylinder(d=7.6, h=21.43, center=true);
            translate([0,0,0]) cylinder(d=9, h=9, center=true);
            cylinder(d=4, h=20, center=true);
            posts();
        }
    }
}

module posts()
{
    translate([0,0,-5.9]) cylinder(d1=1, d2=4.5, h=3, center=true);
    translate([0,0, 5.9]) cylinder(d1=4.5, d2=1, h=3, center=true);
}

/* ******************************* */
