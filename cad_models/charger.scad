loop_d = 8.5;

robot_d = 84;
th = 4;
$fn = 90;

module frame() {
    difference() {
        square([robot_d+2*th,robot_d-30], center=true);
        circle(d=robot_d);
    
        translate([0,-robot_d/2]) square([robot_d/2+th,robot_d]);
    }
}

difference() {
    linear_extrude(height=12.5) frame();
    
    translate([-robot_d/2,8.3,1]) #cube([10,10,0.4], center=true);
    translate([-robot_d/2,-8.3,1]) #cube([10,10,0.4], center=true);
}


translate([-robot_d/2+10/2,0,8.5/2]) difference() {
    cube([10,4,8.5], center=true);
    #translate([5,0,5]) rotate([0,45]) cube([10,4,8.5], center=true);
}