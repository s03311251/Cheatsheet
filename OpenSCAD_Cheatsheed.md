# OpenSCAD cheatsheet

* https://www.openscad.org/documentation.html?version=2019.05

## Navigation

* Zoom: scroll wheel / Shift + right click
* Pan: right click
* Rotate: left click

## Syntax

### Shapes

``` openscad
cube(size=10); // Origin at one of the corner
cube([20,30,50]);
cube([20,30,50],center=true); // Origin at the centre

cylinder(h=3,r=8); // Origin at the centre of the base
cylinder(h=3,r=8,center=true); // Origin at the centre of the middle height
```

### Transformation

``` openscad
translate([0,0,5])
    cube([30,20,10],center=true);
scale([0.5,1,2])
    cylinder(h=3,r=8);

rotate([90,0,0])
    translate([0,-20,0])
    cylinder(h=3,r=8);
```

### Rendering

``` openscad
// higher resolution
$fa = 1;
$fs = 0.4;
```

