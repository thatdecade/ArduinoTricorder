
margin_for_error = 0.2;

//display_pcb();
//$fn=25;

module display_pcb()
{
    //scale(1.001)
    
    translate([-38.1/2,-45.72/2,1.6/2])
    translate([1.27/2,-1,0])
    difference()
    {
        //OUTLINE
        translate([-1.27,1,0])
        linear_extrude(height = 1.6, center = true, convexity = 10) import("Adafruit 1.69in 280x240 Round Rectangle TFT.dxf");
        
        //HOLES
        //translate([2.25,43.18,0]) cylinder(r=1.2, h=2, center=true);
        //translate([34.0,43.18,0]) cylinder(r=1.2, h=2, center=true);
        //translate([34.0,4.2,0]) cylinder(r=1.2, h=2, center=true);
        //translate([2.25,4.2,0]) cylinder(r=1.2, h=2, center=true);
    }

    //LCD
    fast_rounded_box([30,38,5.4], 4);
}

module fast_rounded_box(size, radius)
{
    height = size[2];
    linear_extrude(height = height)
    projection(cut = true)
    roundedRectangle([size[0]-radius,size[1]-radius,0], radius);
}

module roundedRectangle(size, radius, frontTaper = 0) {
    // https://www.reddit.com/r/openscad/comments/bfx897/comment/elhugtd/
    
    x = size[0];
    y = size[1];
    z = size[2];

    hull() {
        cornerSphere([(-x/2)+(radius/2), (-y/2)+(radius/2) - frontTaper, z], radius);
        cornerSphere([(x/2)-(radius/2), (-y/2)+(radius/2) - frontTaper, z], radius);
        cornerSphere([(-x/2)+(radius/2), (y/2)-(radius/2), z], radius);
        cornerSphere([(x/2)-(radius/2), (y/2)-(radius/2), z], radius);
    }
}

module cornerSphere(location, radius) {
    translate(location) sphere(r=radius);
}