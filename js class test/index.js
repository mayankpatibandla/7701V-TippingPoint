class WayPoint {

	constructor(x, y, theta) {
	  this.x = x;
	  this.y = y;
	  this.theta = theta;
	}
  
	getCoords() {
	  return new Vector(this.x, this.y);
	}
  
	vector() {
	  return new Vector(this.x, this.y);
	}
}

let p1 = new WayPoint(10, 5, 1);

p1.vel = 5;

console.log(""+p1.vel);
console.log("ajsodjoasjdojaso")