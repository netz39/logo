module wings(){
	linear_extrude(height = 2, center = false, convexity = 10, twist = 0)
	polygon([[10,10],[35,10],[40,18],[90,18],[95,26],[45,26],[20,18]]);
	linear_extrude(height = 4, center = false, convexity = 10, twist = 0)
	polygon([[15,18],[40,18],[45,26],[100,26],[105,34],[50,34],[25,26]]);
	linear_extrude(height = 6, center = false, convexity = 10, twist = 0)
	polygon([[20,26],[45,26],[50,34],[110,34],[115,42],[55,42],[20,34]]);
	linear_extrude(height = 8, center = false, convexity = 10, twist = 0)
	polygon([[20,34],[50,34],[55,42],[120,42],[125,50],[25,50],[17,42]]);
}

module badge() {
	wings();
	mirror() wings();
	translate([0,25,0])
	cylinder(h=8,r=25);
	linear_extrude(height = 10, center = false, convexity = 10, twist = 0)
	translate([-25,0,0])
	import("n39_logo_50mm.dxf");
}

scale(0.5)badge();