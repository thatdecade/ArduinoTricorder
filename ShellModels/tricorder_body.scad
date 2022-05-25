
/* Tricorder Model for printing

   Dustin Westaby 
   
   Ideally, orient on the print bed for color changes.
   See Lower Decks' Purple Stripe Tricorder, lol
   
   Note: don't worry about minor details like chamfers here.  Add later with FreeCAD.
   reddit.com/r/openscad/comments/lrcby9/minkowski_without_size_increase_cube_with_rounded/
*/

include <roundedcube.scad>; // https://danielupshaw.com/openscad-rounded-corners/

friction_fit = 0.02;
sliding_fit  = 0.2;
loose_fit    = 2.0;

wall_thickness = 2;

outer_x = 80;
outer_y = 84.11;
outer_z = 39.9;

$fn=25; //crank up for final render

module outer_body()
{
    roundedcube([outer_x, outer_y, outer_z], false, 10, "y");
    //cube([80, 84.11, 39.9], false);;
}

module body_inner_wall()
{
    translate([wall_thickness,-1,wall_thickness]) 
    resize([outer_x - wall_thickness*2, outer_y+2, outer_z-wall_thickness*2]) 
    outer_body();
}

module body_inner_face()
{
    translate([wall_thickness+friction_fit,-1,wall_thickness+friction_fit]) 
    resize([outer_x - wall_thickness*2 - friction_fit*2, outer_y+2, outer_z-wall_thickness*2 - friction_fit*2]) 
    outer_body();
}

module cover_cutout(face="lower")
{
    difference()
    {
        translate([-0.1,0,19.1]) rotate([5.2,0,0]) cube([90,56,40]);
        if(face=="upper") translate([-0.1,7.6+wall_thickness*2/3,0]) rotate([90,0,0]) cube([90,56,40]);
    }
    
    translate([-0.1,55.84,24.17]) rotate([45,0,0]) cube([90,56,20]);
    if(face=="lower") translate([-0.1,0,0]) rotate([71.5,0,0]) cube([90,56,40]);
}

module body_cutout(face="upper")
{
    difference()
    {
        translate([-0.1,0,19.1-40+sliding_fit]) rotate([5.2,0,0]) cube([90,100,40]);
        if(face=="lower") translate([-0.1,wall_thickness/2,0]) rotate([71.5,0,0]) cube([90,56,40]);
    }
    
    translate([-0.1,55.84,24.17-28+sliding_fit]) rotate([45,0,0]) cube([90,56,20]);
    
    if(face=="upper") translate([-0.1,7.6,0]) rotate([90,0,0]) cube([90,56,40]);
}

module main_body()
{
    difference()
    {
        outer_body();
        cover_cutout();
        body_inner_wall();
    }
}

module lid_body()
{
    difference()
    {
        outer_body();
        body_cutout();
        body_inner_wall();
    }
}

module lcd_cutout()
{
    lcd_view_x = 1.61 * 25.4 + sliding_fit;
    lcd_view_y = 1.15 * 25.4 + sliding_fit;
    lcd_bezel_x = 1.73 * 25.4 + sliding_fit;
    lcd_bezel_y = 1.26 * 25.4 + sliding_fit;
    
    translate([50.75,39,18+wall_thickness]) rotate([5.2,0,0]) 
    {
        cube([lcd_view_x, lcd_view_y, wall_thickness*3], center=true);
        cube([lcd_bezel_x, lcd_bezel_y, wall_thickness*2], center=true);
    }
}

module screen_face_body()
{
    difference()
    {
        body_inner_face();
        cover_cutout();
        lcd_cutout();
        
        translate([0,0,-wall_thickness]) body_cutout(face="lower");
        
        //TBDs
        //sticker outline
        //Vertical LEDs: PWR, ALPHA, BETA, GAMMA, DELTA
        //Scroll wheel
        //Horizontal Edge Lit Buttons): GEO, MET, BIO
        //pin coupler
        //button pcb holder
    }
}

module id_lid_face()
{
    difference()
    {
        body_inner_face();
        body_cutout();
        lcd_cutout();
        
        translate([0,0,wall_thickness]) cover_cutout(face="upper");
        
        //TBDs
        //sticker outline
        //EMRG LED
        //ID LED
    }
}

main_body();
screen_face_body();
//id_lid_face();
//lid_body();