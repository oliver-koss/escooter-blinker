$fn=360;

//Ausschnitt für Knopf

module rcube(length, width, depth, radius) {
    $fn =30;
    for(pos = [[radius,radius,0],[radius,depth-radius,0],[width-radius,depth-radius,0],[width-radius,radius,0]])
    {
        translate(pos){
            cylinder(r=radius,h=length);
        }
    }

    translate([radius,0,0]){
        cube([width-2*radius,depth,length]);
    }
    translate([0,radius,0]){
        cube([width, depth-2*radius,length]);
    }
}

module mounting () {
    difference(){
    union(){
    translate([-7.5, 14, 0]) cube([15, 6, 4]);
    cylinder(r=16.5, h=4);
    }
    
    union(){
        translate([-3, 7, -5]) cube([6, 16.5, 10]);
        translate(0, 0, -5) cylinder(r=11.5, h=10);
        translate([-15, 17.5, 2]) rotate([0, 90, 0]) cylinder(r=1.5, h=30);
        }
}
    }

module triangle(b, h, w){
//b = länge, h = höhe, w= breite
rotate(a=[90,90,90])
linear_extrude(height = w, center = true, convexity = 10, twist = 0)
polygon(points=[[0,0],[h,0],[0,b]], paths=[[0,1,2]]);
};

translate([-2, 46.5, 0]) rotate([0, 90, 0]) mounting();



module base(){
    cylinder(r=12, h=5);
    translate([-12, -8, 0]) rcube(5, 24, 30, 8);
}

difference(){
    base();
    union(){
        translate(-5, 0, 0) cylinder(r=8.25, h=30);
        translate([-8, 13, 4]) scale([0.6, 0.6, 0.6]) linear_extrude(height=3) text("PTT");
    }

}

translate([-2, 20, 0]) cube([4, 14, 5]);

translate([0, 32, 0]) rotate([0, 0, 180]) triangle(16, 6, 4);