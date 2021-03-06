##  42_Scop
42 school project : 3d visualizer for .obj (blender) in C and OpenGL - made early 2016

I did not made any of the ressources objects in the ressources directory.
If no texture is provided with the mesh, or if it won't load it for whatever
reason, a default pony texture is applied.

#### File format
* [.obj](http://www.martinreddy.net/gfx/3d/OBJ.spec)
* [.mtl](http://www.fileformat.info/format/material/)

#### Requirement
	* .obj parsing (minimal to render object)
	* .obj error handling
	* Object rotation around axis y - middle of object
	* Make object rotation automatic		
	* Color (no textures) with grey level to see facettes
	* Basic Bad Texture application
	* toggle between texture and color with key press
	* Soft transition when texture/color switch
	* Move object on x, both directions, on keypress
	* Move object on y, both directions, on keypress
	* Move object on z, both directions, on keypress
	* Norme
	* OpenGL 4+ with shaders

#### Bonus
	* Camera rotation around object
	* Texure with provided UV coordinates
	* lighting
	* keys binded to increase/decrease light_power
	* Key Toggle auto_rot on and off
	* bmp loader
	* tga loader
	* zoom dezoom

#### Other/Idea
	- Control framerate
	- MODIFIY ROTATION SO THAT IT DOESN'T KEEP TRACK OF PREVIOUS ANGLES
	- mtl file parsing
	- Apply mtl file values
	- tga loader
	- Replace SDL with glgw ?
	- ZOOM - DE_ZOOM


###### mtl files

Extracted from [this topic](http://nendowingsmirai.yuku.com/forum/viewtopic/id/1723#.VsSZkpMrJBw) :

* Ns = Phong specular component. Ranges from 0 to 1000. (I've seen various statements about this range (see below))
* Kd = Diffuse color weighted by the diffuse coefficient.
* Ka = Ambient color weighted by the ambient coefficient.
* Ks = Specular color weighted by the specular coefficient.
* d = Dissolve factor (pseudo-transparency). Values are from 0-1. 0 is completely transparent, 1 is opaque.
* Ni = Refraction index. Values range from 1 upwards. A value of 1 will cause no refraction. A higher value implies refraction.
* illum = (0, 1, or 2) 0 to disable lighting, 1 for ambient & diffuse only (specular color set to black), 2 for full lighting (see below)
* sharpness = ? (see below)
* map_Kd = Diffuse color texture map.
* map_Ks = Specular color texture map.
* map_Ka = Ambient color texture map.
* map_Bump = Bump texture map.
* map_d = Opacity texture map.
* refl = reflection type and filename (?)

>...I've also seen values of 3 and 4 for 'illum'... when there's a 3 there, there's often a 'sharpness' attribute, but I didn't find any explanation. And I think the 4 illum value is supposed to denote two-sided polygons, but I kinda get the impression that some people just make stuff up and add whatever they want to these files, so there could be anything in there ;). Of course Poser only writes out a few of the above and apparently ignores many of the above when reading as well.

>Also for the Ns (OpenGL Shininess) value, OpenGL wants this range to be 0-128... one source said tha the wavefront spec was 0-1000 (and I've seen many .obj files with values in the 400-700 range), but the PolyTrans people say 0-200 and they've been refining thier converter program for over a decade (shrug). Of course Poser seems to use a range of 1-100, so I don't suppose you can ever get this value 'correct'
for all apps... Currently Wings3D currently always writes '80' for this value ;). I haven't checked Bryce or other apps yet... since my app is mostly geared towards Poser, I decided to cap it at 100.

>For the 'd' record (transparency), Wings3D always writes a '1.0', even when the material inside Wings is semi-transparent. When I read this value in my program, I store it as the alpha value of the Diffuse component (which OpenGL uses) and just write that value back out from there on export.
