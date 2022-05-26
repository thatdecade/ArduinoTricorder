
margin_for_error = 0.2;

module led_sequin()
{
    scale(1.01)
    {
        //OUTLINE
        linear_extrude(height = 1.6, center = true, convexity = 10) import("Adafruit LED Sequin.dxf");

        //LED
        translate([0,-0.762,1.6-0.55]) cube([3.2+margin_for_error,1.6+margin_for_error,0.55], center=true);

        //RESISTOR
        translate([0,1.016,1.6-0.55]) cube([1.6+margin_for_error,0.8+margin_for_error,0.55], center=true);

        //WIRES
        translate([-3.556,0,1.6-0.5]) cylinder(d=1,h=1, center=true, $fn=10);
        translate([ 3.556,0,1.6-0.5]) cylinder(d=1,h=1, center=true, $fn=10);
    }
}

//led_sequin();