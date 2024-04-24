x = 8;
h = 5.5;
y = h;

$fn = 30;

module cyl(d,h) {
	hull() {
		translate([d/4,0]) cylinder(d=d,h=h);
		translate([-d/4,0]) cylinder(d=d,h=h);
	}
}

difference() {
	cube([19.1,y,2]);

	dist = (19.1-13.5)/2;
	#translate([dist,y/2]) cyl(d=2.1,h=2);
	#translate([19.1-dist,y/2]) cyl(d=2.1,h=2);
}

difference() {
	
	translate([(19.1-x-2*1)/2,0,2]) cube([x+2*1,y,2]);
	translate([(19.1-x)/2,0,2]) cube([x,y,2]);
	
}