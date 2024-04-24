x = 12.0;
y = 10.0;

$fn = 60;

hole = [x/2, y/2];

m_holes = [ [1.55,y/2], [12-1.55,y/2] ];
m_hole_d = 1.6 + 0.1;

hole_h = 0.7 + 0.1;
hole_d = 4.1;

pcb_h = 1.75;
//pcb_h = 1.56;

base_th = 2;

linear_extrude(height=hole_h) difference() {
	square([x,y]);
	translate(hole) circle(d=hole_d);
	
	for(m = m_holes) translate(m) circle(d=m_hole_d);
}

linear_extrude(height=hole_h) {
	translate([0,-pcb_h]) square([ x, pcb_h ]);
}

l = 3;
translate([0,0,-l]) 
	#linear_extrude(height=l + hole_h) {
		translate([0,-pcb_h-base_th]) square([x, base_th]);
	}