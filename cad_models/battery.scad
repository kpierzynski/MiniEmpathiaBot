d = 18.15;
th = 2;
h = 7;
r=d/2-th;

$fn = 90*2;

difference() {
	rotate([0,0,-45]) {
		translate([-r,r+th/2,h/2]) rotate([0,0,45])
			translate([0,1,0]) cube([d+2*th, th+2, h], center=true);
		rotate([0,0,-20]) rotate_extrude(angle=220) translate([d/2,0]) square([th,h]);
	}
	
	translate([0,0,h/2]) rotate([-90,0]) cylinder(d=4.2, h=d/2 + 2);
	#translate([0,0,h/2]) rotate([-90,0]) cylinder(d=2.2, h=d);
}