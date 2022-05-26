
margin_for_error = 0.2;

//button_pcb();


module button_pcb()
{
    scale(1.01)
    translate([-41.91/2,-21.59/2,0])
    {
        //OUTLINE
        linear_extrude(height = 1.6, center = true, convexity = 10) import("ButtonPCB.dxf");

        translate([0,0,1.6-0.55])
        {
        //LEDs
        translate([9.525, 14.986,0]) button_side_led();
        translate([22.606,14.986,0]) button_side_led();
        translate([35.56, 14.986,0]) button_side_led();

        //BUTTONS
        translate([9.398, 8.382,0]) button_button();
        translate([22.479,8.382,0]) button_button();
        translate([35.56, 8.382,0]) button_button();

        //WIRES
        translate([39.37,20.32,0]) button_spaced_wire_connector();
        }
    }
}

module button_side_led()
{
    cube([3.98+margin_for_error,1.7+margin_for_error,2+margin_for_error], center=true);
}

module button_button()
{
            translate([0,0,+0.5]) cube([11.4+margin_for_error,1.6+margin_for_error,1.6], center=true);
            translate([0,0,1.9]) cube([6+margin_for_error,3.5+margin_for_error,4.57], center=true);
}

module button_spaced_wire_connector()
{
        button_wire_spacing = 2.54;
        translate([-button_wire_spacing*0,0,0]) cylinder(d=1,h=1, center=true, $fn=10);
        translate([-button_wire_spacing*1,0,0]) cylinder(d=1,h=1, center=true, $fn=10);
        translate([-button_wire_spacing*2,0,0]) cylinder(d=1,h=1, center=true, $fn=10);
        translate([-button_wire_spacing*3,0,0]) cylinder(d=1,h=1, center=true, $fn=10);
        translate([-button_wire_spacing*4,0,0]) cylinder(d=1,h=1, center=true, $fn=10);
        translate([-button_wire_spacing*5,0,0]) cylinder(d=1,h=1, center=true, $fn=10);
        translate([-button_wire_spacing*6,0,0]) cylinder(d=1,h=1, center=true, $fn=10);
        translate([-button_wire_spacing*7,0,0]) cylinder(d=1,h=1, center=true, $fn=10);
        translate([-button_wire_spacing*8,0,0]) cylinder(d=1,h=1, center=true, $fn=10);
}
