var slider;
var angle;
var root, b, b1, b2;
var v;
const lenFactor = 2/3;
var rootLen = 90;
var branchLen;
var t;
function setup() {
    createCanvas(400, 400);
    slider = createSlider(0, PI/4, PI / 16, 0.01);
    t = new tree(new node(200,400), rootLen, angle);
    t.grow();
}

function draw() {
    background(51);
    angle = slider.value();
    t = new tree(new node(200,400), rootLen, angle);
    t.grow();
    t.draw();
}

function node(x, y)
{
    return createVector(x, y);
}

function branch(base, angle, len, offset=0)
{
    const axis_offset = -PI/2;
    this.offset = offset;
    this.base = base;
    this.angle = angle;
    this.len = len;
    let v = p5.Vector.fromAngle(axis_offset + this.offset + this.angle, this.len);

    this.getEnd = function()
    {
        return p5.Vector.add(this.base, v);
    }
    this.getAbsAngle = function ()
    {
        return this.angle + this.offset;
    }
    this.draw = function()
    {
        push();
        stroke(255);
        translate(base.x, base.y);
        line(0,0,v.x, v.y);
        pop();
        // line(begin, end);
    }
}
function tree(base, len, angle)
{
    this.base = base;
    this.len = len;
    this.angle = angle;
    this.root = new treeNode(this.base, 0, this.len);
    this.grow = function()
    {
        this.root.left = new treeNode(this.root.br.getEnd(), this.angle, this.len*lenFactor);
        this.root.left.growLeft();
        this.root.left.growRight();
        this.root.right = new treeNode(this.root.br.getEnd(), -this.angle, this.len*lenFactor);
        this.root.right.growLeft();
        this.root.right.growRight();
    }
    this.draw = function()
    {
        this.root.draw();
        this.root.left.draw();
        this.root.right.draw();
    }
}
function treeNode(base, angle, len, offset)
{   
    const minBranchLen = 3;
    this.br = new branch(base, angle, len, offset);
    this.left = this.right = null;
    this.growLeft = function()
    {
        if(len * lenFactor > minBranchLen)
        {
            this.left = new treeNode(this.br.getEnd(), -angle, len * lenFactor, this.br.getAbsAngle());
            this.left.growLeft();
            this.left.growRight();
        }  
    }
    this.growRight = function()
    {
        if(len * lenFactor > minBranchLen)
        {
            this.right = new treeNode(this.br.getEnd(), angle, len * lenFactor, this.br.getAbsAngle());
            this.right.growLeft();
            this.right.growRight();
        }     
    }
    this.draw = function()
    {
        this.br.draw();
        if(this.left != null)
            this.left.draw();
        if(this.right != null)
            this.right.draw();
    }
}