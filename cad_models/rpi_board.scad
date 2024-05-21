module pcb() {
	import("../kicad_workspace/bottom/pcb_shape/shape.dxf");
}

module spacer() {
	linear_extrude(height=3) difference() {
		circle(d=5);
		circle(d=3);
	}
}

holes = [
	[3.5,3.5],
	[3.5,3.5+23],
	[65-3.5,3.5],
	[65-3.5,3.5+23]
];

$fn = 60;
h = 2;

camera_holes = [
	[2.0,2.0],
	[25-2.0,2.0],
	[2.0,14.5],
	[25-2.0,14.5]
];

module my_circle(d) {
	hull() {
		translate([0,-d]) circle(d=d);
		translate([0,d]) circle(d=d);
	}
}

camera_x = 25;
camera_y = 23.862;

d = 84;
linear_extrude(height=h) difference() {
	pcb();
	rotate([0,0,90])
		translate([-65/2+5,-30/2])
			for( h = holes ) translate(h) circle(d=3);
				

	#translate([0,-d/2+5/2,0]) square([camera_x, 5], center=true);
	#translate([0,-d/2+5/2,0]) square([camera_x, 10], center=true);
			
	translate([-3.4,15]) my_circle(d=2.2);
	translate([-3.4,-15]) my_circle(d=2.2);

	hull() {
		translate([20,10]) circle(d=10);
		translate([20,-17.5]) circle(d=10);
	}
	
	hull() {
		translate([-20,10]) circle(d=10);
		translate([-20,-17.5]) circle(d=10);
	}
    
    translate([-20,27.5]) circle(d=10);
    translate([20,27.5]) circle(d=10);
    
    translate([20,35]) square([3,10], center=true);
	translate([-20,35]) square([3,10], center=true);
    
	circle(d=10);
}

rotate([0,0,90]) translate([-65/2+5,-30/2,h]) for( hole = holes ) translate(hole) spacer();

translate([0,0,h]) difference() {
    rotation = -7;
    
	translate([-camera_x/2 -3,-d/2+5]) rotate([rotation,0,0]) cube([camera_x+2*3,4,6]);
	
	#translate([-17/2,-d/2+5 - 0.01]) rotate([rotation,0,0]) cube([17,3,6 + 0.01]);
	#translate([25/2-2,-d/2+5, 3]) rotate([-90+rotation,0]) cylinder(d=2.4,h=5);
	#translate([-25/2+2,-d/2+5, 3]) rotate([-90+rotation,0]) cylinder(d=2.4,h=5);
}




