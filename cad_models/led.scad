h = 6.1;
d = 22.9;
$fn = 60;

module base() {

	translate([0,0,h/2]) scale([0.99,0.99,1]) import("C:/Users/Konrad/Desktop/MiniEmpathiaBot/battery/led_base.stl");
}

base();

x = 30;
holes_x = 23;

difference() {
	translate([0,d/2-4/2,3/2]) cube([x,4,3], center=true);
	#translate([holes_x/2,d/2-4/2,0]) cylinder(d=2.4, h=3);
	#translate([-holes_x/2,d/2-4/2,0]) cylinder(d=2.4, h=3);
	
	scale([0.99,0.99,1]) cylinder(d=d,h=h);
}