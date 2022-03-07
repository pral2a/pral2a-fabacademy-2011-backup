/*

---------------------------------------------------

cba.mit.edu
FABACADEMY - Great Invention Kit (GIK).
Pral2a, 2011. hi@pral2a.com
Creative Commons Attribution-Share Alike 3.0

---------------------------------------------------

GIK_node(module_size, material_height); 
	
	Creates a basic node (4 moduls A + 1 modul B) nested for cutting	

GIK_modulA(module_size, material_height); 
	
	Creates a single node A

GIK_modulB(module_size, material_height); 
	
	Creates a single node B

*/

GIK_node (6, 1.5);
//GIK_modulA (6, 1.5);
//GIK_modulB (6, 1.5);


module GIK_node (m, material_height) {

translate([m*3+0.1,m+0.1]) rotate(0) GIK_modulA (m, material_height);
translate([-m*3+0.1,m+0.1]) rotate(0) GIK_modulA (m, material_height);
translate([m*3+0.1,-(m+0.1)]) rotate(180) GIK_modulA (m, material_height);
translate([-m*3+0.1,-(m+0.1)]) rotate(180) GIK_modulA (m, material_height);
translate(0) rotate(0) GIK_modulB (m, material_height);
}

module GIK_modulA (m, material_height) {

long_width=m*3;
short_width=m;
height=m;
fit_width=height*2;
fit_height=material_height;

A=[+long_width,+height];
B=[+short_width,-height];
C=[-short_width,-height];
D=[-long_width,+height];
base_points=[A,B,C,D];

AB_mid=[((+(long_width))+(+(short_width)))/2,((+(height)+-(height))/2)];
CD_mid=[((-(short_width))+(-(long_width)))/2,((-(height)++(height))/2)];


AB_angle=45;
CD_angle=-45;

difference() {
polygon(base_points, center=true);

for(i = [
        [0, -height],
        [-short_width, +height],
        [+short_width, +height],
        ])
        translate (i) square([fit_height,fit_width], center = true);

translate (AB_mid) rotate (AB_angle) square([fit_height,fit_width], center = true);
translate (CD_mid) rotate (CD_angle) square([fit_height,fit_width], center = true);

}
}

module GIK_modulB (m, material_height) {

diameter=sqrt(m*m+m*m);
short_width=m;
height=m;
fit_width=height*2;
fit_height=material_height;

AB_angle=45;
CD_angle=-45;

difference() {
circle(r = diameter, center=true);


translate ([0, -diameter]) rotate (0) square([fit_height,fit_width], center = true);
translate ([0, +diameter]) rotate (0) square([fit_height,fit_width], center = true);
translate ([-diameter, 0]) rotate (90) square([fit_height,fit_width], center = true);
translate ([+diameter, 0]) rotate (90) square([fit_height,fit_width], center = true);

}
}


