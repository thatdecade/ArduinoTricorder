
/* Tricorder Model for printing

   Dustin Westaby 
   
   Ideally, orient on the print bed for color changes.
   See Lower Decks' Purple Stripe Tricorder, lol
   
   Note: don't worry about minor details like chamfers here.  Add later with FreeCAD.
   reddit.com/r/openscad/comments/lrcby9/minkowski_without_size_increase_cube_with_rounded/
   
   List of Parts:
    - main_body() - Housing for most of the circuits and battery
    - control_panel_face_body() - Friction fits into main body. Housing for the LCD and most buttons / lights
    
    - lid_body() - Housing for closable lid
    - id_lid_face() - Friction fits into lid body. Housing for closable lid, contains two LEDs
    
    - body_hinge() - Glues onto control_panel_face_body. Contains hinge assembly and wire routes.
    - lid_hinge() - Glues onto id_lid_face. Contains hinge assembly and wire routes.
    
    - EMRG_insert() - Holder for EMRG LED
    
    - front_sensor_panel() - Friction fits into front of main body. Contains sensor outlines and screw holes.
    
    - button_diffusers() - Friction fits into control_panel_face_body
    - LED_diffusers() - Friction fits into control_panel_face_body
    
    TBD: Power switch assembly
   
*/

include <roundedcube.scad>; // https://danielupshaw.com/openscad-rounded-corners/
include <Adafruit LED Sequin.scad>;
include <ButtonPCB.scad>;

friction_fit = 0.02;
sliding_fit  = 0.2;
loose_fit    = 2.0;

wall_thickness = 2;

outer_x = 80;
outer_y = 84.11;
outer_z = 39.9;
outer_r = 10;

$fn=25; //crank up for final render

/* ******************************* */

//main_body(); //Note: print with a brim
upper_control_panel_face_body();
lower_control_panel_face_body();
//id_lid_face();
//lid_body();

/* ******************************* */

/* ******************************* */

module roundedcube_simple(size = [1, 1, 1], center = false, radius = 0.5) {
// More information: https://danielupshaw.com/openscad-rounded-corners/
	// If single value, convert to [x, y, z] vector
	size = (size[0] == undef) ? [size, size, size] : size;

	translate = (center == false) ?
		[radius, radius, radius] :
		[
			radius - (size[0] / 2),
			radius - (size[1] / 2),
			radius - (size[2] / 2)
	];

	translate(v = translate)
	minkowski() {
		cube(size = [
			size[0] - (radius * 2),
			size[1] - (radius * 2),
			size[2] - (radius * 2)
		]);
		sphere(r = radius);
	}
}

module outer_body()
{
    roundedcube([outer_x, outer_y, outer_z], false, outer_r, "y");
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
    
    translate([-0.1,55.84-0.07,24.17+0.007]) rotate([45,0,0]) cube([90,56,20]);
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
    
    //TBD - Battery protective sleeve
    
    //draw_retension_brackets
    //Prevent button presses from breaking the glue on the control panel
    faceplate_wall_thickness = 1.6; //measured
    //front left
    translate([wall_thickness,4.80+faceplate_wall_thickness,outer_r+1]) rotate([71.5,0,0]) 
    roundedcube_simple([2,10,2], true, 0.9);
    //front right
    translate([outer_x-wall_thickness,4.80+faceplate_wall_thickness,outer_r+1]) rotate([71.5,0,0]) 
    roundedcube_simple([2,10,2], true, 0.9);
    
    //top left
    translate([wall_thickness,30,19.1+1.72-faceplate_wall_thickness]) rotate([-5.2,0,0]) rotate([5.2,0,0]) rotate([5.2,0,0]) 
    roundedcube_simple([2,30,2], true, 0.9);
    //top right
    translate([outer_x-wall_thickness,30,19.1+1.72-faceplate_wall_thickness]) rotate([-5.2,0,0]) rotate([5.2,0,0]) rotate([5.2,0,0]) 
    roundedcube_simple([2,30,2], true, 0.9);
    
    //lower front
    translate([outer_x/2,wall_thickness-0.1+faceplate_wall_thickness,wall_thickness]) 
    roundedcube_simple([30,2,2], true, 0.9);
    
    //upper top
    translate([outer_x/2,outer_y-13.60+faceplate_wall_thickness,outer_z-wall_thickness]) 
    roundedcube_simple([30,2,2], true, 0.9);
    //upper left
    translate([wall_thickness,outer_y-23.2+faceplate_wall_thickness,outer_z-12]) rotate([45,0,0]) 
    roundedcube_simple([2,10,2], true, 0.9);
    //upper right
    translate([outer_x-wall_thickness,outer_y-23.2+faceplate_wall_thickness,outer_z-12]) rotate([45,0,0]) 
    roundedcube_simple([2,10,2], true, 0.9);

}

module lid_body()
{
    difference()
    {
        outer_body();
        body_cutout();
        body_inner_wall();
    }
    
    //TBD - retension brackets (so button presses don't push the cp out of position
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

module vertical_leds(type="windows")
{
    spacing = 8;
    
    if (type=="windows")
    {
        //sequin inserts
        translate([14.5,30,19.5]) 
        rotate([5.2,0,0]) 
        {
            translate([0,spacing*0,0]) led_sequin();  //ALPHA
            translate([0,spacing*1,0]) led_sequin(); //BETA
            translate([0,spacing*2,0]) led_sequin(); //GAMMA
            translate([0,spacing*3,0]) led_sequin(); //DELTA
            
            translate([0,spacing*4+2.8,6.5]) 
            rotate([45-5,0,0]) led_sequin(); //PWR
        }
    }
        
    if (type=="windows")
    {
        //windows
        translate([14.55,29.1,19.5]) 
        rotate([5.2,0,0]) 
        {
            translate([0,spacing*0,0]) cube([8.1,3.2,5], center=true);  //ALPHA
            translate([0,spacing*1,0]) cube([8.1,3.2,5], center=true); //BETA
            translate([0,spacing*2,0]) cube([8.1,3.2,5], center=true); //GAMMA
            translate([0,spacing*3,0]) cube([8.1,3.2,5], center=true); //DELTA
            
            translate([0,spacing*4+2.8,6.5]) 
            rotate([45-5,0,0]) cube([8.1,3.2,5], center=true); //PWR
        }
    }
    
    
    if (type=="shield")
    {
        translate([14.5,26,19]) 
        rotate([5.2,0,0]) 
        {
            translate([0,spacing*0,0]) roundedcube_simple([15,wall_thickness,3], true, 0.9);
            translate([0,spacing*1,0]) roundedcube_simple([15,wall_thickness,3], true, 0.9);
            translate([0,spacing*2,0]) roundedcube_simple([15,wall_thickness,3], true, 0.9);
            translate([0,spacing*3,0]) roundedcube_simple([15,wall_thickness,3], true, 0.9);
        }
    }
}

module horizontal_button_windows()
{
    spacing = 12.8;
    translate([32.8,14,20])
    rotate([5.2,0,0]) 
    {
        //Horizontal Edge Lit Buttons): GEO, MET, BIO
        translate([spacing*0, 0,0]) cube([7,3,4.57], center=true);
        translate([spacing*1,0,0]) cube([7,3,4.57], center=true);
        translate([spacing*2, 0,0]) cube([7,3,4.57], center=true);
    }
    
}

module horizontal_button_pcb_holder(show_pcb=false)
{
   if(show_pcb) translate([44,17,12.5]) rotate([5.2,0,0]) color("blue") button_pcb();
       
   translate([45,17,12.5]) rotate([5.2,0,0]) 
   difference()
   {
       translate([0,-9.6,0.5])
       rotate([-90+71.5-5,0,0]) 
       roundedcube_simple([40,wall_thickness*2,1.6+wall_thickness*2],true,0.5);
       
       button_pcb();
   }
}

module control_panel_face_body()
{
    difference()
    {
        body_inner_face();
        cover_cutout();
        lcd_cutout();
        
        translate([0,0,-wall_thickness]) body_cutout(face="lower");
        
        vertical_leds(type="windows");
        horizontal_button_windows();
        
        //TBDs
        //sticker outline
        //Scroll wheel
        //pin coupler
        //wire route to cover
    }
    
    //LED Light Shield
    vertical_leds(type="shield");
    horizontal_button_pcb_holder(show_pcb=false);
}

module upper_control_panel_face_body()
{
    translate([0,0,0.01])
    difference()
    {
        control_panel_face_body();
        cube([100,100,24.18]);
    }
}

module lower_control_panel_face_body()
{
    difference()
    {
        control_panel_face_body();
        translate([0,0,24.18]) cube([100,100,24.18]);
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
        //wire route to control panel
    }
}
